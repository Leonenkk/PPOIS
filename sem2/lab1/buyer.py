from dataclasses import dataclass,field
from product import MarketplaceError
from typing import Dict,Any
from cart import Cart


@dataclass
class Buyer:
    buyer_id: int
    name: str
    contact_info:str
    cart: Cart=field(default_factory=Cart)

    def __post_init__(self):
        if  not self.contact_info:
            raise MarketplaceError('contact_info is empty')
        if not self.name:
            raise MarketplaceError('name is empty')
        if self.buyer_id<=0 or not self.buyer_id:
            raise MarketplaceError('buyer_id is incorrect')

    def to_dict(self)->Dict[str, Any]:
        return {
            "buyer_id":self.buyer_id,
            "name":self.name,
            "contact_info":self.contact_info,
            "cart":self.cart.to_dict()
        }

    @classmethod
    def from_dict(cls,data: Dict[str, Any]) -> 'Buyer':
        cart_data=data.get("cart",{})
        cart=Cart.from_dict(cart_data)
        return cls(
            buyer_id=data['buyer_id'],
            name=data['name'],
            contact_info=data['contact_info'],
            cart=cart
        )



