from dataclasses import dataclass,field
from typing import Dict,Any,List
from product import Product,MarketplaceError

@dataclass
class Trader:
    trader_id:int
    name:str
    contact_info:str
    products:List[Product]=field(default_factory=list)

    def __post_init__(self):
        if self.name is None:
            raise MarketplaceError("Trader name cannot be None")
        if not self.contact_info:
            raise MarketplaceError("Trader contact info cannot be None")
        if not self.trader_id or self.trader_id<=0:
            raise MarketplaceError("Trader id is incorrect")

    def add_product(self,product:Product)->None:
        if any(p.product_id==product.product_id for p in self.products):
            raise MarketplaceError(f"Trader product with id={product.product_id} already exists")
        self.products.append(product)

    def remove_product(self,product_id :int)->None:
        for p in self.products:
            if p.product_id==product_id:
                self.products.remove(p)
                return
        raise MarketplaceError(f"Trader product with id {product_id} does not exist")

    def list_products(self)->List[Product]:
        return self.products

    def to_dict(self)->Dict[str, Any]:
        return {
            "trader_id":self.trader_id,
            "name":self.name,
            "contact_info":self.contact_info,
            "products": [product.to_dict() for product in self.products]
        }

    @classmethod
    def from_dict(cls,data:Dict[str, Any])->'Trader':
        products=[Product.from_dict(prod_data) for prod_data in data.get("products",[])]
        return cls(
            trader_id=data["trader_id"],
            name=data["name"],
            contact_info=data["contact_info"],
            products=products
        )

    def __str__(self):
        return f'{self.name}-{self.contact_info}'

