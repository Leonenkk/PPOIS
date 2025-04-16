import json
from datetime import datetime
from typing import Dict, List, Type, Any
from dataclasses import asdict
from trader import Trader
from stand import Stand
from product import Product
from buyer import Buyer
from attraction import Attraction
from advertisement import Advertisement
from utils import MarketplaceError

class MarketplaceManager:
    def __init__(self, save_file: str = "marketplace_state.json"):
        self.save_file = save_file
        self.traders: List[Trader] = []
        self.buyers: List[Buyer] = []
        self.attractions: List[Attraction] = []
        self.advertisements: List[Advertisement] = []
        self.negotiations: Dict[int, Dict] = {}
        self.last_ids: Dict[Type, int] = {
            Trader: 0, Product: 0,
            Buyer: 0, Attraction: 0,
            Advertisement: 0, object: 0
        }

    def _get_next_id(self, entity_type: Type) -> int:
        self.last_ids[entity_type] += 1
        return self.last_ids[entity_type]

    def create_trader(self, name: str, contact: str) -> Trader:
        trader = Trader(
            trader_id=self._get_next_id(Trader),
            name=name,
            contact_info=contact
        )
        self.traders.append(trader)
        self.save_state()
        return trader

    def add_product(self, trader_id: int, product_data: Dict) -> Product:
        product = Product(
            product_id=self._get_next_id(Product),
            **product_data
        )
        trader = next(t for t in self.traders if t.trader_id == trader_id)
        trader.add_product(product)
        self.save_state()
        return product


    def update_product_price(self, product_id: int, new_price: float) -> None:
        product = next(p for p in self.get_all_products() if p.product_id == product_id)
        product.update_price(new_price)
        self.save_state()

    def create_buyer(self, name: str, contact: str) -> Buyer:
        buyer = Buyer(
            buyer_id=self._get_next_id(Buyer),
            name=name,
            contact_info=contact
        )
        self.buyers.append(buyer)
        self.save_state()
        return buyer

    def create_negotiation(self, buyer_id: int, product_id: int, price: float) -> int:
        for req in self.negotiations.values():
            if req['product_id'] == product_id and req['buyer_id'] == buyer_id:
                raise MarketplaceError("Предложение по этому товару уже отправлено. Дождитесь ответа продавца.")
        request_id = self._get_next_id(object)
        self.negotiations[request_id] = {
            'buyer_id': buyer_id,
            'product_id': product_id,
            'price': price
        }
        self.save_state()
        return request_id

    def accept_negotiation(self, request_id: int) -> None:
        request = self.negotiations.pop(request_id)
        buyer = next(b for b in self.buyers if b.buyer_id == request['buyer_id'])
        product = next(p for p in self.get_all_products() if p.product_id == request['product_id'])
        seller = next((t for t in self.traders if product in t.products), None)
        if buyer.cart.has_product(product.product_id):
            print("Товар уже в корзине, предложение не будет обработано.")
            return
        buyer.cart.negotiated_prices[product.product_id] = request['price']
        buyer.cart.add_to_cart(product, preserve_negotiated=True)
        if seller:
            seller.capital += request['price']
        self.save_state()

    def create_advertisement(self, description: str) -> Advertisement:
        ad = Advertisement(
            ad_id=self._get_next_id(Advertisement),
            description=description
        )
        self.advertisements.append(ad)
        self.save_state()
        return ad

    def create_attraction(self, name: str, description: str, ticket_price: float,seller: Trader) -> Attraction:
        attraction = Attraction(
            attraction_id=self._get_next_id(Attraction),
            name=name,
            description=description,
            ticket_price=ticket_price,
            seller_id=seller.trader_id,
        )
        self.attractions.append(attraction)
        self.save_state()
        return attraction

    def save_state(self) -> None:
        state = {
            "traders": [t.to_dict() for t in self.traders],
            "buyers": [b.to_dict() for b in self.buyers],
            "ads": [a.to_dict() for a in self.advertisements],
            "attractions": [a.to_dict() for a in self.attractions],
            "negotiations": self.negotiations,
            "last_ids": {k.__name__: v for k, v in self.last_ids.items()}
        }
        with open(self.save_file, 'w', encoding='utf-8') as f:
            json.dump(state, f, default=self._json_serializer, ensure_ascii=False, indent=2)

    def load_state(self) -> None:
        try:
            with open(self.save_file, 'r') as f:
                data = json.load(f)
                self.traders = [Trader.from_dict(t) for t in data["traders"]]
                self.buyers = [Buyer.from_dict(b) for b in data["buyers"]]
                self.advertisements = [Advertisement.from_dict(a) for a in data["ads"]]
                self.attractions = [Attraction.from_dict(a) for a in data["attractions"]]
                self.negotiations = data.get("negotiations", {})
                self.last_ids = {eval(k): v for k, v in data["last_ids"].items()}
        except (FileNotFoundError, KeyError):
            pass

    def _json_serializer(self, obj: Any) -> Any:
        if isinstance(obj, datetime):
            return obj.isoformat()
        return str(obj)

    def get_all_products(self) -> List[Product]:
        return [p for t in self.traders for p in t.products]

    def get_stands(self) -> List[Stand]:
        return [t.stand for t in self.traders]

    def get_active_ads(self) -> List[Advertisement]:
        return [ad for ad in self.advertisements if ad.is_active()]
