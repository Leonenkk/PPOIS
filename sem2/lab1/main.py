from fastapi import FastAPI, HTTPException, status, Depends, Query
from typing import Optional, Dict, List, Union
from pydantic import BaseModel
import uvicorn
from marketplace import MarketplaceManager
from trader import Trader
from buyer import Buyer
from product import Product
from stand import Stand
from advertisement import Advertisement, DEFAULT_PRICE
from attraction import Attraction
from utils import MarketplaceError

app = FastAPI(title="Marketplace API", version="1.0.0")

manager = MarketplaceManager()
manager.load_state()

class CartAddItem(BaseModel):
    product_id: int

class TraderResponse(BaseModel):
    trader_id: int
    name: str
    contact_info: str
    capital: float

class LoginRequest(BaseModel):
    contact_info: str

class AdvertisementCreate(BaseModel):
    description: str
    trader_id: int

class AttractionCreate(BaseModel):
    name: str
    description: str
    ticket_price: float
    seller_id: int

class ProductResponse(BaseModel):
    product_id: int
    name: str
    description: str
    price: float

class ProductCreate(BaseModel):
    name: str
    description: str
    price: float

class TraderCreate(BaseModel):
    name: str
    contact_info: str

class BuyerCreate(BaseModel):
    name: str
    contact_info: str

class BuyerResponse(BaseModel):
    buyer_id: int
    name: str
    contact_info: str
    balance: float

class CartItemResponse(BaseModel):
    product: ProductResponse

class CartResponse(BaseModel):
    items: List[CartItemResponse]
    total: float

class StandResponse(BaseModel):
    trader_id: int
    trader_name: str
    location: str
    products: List[ProductResponse]

class AdvertisementResponse(BaseModel):
    ad_id: int
    description: str
    price: float
    start_time: str
    duration: int
    stand: Optional[Dict] = None
    is_active: bool

class AttractionResponse(BaseModel):
    attraction_id: int
    name: str
    description: str
    ticket_price: float
    seller_id: int
    seller_name: Optional[str] = None

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

@app.post("/login")
def login(login_data: LoginRequest):
    contact = login_data.contact_info
    trader = next((t for t in manager.traders if t.contact_info == contact), None)
    if trader:
        return {"user_type": "trader", "id": trader.trader_id}

    buyer = next((b for b in manager.buyers if b.contact_info == contact), None)
    if buyer:
        return {"user_type": "buyer", "id": buyer.buyer_id}

    raise HTTPException(status_code=404, detail="User not found")

@app.get("/traders/", response_model=List[TraderResponse])
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

@app.get("/traders/{trader_id}", response_model=TraderResponse)
def get_trader_details(trader_id: int):
    """Получить информацию о конкретном продавце"""
    trader = get_trader(trader_id)
    return {
        "trader_id": trader.trader_id,
        "name": trader.name,
        "contact_info": trader.contact_info,
        "capital": trader.capital
    }

@app.delete("/buyers/{buyer_id}/cart", status_code=status.HTTP_204_NO_CONTENT)
def clear_cart(buyer_id: int):
    buyer = get_buyer(buyer_id)
    buyer.cart.clear_cart()
    manager.save_state()
    return

@app.get("/traders/{trader_id}/products", response_model=List[ProductResponse])
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

@app.get("/traders/{trader_id}/stand", response_model=StandResponse)
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

@app.get("/products/", response_model=List[ProductResponse])
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

@app.get("/products/{product_id}", response_model=ProductResponse)
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

@app.get("/buyers/", response_model=List[BuyerResponse])
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

@app.get("/buyers/{buyer_id}", response_model=BuyerResponse)
def get_buyer_details(buyer_id: int):
    """Получить информацию о конкретном покупателе"""
    buyer = get_buyer(buyer_id)
    return {
        "buyer_id": buyer.buyer_id,
        "name": buyer.name,
        "contact_info": buyer.contact_info,
        "balance": buyer.balance
    }

@app.get("/buyers/{buyer_id}/cart", response_model=CartResponse)
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

@app.get("/stands/", response_model=List[StandResponse])
def get_all_stands():
    """Получить список всех стендов"""
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

@app.get("/advertisements/", response_model=List[AdvertisementResponse])
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

@app.get("/attractions/", response_model=List[AttractionResponse])
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

@app.post("/traders/", response_model=TraderResponse, status_code=status.HTTP_201_CREATED)
def create_trader(trader_data: TraderCreate):
    try:
        return manager.create_trader(trader_data.name, trader_data.contact_info)
    except Exception as e:
        raise HTTPException(status_code=400, detail=str(e))

@app.post("/traders/{trader_id}/products/", response_model=ProductResponse, status_code=status.HTTP_201_CREATED)
def add_product(trader_id: int, product_data: ProductCreate):
    trader = get_trader(trader_id)
    try:
        return manager.add_product(trader_id, product_data.model_dump())
    except Exception as e:
        raise HTTPException(status_code=400, detail=str(e))

@app.put("/products/{product_id}/price/", response_model=Dict[str, str])
def update_product_price(product_id: int, new_price: float):
    try:
        manager.update_product_price(product_id, new_price)
        return {"message": "Price updated successfully"}
    except Exception as e:
        raise HTTPException(status_code=400, detail=str(e))

@app.post("/buyers/", response_model=BuyerResponse, status_code=status.HTTP_201_CREATED)
def create_buyer(buyer_data: BuyerCreate):
    try:
        return manager.create_buyer(buyer_data.name, buyer_data.contact_info)
    except Exception as e:
        raise HTTPException(status_code=400, detail=str(e))

@app.post("/advertisements/", response_model=AdvertisementResponse, status_code=status.HTTP_201_CREATED)
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

@app.post("/attractions/", response_model=AttractionResponse, status_code=status.HTTP_201_CREATED)
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

@app.post("/buyers/{buyer_id}/cart/", response_model=Dict[str, str])
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

@app.post("/buyers/{buyer_id}/checkout/", response_model=Dict[str, Union[str, float]])
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

@app.post("/attractions/{attraction_id}/visit/", response_model=Dict[str, str])
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

@app.post(
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


@app.delete(
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

@app.get(
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


@app.delete(
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


if __name__ == "__main__":
    uvicorn.run("main:app", host="0.0.0.0", port=8000, reload=True)
