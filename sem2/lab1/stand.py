from dataclasses import dataclass, field
from typing import List, Dict, Any, TYPE_CHECKING
from product import Product
from utils import MarketplaceError

if TYPE_CHECKING:
    from trader import Trader

@dataclass
class Stand:
    stand_id: int
    location: str
    trader: "Trader"
    products: List[Product] = field(default_factory=list)

    def __post_init__(self):
        if self.stand_id <= 0:
            raise MarketplaceError(f'Неверный stand_id: {self.stand_id}. Должен быть положительным.')
        if not self.location:
            raise MarketplaceError('Местоположение обязательно')

    def add_product(self, product: Product) -> None:
        if product not in self.trader.products:
            raise MarketplaceError(f'Продукт {product} не назначен торговцу')
        if product in self.products:
            raise MarketplaceError(f'Продукт {product} уже на стенде')
        self.products.append(product)

    def remove_product(self, product_id: int) -> None:
        for product in self.products:
            if product.product_id == product_id:
                self.products.remove(product)
                return
        raise MarketplaceError(f'Продукт с id={product_id} не найден на стенде')

    def to_dict(self, shallow: bool = False) -> Dict[str, Any]:
        data = {
            "stand_id": self.stand_id,
            "location": self.location,
            "products": [product.to_dict() for product in self.products],
        }
        if not shallow and self.trader:
            data["trader"] = {
                "trader_id": self.trader.trader_id,
                "name": self.trader.name,
                "contact_info": self.trader.contact_info,
            }
        return data

    @classmethod
    def from_dict(cls, data: Dict[str, Any]) -> "Stand":
        try:
            product_items = data.get("products", [])
            products = [Product.from_dict(product) for product in product_items]
            trader_data = data.get("trader")
            trader = None
            if trader_data:
                trader = type("TraderShallow", (), trader_data)
            return cls(
                stand_id=data["stand_id"],
                location=data["location"],
                trader=trader,
                products=products,
            )
        except KeyError as e:
            raise MarketplaceError(f'Отсутствует обязательное поле: {e}') from e
        except Exception as e:
            raise MarketplaceError(f'Неверные данные: {e}') from e
