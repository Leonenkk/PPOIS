from dataclasses import dataclass
from typing import Dict, Any
from utils import MarketplaceError

@dataclass
class Attraction:
    attraction_id: int
    name: str
    description: str
    ticket_price: float
    seller_id:int=0

    def __post_init__(self):
        if self.attraction_id <= 0:
            raise MarketplaceError("ID аттракциона должен быть положительным")
        if self.ticket_price < 0:
            raise MarketplaceError("Цена билета не может быть отрицательной")
        if not self.description.strip():
            raise MarketplaceError("Некорректное описание")
        if not self.name.strip():
            raise MarketplaceError("Некорректное имя")


    def to_dict(self) -> Dict[str, Any]:
        return {
            "attraction_id": self.attraction_id,
            "name": self.name,
            "description": self.description,
            "ticket_price": self.ticket_price,
            "seller_id": self.seller_id,
        }

    @classmethod
    def from_dict(cls, data: Dict[str, Any]) -> 'Attraction':
        return cls(**data)