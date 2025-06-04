from fastapi import APIRouter, HTTPException
from marketplace import MarketplaceManager
from api.src.models import LoginRequest

router = APIRouter(tags=["Authentication"])
manager = MarketplaceManager()

@router.post("/login")
def login(login_data: LoginRequest):
    contact = login_data.contact_info
    trader = next((t for t in manager.traders if t.contact_info == contact), None)
    if trader:
        return {"user_type": "trader", "id": trader.trader_id}

    buyer = next((b for b in manager.buyers if b.contact_info == contact), None)
    if buyer:
        return {"user_type": "buyer", "id": buyer.buyer_id}

    raise HTTPException(status_code=404, detail="User not found")