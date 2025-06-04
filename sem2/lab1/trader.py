from dataclasses import dataclass, field
import random
from typing import Dict, Any, List
from product import Product
from stand import Stand
from utils import is_valid_contact, MarketplaceError

@dataclass
class Trader:
    trader_id: int
    name: str
    contact_info: str
    capital: float = field(default_factory=lambda: round(random.uniform(1000, 2000), 2))
    products: List[Product] = field(default_factory=list)
    stand: Stand = field(init=False)

    def __post_init__(self):
        if not self.name:
            raise MarketplaceError("Имя торговца не может быть пустым")
        if not self.contact_info:
            raise MarketplaceError("Контактная информация торговца не может быть пустой")
        if self.trader_id <= 0:
            raise MarketplaceError("Неверный идентификатор торговца")
        if not is_valid_contact(self.contact_info):
            raise MarketplaceError("Проверьте корректность введенных данных.")
        if self.capital < 0:
            raise MarketplaceError("Капитал не может быть отрицательным")
        self.stand = Stand(
            stand_id=self.trader_id,
            location=f"Стенд {self.name}",
            trader=self
        )

    def add_product(self, product: Product) -> None:
        if any(p.product_id == product.product_id for p in self.products):
            raise MarketplaceError(f"Продукт с id={product.product_id} уже существует")
        self.products.append(product)

    def remove_product(self, product_id: int) -> None:
        for p in self.products:
            if p.product_id == product_id:
                self.products.remove(p)
                return
        raise MarketplaceError(f"Продукт с id {product_id} не существует")

    def list_products(self) -> List[Product]:
        return self.products

    def to_dict(self) -> Dict[str, Any]:
        return {
            "trader_id": self.trader_id,
            "name": self.name,
            "contact_info": self.contact_info,
            "products": [product.to_dict() for product in self.products],
            "capital": self.capital,
            "stand": self.stand.to_dict(shallow=True),
        }

    @classmethod
    def from_dict(cls, data: Dict[str, Any]) -> "Trader":
        products = [Product.from_dict(prod_data) for prod_data in data.get("products", [])]
        trader = cls(
            trader_id=data["trader_id"],
            name=data["name"],
            contact_info=data["contact_info"],
            products=products,
            capital=data.get("capital", round(random.uniform(1000, 2000), 2)),
        )
        if "stand" in data and data["stand"]:
            from stand import Stand
            stand = Stand.from_dict(data["stand"])
            trader.stand = stand
            stand.trader = trader
        return trader

    def __str__(self) -> str:
        return f'{self.name}-{self.contact_info}'
