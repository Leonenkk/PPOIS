from fastapi import HTTPException

from buyer import Buyer
from marketplace import MarketplaceManager
from product import Product
from trader import Trader

manager=MarketplaceManager()

def get_trader(trader_id: int) -> Trader:
    trader = next((t for t in manager.traders if t.trader_id == trader_id), None)
    if not trader:
        raise HTTPException(status_code=404, detail="Trader not found")
    return trader

def get_buyer(buyer_id: int) -> Buyer:
    buyer = next((b for b in manager.buyers if b.buyer_id == buyer_id), None)
    if not buyer:
        raise HTTPException(status_code=404, detail="Buyer not found")
    return buyer

def get_product(product_id: int) -> Product:
    product = next((p for p in manager.get_all_products() if p.product_id == product_id), None)
    if not product:
        raise HTTPException(status_code=404, detail="Product not found")
    return product