from dataclasses import dataclass, field
from typing import Dict, Any
from cart import Cart
from utils import is_valid_contact, MarketplaceError
import random

@dataclass
class Buyer:
    buyer_id: int
    name: str
    contact_info: str
    cart: Cart = field(default_factory=Cart)
    balance: float = field(default_factory=lambda: round(random.uniform(1000, 2000), 2))

    def __post_init__(self):
        if not self.contact_info:
            raise MarketplaceError('Контактная информация отсутствует')
        if not self.name:
            raise MarketplaceError('Имя отсутствует')
        if self.buyer_id <= 0:
            raise MarketplaceError('Некорректный идентификатор покупателя')
        if self.balance < 0:
            raise MarketplaceError('Баланс не может быть отрицательным')
        if not is_valid_contact(self.contact_info):
            raise MarketplaceError('Проверьте корректность введенных данных')

    def to_dict(self) -> Dict[str, Any]:
        return {
            "buyer_id": self.buyer_id,
            "name": self.name,
            "contact_info": self.contact_info,
            "cart": self.cart.to_dict(),
            "balance": self.balance
        }

    @classmethod
    def from_dict(cls, data: Dict[str, Any]) -> 'Buyer':
        cart_data = data.get("cart", {})
        cart = Cart.from_dict(cart_data)
        return cls(
            buyer_id=data['buyer_id'],
            name=data['name'],
            contact_info=data['contact_info'],
            cart=cart,
            balance=data.get('balance', round(random.uniform(1000, 2000), 2))
        )
