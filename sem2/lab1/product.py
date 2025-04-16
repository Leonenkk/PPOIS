from dataclasses import dataclass, asdict
from typing import Any, Dict
from utils import MarketplaceError

@dataclass
class Product:
    product_id: int
    name: str
    description: str
    price: float

    def __post_init__(self):
        if self.product_id <= 0:
            raise MarketplaceError(f'Идентификатор продукта должен быть положительным. Получено: {self.product_id}')
        if self.price > 2000:
            raise MarketplaceError(f'Цена продукта должна быть меньше 2000. Получено: {self.price}')
        self._validate_price(self.price)

    def _validate_price(self, price: float) -> None:
        if price < 0:
            raise MarketplaceError(f'Цена не может быть отрицательной. Получено: {price}')

    def update_price(self, new_price: float) -> None:
        self._validate_price(new_price)
        self.price = new_price

    def to_dict(self) -> Dict[str, Any]:
        return asdict(self)

    @classmethod
    def from_dict(cls, data: Dict[str, Any]) -> 'Product':
        return cls(**data)

    def __str__(self) -> str:
        return f'{self.name} (${self.price})'

    def __eq__(self, other):
        if isinstance(other, Product):
            return self.product_id == other.product_id
        return False

    def __hash__(self):
        return hash(self.product_id)
