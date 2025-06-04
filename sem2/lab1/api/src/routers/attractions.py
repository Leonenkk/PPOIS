from fastapi import APIRouter, HTTPException, status
from typing import List, Dict
from api.src.models import AttractionCreate, AttractionResponse
from api.src.dependencies import get_trader, get_buyer
from marketplace import MarketplaceManager

manager = MarketplaceManager()

router = APIRouter(tags=["Attractions"])


@router.get("/attractions/", response_model=List[AttractionResponse])
def get_attractions():
    """Получить список всех аттракционов"""
    attractions = []
    for attraction in manager.attractions:
        seller = next((t for t in manager.traders if t.trader_id == attraction.seller_id), None)
        attractions.append({
            "attraction_id": attraction.attraction_id,
            "name": attraction.name,
            "description": attraction.description,
            "ticket_price": attraction.ticket_price,
            "seller_id": attraction.seller_id,
            "seller_name": seller.name if seller else None
        })
    return attractions

@router.post("/attractions/", response_model=AttractionResponse, status_code=status.HTTP_201_CREATED)
def create_attraction(attraction_data: AttractionCreate):
    try:
        seller = get_trader(attraction_data.seller_id)
        return manager.create_attraction(
            attraction_data.name,
            attraction_data.description,
            attraction_data.ticket_price,
            seller
        )
    except Exception as e:
        raise HTTPException(status_code=400, detail=str(e))


@router.post("/attractions/{attraction_id}/visit/", response_model=Dict[str, str])
def visit_attraction(attraction_id: int, buyer_id: int):
    buyer = get_buyer(buyer_id)
    attraction = next((a for a in manager.attractions if a.attraction_id == attraction_id), None)
    if not attraction:
        raise HTTPException(status_code=404, detail="Attraction not found")

    if buyer.balance < attraction.ticket_price:
        raise HTTPException(status_code=400, detail="Insufficient funds")

    try:
        buyer.balance -= attraction.ticket_price
        seller = next((t for t in manager.traders if t.trader_id == attraction.seller_id), None)
        if seller:
            seller.capital += attraction.ticket_price
        manager.save_state()
        return {"message": "Attraction visited successfully"}
    except Exception as e:
        raise HTTPException(status_code=400, detail=str(e))


