from fastapi import APIRouter, HTTPException, status
from typing import List, Dict
from api.src.models import TraderResponse, TraderCreate, ProductResponse, ProductCreate, StandResponse
from api.src.dependencies import get_trader
from marketplace import MarketplaceManager
from utils import MarketplaceError

manager = MarketplaceManager()

router = APIRouter(tags=["Traders"])

@router.get("/traders/", response_model=List[TraderResponse])
def get_traders():
    """Получить список всех продавцов"""
    return [
        {
            "trader_id": t.trader_id,
            "name": t.name,
            "contact_info": t.contact_info,
            "capital": t.capital
        } for t in manager.traders
    ]

@router.get("/traders/{trader_id}", response_model=TraderResponse)
def get_trader_details(trader_id: int):
    """Получить информацию о конкретном продавце"""
    trader = get_trader(trader_id)
    return {
        "trader_id": trader.trader_id,
        "name": trader.name,
        "contact_info": trader.contact_info,
        "capital": trader.capital
    }

@router.post("/traders/", response_model=TraderResponse, status_code=status.HTTP_201_CREATED)
def create_trader(trader_data: TraderCreate):
    try:
        return manager.create_trader(trader_data.name, trader_data.contact_info)
    except Exception as e:
        raise HTTPException(status_code=400, detail=str(e))

@router.delete(
    "/traders/{trader_id}/inventory/{product_id}",
    status_code=status.HTTP_204_NO_CONTENT,
)
def remove_product_from_inventory(trader_id: int, product_id: int):
    trader = get_trader(trader_id)
    try:
        trader.remove_product(product_id)
        try:
            trader.stand.remove_product(product_id)
        except MarketplaceError:
            pass
        manager.save_state()
        return {
            "message": f"Product id={product_id} removed from inventory and stand of trader id={trader_id}"
        }
    except MarketplaceError as e:
        raise HTTPException(status_code=404, detail=str(e))


@router.post(
    "/traders/{trader_id}/stand/products/{product_id}",
    response_model=Dict[str, str],
    status_code=status.HTTP_200_OK
)
def add_product_to_stand(trader_id: int, product_id: int):
    trader = get_trader(trader_id)
    product = next(
        (p for p in manager.get_all_products() if p.product_id == product_id),
        None
    )
    if not product:
        raise HTTPException(status_code=404, detail="Product not found")
    if product not in trader.products:
        raise HTTPException(
            status_code=400,
            detail=f"Product id={product_id} does not belong to trader id={trader_id}"
        )
    try:
        trader.stand.add_product(product)
        manager.save_state()
        return {"message": f"Product id={product_id} added to stand of trader id={trader_id}"}
    except MarketplaceError as e:
        raise HTTPException(status_code=400, detail=str(e))


@router.delete(
    "/traders/{trader_id}/stand/products/{product_id}",
    status_code=status.HTTP_204_NO_CONTENT
)
def remove_product_from_stand(trader_id: int, product_id: int):
    trader = get_trader(trader_id)
    try:
        trader.stand.remove_product(product_id)
        manager.save_state()
        return {"message": f"Product id={product_id} removed from stand of trader id={trader_id}"}
    except MarketplaceError as e:
        raise HTTPException(status_code=404, detail=str(e))

@router.get(
    "/traders/{trader_id}/stand/unassigned-products",
    response_model=List[ProductResponse]
)
def get_products_not_on_stand(trader_id: int):
    trader = get_trader(trader_id)
    all_products = trader.products
    stand_products = trader.stand.products
    unassigned = [
        p for p in all_products
        if p not in stand_products
    ]
    return [
        {
            "product_id": p.product_id,
            "name": p.name,
            "description": p.description,
            "price": p.price
        }
        for p in unassigned
    ]

@router.post("/traders/{trader_id}/products/", response_model=ProductResponse, status_code=status.HTTP_201_CREATED)
def add_product(trader_id: int, product_data: ProductCreate):
    trader = get_trader(trader_id)
    try:
        return manager.add_product(trader_id, product_data.model_dump())
    except Exception as e:
        raise HTTPException(status_code=400, detail=str(e))

@router.get("/traders/{trader_id}/stand", response_model=StandResponse)
def get_trader_stand(trader_id: int):
    """Получить информацию о стенде продавца"""
    trader = get_trader(trader_id)
    return {
        "trader_id": trader.trader_id,
        "trader_name": trader.name,
        "location": trader.stand.location,
        "products": [
            {
                "product_id": p.product_id,
                "name": p.name,
                "description": p.description,
                "price": p.price
            } for p in trader.stand.products
        ]
    }

@router.get("/traders/{trader_id}/products", response_model=List[ProductResponse])
def get_trader_products(trader_id: int):
    """Получить товары конкретного продавца"""
    trader = get_trader(trader_id)
    return [
        {
            "product_id": p.product_id,
            "name": p.name,
            "description": p.description,
            "price": p.price
        } for p in trader.products
    ]