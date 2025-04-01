from dataclasses import dataclass
from typing import Optional, List
from trader import Trader
from product import Product,MarketplaceError

@dataclass
class Stand:
    stand_id:int
    location:str
    trader:Optional[Trader]
    products :List[Product]

    def __post_init__(self):
        if not self.stand_id and self.stand_id<=0:
            raise MarketplaceError(f'{self.stand_id} is an invalid stand_id')
        if not self.location:
            raise MarketplaceError('location is required')

    def assign_trader(self,trader:Trader)->None:
        if not self.trader:
            self.trader=trader
        else:
            raise MarketplaceError(f'Trader is already assigned to {self.trader}')

    def remove_trader(self,trader:Trader)->None:
        if not self.trader:
            raise MarketplaceError(f'This place is not assigned')
        else:
            self.trader=None




