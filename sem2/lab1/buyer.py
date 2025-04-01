from dataclasses import dataclass,field
from product import MarketplaceError
from typing import Dict,Any
from cart import Cart
import random


@dataclass
class Buyer:
    buyer_id: int
    name: str
    contact_info:str
    cart: Cart=field(default_factory=Cart)
    balance: float=field(default_factory=lambda: round(random.uniform(1000,2000),2))

    def __post_init__(self):
        if  not self.contact_info:
            raise MarketplaceError('contact_info is empty')
        if not self.name:
            raise MarketplaceError('name is empty')
        if self.buyer_id<=0 or not self.buyer_id:
            raise MarketplaceError('buyer_id is incorrect')
        if self.balance <1000 or self.balance >2000:
            raise MarketplaceError('balance is out of range (1000-2000)')

    def to_dict(self)->Dict[str, Any]:
        return {
            "buyer_id":self.buyer_id,
            "name":self.name,
            "contact_info":self.contact_info,
            "cart":self.cart.to_dict(),
            "balance":self.balance
        }

    @classmethod
    def from_dict(cls,data: Dict[str, Any]) -> 'Buyer':
        cart_data=data.get("cart",{})
        cart=Cart.from_dict(cart_data)
        return cls(
            buyer_id=data['buyer_id'],
            name=data['name'],
            contact_info=data['contact_info'],
            cart=cart,
            balance=data.get('balance',round(random.uniform(1000,2000),2))
        )
