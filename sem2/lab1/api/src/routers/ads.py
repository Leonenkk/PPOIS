from fastapi import APIRouter, HTTPException, status, Query
from typing import List

from advertisement import DEFAULT_PRICE
from api.src.models import AdvertisementCreate, AdvertisementResponse
from api.src.dependencies import get_trader
from marketplace import MarketplaceManager

router = APIRouter(tags=["Advertisements"])
manager = MarketplaceManager()

@router.get("/advertisements/", response_model=List[AdvertisementResponse])
def get_advertisements(active_only: bool = Query(True, description="Только активные объявления")):
    """Получить список рекламных объявлений"""
    ads = manager.advertisements
    if active_only:
        ads = [ad for ad in ads if ad.is_active()]
    return [
        {
            "ad_id": ad.ad_id,
            "description": ad.description,
            "price": ad.price,
            "start_time": ad.start_time.isoformat(),
            "duration": ad.duration,
            "stand": ad.stand,
            "is_active": ad.is_active()
        } for ad in ads
    ]

@router.post("/advertisements/", response_model=AdvertisementResponse, status_code=status.HTTP_201_CREATED)
def create_advertisement(ad_data: AdvertisementCreate):
    try:
        trader = get_trader(ad_data.trader_id)
        if trader.capital < DEFAULT_PRICE:
            raise HTTPException(status_code=400, detail="Insufficient funds")
        ad = manager.create_advertisement(ad_data.description)
        trader.capital -= ad.price
        ad.stand = {
            "trader_name": trader.name,
            "location": trader.stand.location
        }
        manager.save_state()
        return {
            "ad_id": ad.ad_id,
            "description": ad.description,
            "price": ad.price,
            "start_time": ad.start_time.isoformat(),
            "duration": ad.duration,
            "stand": ad.stand,
            "is_active": ad.is_active()
        }
    except HTTPException:
        raise
    except Exception as e:
        raise HTTPException(status_code=400, detail=str(e))
