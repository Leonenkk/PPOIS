from fastapi import APIRouter, HTTPException
from typing import List, Dict
from api.src.models import ProductResponse
from marketplace import MarketplaceManager

router = APIRouter(tags=["Products"])
manager = MarketplaceManager()

@router.get("/products/", response_model=List[ProductResponse])
def get_all_products():
    products = []
    for trader in manager.traders:
        for product in trader.products:
            products.append({
                "product_id": product.product_id,
                "name": product.name,
                "description": product.description,
                "price": product.price
            })
    return products

@router.get("/products/{product_id}", response_model=ProductResponse)
def get_product_details(product_id: int):
    for trader in manager.traders:
        for product in trader.products:
            if product.product_id == product_id:
                return {
                    "product_id": product.product_id,
                    "name": product.name,
                    "description": product.description,
                    "price": product.price
                }
    raise HTTPException(status_code=404, detail="Product not found")


@router.put("/products/{product_id}/price/", response_model=Dict[str, str])
def update_product_price(product_id: int, new_price: float):
    try:
        manager.update_product_price(product_id, new_price)
        return {"message": "Price updated successfully"}
    except Exception as e:
        raise HTTPException(status_code=400, detail=str(e))

