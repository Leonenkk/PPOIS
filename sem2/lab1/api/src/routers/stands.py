from fastapi import APIRouter
from typing import List
from api.src.models import StandResponse
from marketplace import MarketplaceManager

router = APIRouter(tags=["Stands"])
manager = MarketplaceManager()


@router.get("/stands/", response_model=List[StandResponse])
def get_all_stands():
    stands = []
    for trader in manager.traders:
        stands.append({
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
        })
    return stands