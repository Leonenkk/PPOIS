import json
from typing import Any, Dict
from dataclasses import dataclass,asdict
from enum import Enum

class MarketplaceError(Exception):
    pass

@dataclass
class Product:
    class Status(Enum):
        NEW='new'
        SOLD='sold'
        ON_SALE='on_sale'

    product_id: int
    name: str
    description: str
    price: float
    status: Status =Status.NEW

    def __post_init__(self):
        if self.product_id<=0:
            raise MarketplaceError(f'Product {self.product_id} is out of range')
        if self.price <0:
            raise MarketplaceError(f'Price is negative')

    def update_price(self,new_price:float)->None:
        if new_price <0:
            raise MarketplaceError('Price cannot be negative')
        self.price=new_price

    def mark_as_sold(self)->None:
        self.status=self.Status.SOLD

    def mark_as_on_sale(self)->None:
        self.status=self.Status.ON_SALE

    def to_dict(self)->Dict[str, Any]:
        data=asdict(self)
        data['status']=self.status.value
        return data

    @classmethod
    def from_dict(cls,data: Dict[str, Any]) -> 'Product':
        if 'status' in data:
            data['status']=cls.Status(data['status'])
        return cls(**data)

    def __str__(self)->str:
        return f'{self.name}-{self.price}'
