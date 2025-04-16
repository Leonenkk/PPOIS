from dataclasses import dataclass, field
from typing import List, Dict, Any
from product import Product
from utils import MarketplaceError

@dataclass
class Cart:
    cart_items: List[Product] = field(default_factory=list)
    negotiated_prices: Dict[int, float] = field(default_factory=dict)

    def add_to_cart(self, product: Product, preserve_negotiated: bool = False) -> None:
        if any(p.product_id == product.product_id for p in self.cart_items):
            raise MarketplaceError(f'Продукт с id={product.product_id} уже добавлен в корзину')
        if not preserve_negotiated:
            self.negotiated_prices.pop(product.product_id, None)
        self.cart_items.append(product)

    def remove_from_cart(self, product: Product) -> None:
        if all(p.product_id != product.product_id for p in self.cart_items):
            raise MarketplaceError(f'Продукт с id={product.product_id} не добавлен в корзину')
        self.cart_items.remove(product)

    def view_cart(self) -> List[Product]:
        return self.cart_items

    def get_total_price(self) -> float:
        return sum(
            self.negotiated_prices.get(p.product_id, p.price)
            for p in self.cart_items
        )

    def has_product(self, product_id: int) -> bool:
        return any(p.product_id == product_id for p in self.cart_items)

    def clear_cart(self) -> None:
        self.cart_items.clear()
        self.negotiated_prices.clear()

    def to_dict(self) -> Dict[str, Any]:
        return {
            "cart_items": [product.to_dict() for product in self.cart_items],
            "negotiated_prices": self.negotiated_prices
        }

    @classmethod
    def from_dict(cls, data: Dict[str, Any]) -> 'Cart':
        cart_items_data = data.get("cart_items", [])
        cart_items = [Product.from_dict(prod_data) for prod_data in cart_items_data]
        negotiated_prices_raw = data.get("negotiated_prices", {})
        negotiated_prices = {int(k): v for k, v in negotiated_prices_raw.items()}
        return cls(
            cart_items=cart_items,
            negotiated_prices=negotiated_prices
        )
