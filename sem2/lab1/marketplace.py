import json
import random
from typing import Dict, Any
from trader import Trader
from buyer import Buyer
from stand import Stand
from product import Product, MarketplaceError
from advertisement import Advertisement
from attraction import Attraction


class MarketPlace:
    def __init__(self) -> None:
        self.traders: Dict[int, Trader] = {}
        self.buyers: Dict[int, Buyer] = {}
        self.stands: Dict[int, Stand] = {}
        self.products: Dict[int, Product] = {}
        self.advertisements: Dict[int, Advertisement] = {}
        self.attractions: Dict[int, Attraction] = {}


    def add_trader(self, trader: Trader) -> None:
        if trader.trader_id in self.traders:
            raise MarketplaceError(f"Trader with id {trader.trader_id} already exists.")
        self.traders[trader.trader_id] = trader

    def add_buyer(self, buyer: Buyer) -> None:
        if buyer.buyer_id in self.buyers:
            raise MarketplaceError(f"Buyer with id {buyer.buyer_id} already exists.")
        self.buyers[buyer.buyer_id] = buyer

    def add_stand(self, stand: Stand) -> None:
        if stand.stand_id in self.stands:
            raise MarketplaceError(f"Stand with id {stand.stand_id} already exists.")
        self.stands[stand.stand_id] = stand

    def add_product(self, product: Product) -> None:
        if product.product_id in self.products:
            raise MarketplaceError(f"Product with id {product.product_id} already exists.")
        self.products[product.product_id] = product

    def add_advertisement(self, ad: Advertisement) -> None:
        if ad.ad_id in self.advertisements:
            raise MarketplaceError(f"Advertisement with id {ad.ad_id} already exists.")
        self.advertisements[ad.ad_id] = ad

    def add_attraction(self, attraction: Attraction) -> None:
        if attraction.attraction_id in self.attractions:
            raise MarketplaceError(f"Attraction with id {attraction.attraction_id} already exists.")
        self.attractions[attraction.attraction_id] = attraction

    def trade_product(self, buyer_id: int, trader_id: int, product_id: int) -> float:
        if buyer_id not in self.buyers:
            raise MarketplaceError(f"Buyer with id {buyer_id} does not exist.")
        if trader_id not in self.traders:
            raise MarketplaceError(f"Trader with id {trader_id} does not exist.")
        buyer = self.buyers[buyer_id]
        trader = self.traders[trader_id]
        product = None
        for p in trader.products:
            if p.product_id == product_id:
                product = p
                break
        if product is None:
            raise MarketplaceError(f"Product with id {product_id} not found in trader's inventory.")

        base_price = product.price
        final_price = base_price

        if random.choice([True, False]):
            final_price = base_price * 0.85
            if random.choice([True, False]):
                final_price = final_price * 0.90

        if final_price > 2000:
            final_price = 2000

        if buyer.balance < final_price:
            raise MarketplaceError("Buyer does not have enough balance to purchase this product.")

        buyer.balance -= final_price
        trader.capital += final_price

        product.mark_as_sold()
        trader.remove_product(product_id)
        buyer.cart.add_to_cart(product)
        return final_price

    def to_dict(self) -> Dict[str, Any]:
        return {
            "traders": {tid: trader.to_dict() for tid, trader in self.traders.items()},
            "buyers": {bid: buyer.to_dict() for bid, buyer in self.buyers.items()},
            "stands": {sid: stand.to_dict() for sid, stand in self.stands.items()},
            "products": {pid: product.to_dict() for pid, product in self.products.items()},
            "advertisements": {ad_id: ad.to_dict() for ad_id, ad in self.advertisements.items()},
            "attractions": {aid: attraction.to_dict() for aid, attraction in self.attractions.items()}
        }

    @classmethod
    def from_dict(cls, data: Dict[str, Any]) -> 'MarketPlace':
        mp = cls()
        mp.traders = {int(tid): Trader.from_dict(trader_data) for tid, trader_data in data.get("traders", {}).items()}
        mp.buyers = {int(bid): Buyer.from_dict(buyer_data) for bid, buyer_data in data.get("buyers", {}).items()}
        mp.stands = {int(sid): Stand.from_dict(stand_data) for sid, stand_data in data.get("stands", {}).items()}
        mp.products = {int(pid): Product.from_dict(product_data) for pid, product_data in data.get("products", {}).items()}
        mp.advertisements = {int(ad_id): Advertisement.from_dict(ad_data) for ad_id, ad_data in data.get("advertisements", {}).items()}
        mp.attractions = {int(aid): Attraction.from_dict(attr_data) for aid, attr_data in data.get("attractions", {}).items()}
        return mp


    def save_to_json(self, file_path: str) -> None:
        try:
            with open(file_path, 'w', encoding='utf-8') as f:
                json.dump(self.to_dict(), f, ensure_ascii=False, indent=4)
        except Exception as e:
            raise MarketplaceError(f"Error saving to JSON: {e}")

    @classmethod
    def load_from_json(cls, file_path: str) -> 'MarketPlace':
        try:
            with open(file_path, 'r', encoding='utf-8') as f:
                data = json.load(f)
            return cls.from_dict(data)
        except Exception as e:
            raise MarketplaceError(f"Error loading from JSON: {e}")

if __name__ == "__main__":
    mp = MarketPlace()

    trader = Trader(trader_id=1, name="Иван", contact_info="ivan@example.com")
    buyer = Buyer(buyer_id=1, name="Петр", contact_info="petr@example.com")
    product = Product(product_id=1, name="Старинное кресло", description="Кресло из 19 века", price=1500.0)
    print(trader.capital)
    print(buyer.balance)
    trader.add_product(product)

    mp.add_trader(trader)
    mp.add_buyer(buyer)
    mp.add_product(product)

    try:
        final_price = mp.trade_product(buyer_id=1, trader_id=1, product_id=1)
        print(f"Trade successful, final price: {final_price}")
        print(f"Buyer new balance: {buyer.balance}")
        print(f"Trader new capital: {trader.capital}")
    except MarketplaceError as e:
        print(f"Trade failed: {e}")

    ad = Advertisement(ad_id=1, description="Реклама ярмарки!", price=500.0)
    mp.add_advertisement(ad)

    attraction = Attraction(
        attraction_id=1,
        name="Колесо обозрения",
        description="Потрясающий вид на ярмарку с высоты птичьего полета.",
        cost=100.0
    )
    mp.add_attraction(attraction)
    mp.save_to_json("marketplace_state.json")

