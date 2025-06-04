from pathlib import Path

from fastapi import FastAPI
from api.src.routers import (
    traders,
    buyers,
    products,
    stands,
    ads,
    attractions,
)
from marketplace import MarketplaceManager


MARKETPLACE_STATE_PATH ="/home/maksim/Рабочий стол/PPOIIS/sem2/lab1/marketplace_state.json"
manager = MarketplaceManager(MARKETPLACE_STATE_PATH)

app = FastAPI(title="Marketplace API", version="1.0.0")

app.include_router(traders.router)
app.include_router(buyers.router)
app.include_router(products.router)
app.include_router(stands.router)
app.include_router(ads.router)
app.include_router(attractions.router)

manager.load_state()

if __name__ == "__main__":
    import uvicorn
    uvicorn.run(app, host="0.0.0.0", port=8000)