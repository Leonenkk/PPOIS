from fastapi import APIRouter, HTTPException, status
from typing import List, Dict, Union
from api.src.models import BuyerResponse, BuyerCreate, CartResponse, CartAddItem
from api.src.dependencies import get_buyer
from marketplace import MarketplaceManager


router = APIRouter(tags=["Buyers"])
manager = MarketplaceManager()

@router.delete("/buyers/{buyer_id}/cart", status_code=status.HTTP_204_NO_CONTENT)
def clear_cart(buyer_id: int):
    buyer = get_buyer(buyer_id)
    buyer.cart.clear_cart()
    manager.save_state()
    return


@router.get("/buyers/", response_model=List[BuyerResponse])
def get_buyers():
    """Получить список всех покупателей"""
    return [
        {
            "buyer_id": b.buyer_id,
            "name": b.name,
            "contact_info": b.contact_info,
            "balance": b.balance
        } for b in manager.buyers
    ]

@router.get("/buyers/{buyer_id}", response_model=BuyerResponse)
def get_buyer_details(buyer_id: int):
    """Получить информацию о конкретном покупателе"""
    buyer = get_buyer(buyer_id)
    return {
        "buyer_id": buyer.buyer_id,
        "name": buyer.name,
        "contact_info": buyer.contact_info,
        "balance": buyer.balance
    }

@router.get("/buyers/{buyer_id}/cart", response_model=CartResponse)
def get_buyer_cart(buyer_id: int):
    buyer = get_buyer(buyer_id)
    items = []
    total = 0

    for product in buyer.cart.cart_items:
        price = buyer.cart.negotiated_prices.get(product.product_id, product.price)
        items.append({
            "product": {
                "product_id": product.product_id,
                "name": product.name,
                "description": product.description,
                "price": product.price
            },
            "negotiated_price": price
        })
        total += price

    return {"items": items, "total": total}

@router.post("/buyers/", response_model=BuyerResponse, status_code=status.HTTP_201_CREATED)
def create_buyer(buyer_data: BuyerCreate):
    try:
        return manager.create_buyer(buyer_data.name, buyer_data.contact_info)
    except Exception as e:
        raise HTTPException(status_code=400, detail=str(e))

@router.post("/buyers/{buyer_id}/cart/", response_model=Dict[str, str])
def add_to_cart(buyer_id: int, item: CartAddItem):
    buyer = get_buyer(buyer_id)
    product = next((p for p in manager.get_all_products() if p.product_id == item.product_id), None)
    if not product:
        raise HTTPException(status_code=404, detail="Product not found")

    try:
        buyer.cart.add_to_cart(product)
        manager.save_state()
        return {"message": "Product added to cart"}
    except Exception as e:
        raise HTTPException(status_code=400, detail=str(e))

@router.post("/buyers/{buyer_id}/checkout/", response_model=Dict[str, Union[str, float]])
def checkout(buyer_id: int):
    buyer = get_buyer(buyer_id)
    total = buyer.cart.get_total_price()

    if buyer.balance < total:
        raise HTTPException(status_code=400, detail="Insufficient funds")

    try:
        buyer.balance -= total
        for product in buyer.cart.cart_items:
            seller = next((t for t in manager.traders if product in t.products), None)
            if seller:
                purchase_price = buyer.cart.negotiated_prices.get(product.product_id, product.price)
                seller.capital += purchase_price
        buyer.cart.clear_cart()
        manager.save_state()
        return {"message": "Checkout successful", "amount": total}
    except Exception as e:
        raise HTTPException(status_code=400, detail=str(e))