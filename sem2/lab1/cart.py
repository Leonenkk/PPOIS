from dataclasses import dataclass, field
from typing import List,Dict,Any
from product import Product, MarketplaceError


@dataclass
class Cart:
    cart_items: List[Product] = field(default_factory=list)

    def add_to_cart(self, product: Product) -> None:
        if any(p.product_id == product.product_id for p in self.cart_items):
            raise MarketplaceError(f'Product id={product.product_id} already added to cart')
        self.cart_items.append(product)

    def remove_from_cart(self, product: Product) -> None:
        if all(p.product_id != product.product_id for p in self.cart_items):
            raise MarketplaceError(f'Product id={product.product_id} is not added to cart')
        self.cart_items.remove(product)

    def view_cart(self) -> List[Product]:
        return self.cart_items

    def get_total_price(self) -> float:
        return sum( product.price for product in self.cart_items)

    def clear_cart(self) -> None:
        self.cart_items.clear()

    def to_dict(self)->Dict[str, Any]:
        return {
            "cart_items": [product.to_dict() for product in self.cart_items]
        }

    @classmethod
    def from_dict(cls, data: Dict[str, Any]) -> 'Cart':
        cart_items_data=data.get("cart_items",[])
        cart_items = [Product.from_dict(prod_data) for prod_data in cart_items_data]
        return cls(cart_items=cart_items)

