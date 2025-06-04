from pydantic import BaseModel
from typing import Optional, Dict, List


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