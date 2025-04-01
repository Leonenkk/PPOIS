from dataclasses import dataclass, field
from typing import Optional, List,Dict,Any
from trader import Trader
from product import Product,MarketplaceError

@dataclass
class Stand:
    stand_id:int
    location:str
    trader:Optional[Trader]=None
    products :List[Product]=field(default_factory=list)

    def __post_init__(self):
        if self.stand_id<=0:
            raise MarketplaceError(f'Invalid stand_id: {self.stand_id}. Must be positive.')
        if not self.location:
            raise MarketplaceError('location is required')

    def assign_trader(self,trader:Trader)->None:
        if not self.trader:
            self.trader=trader
            self.products=trader.products.copy()
        else:
            raise MarketplaceError(f'Trader is already assigned to {self.trader}')

    def remove_trader(self,trader:Trader)->None:
        if self.trader != trader:
            raise MarketplaceError('This trader is not assigned to the stand')
        if not self.trader:
            raise MarketplaceError(f'This place is not assigned')
        self.trader=None
        self.products.clear()

    def add_product(self,product:Product)->None:
         if not self.trader:
             raise MarketplaceError(f'This place is not assigned')
         if product not in self.trader.products:
             raise MarketplaceError(f'Product {product} is not assigned')
         if product in self.products:
             raise MarketplaceError(f'Product {product} is already assigned')
         self.products.append(product)

    def remove_product(self,product_id:int)->None:
        if not self.trader:
            raise MarketplaceError(f'This place is not assigned')
        for product in self.products:
            if product.product_id==product_id:
                self.products.remove(product)
                return
        raise MarketplaceError(f'Product with id={product_id} not found on the stand')

    def to_dict(self)->Dict[str, Any]:
        return {
            "stand_id":self.stand_id,
            "location":self.location,
            "trader":self.trader.to_dict() if self.trader else None,
            "products":[product.to_dict() for product in self.products],
        }

    @classmethod
    def from_dict(cls,data:Dict[str, Any])->'Stand':
        try:
            product_items=data.get("products",[])
            products=[Product.from_dict(product) for product in product_items]
            trader_data=data.get("trader")
            trader=Trader.from_dict(trader_data) if trader_data else None
            return cls(
                stand_id=data["stand_id"],
                location=data["location"],
                trader=trader,
                products=products,
            )
        except KeyError as e:
            raise MarketplaceError(f'Missing required field: {e}') from e
        except Exception as e:
            raise MarketplaceError(f'Invalid data: {e}') from e



