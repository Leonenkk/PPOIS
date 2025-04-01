import json
from typing import Any, Dict
from dataclasses import dataclass, asdict
from enum import Enum

class MarketplaceError(Exception):
    pass

@dataclass
class Product:
    class Status(Enum):
        NEW = 'new'
        SOLD = 'sold'
        ON_SALE = 'on_sale'

    product_id: int
    name: str
    description: str
    price: float
    status: Status = Status.NEW

    def __post_init__(self):
        if self.product_id <= 0:
            raise MarketplaceError(f'product_id must be positive. Got: {self.product_id}')
        if self.price >2000:
            raise MarketplaceError('Product price must be less than 2000. Got: {self.price}')
        self._validate_price(self.price)

    def _validate_price(self, price: float) -> None:
        if price < 0:
            raise MarketplaceError(f'Price cannot be negative. Got: {price}')

    def update_price(self, new_price: float) -> None:
        self._validate_price(new_price)
        self.price = new_price

    def mark_as_sold(self) -> None:
        self.status = self.Status.SOLD

    def mark_as_on_sale(self) -> None:
        self.status = self.Status.ON_SALE

    def to_dict(self) -> Dict[str, Any]:
        data = asdict(self)
        data['status'] = self.status.value
        return data

    @classmethod
    def from_dict(cls, data: Dict[str, Any]) -> 'Product':
        try:
            if 'status' in data:
                data['status'] = cls.Status(data['status'])
            return cls(**data)
        except ValueError as e:
            raise MarketplaceError(f'Invalid status: {data.get("status")}') from e

    def __str__(self) -> str:
        return f'{self.name} (${self.price}, status: {self.status.value})'

    def __eq__(self, other):
        if isinstance(other, Product):
            return self.product_id == other.product_id
        return False

    def __hash__(self):
        return hash(self.product_id)

