import json
import pytest
import random
from datetime import datetime

from marketplace import MarketplaceManager
from utils import MarketplaceError
from trader import Trader
from product import Product
from buyer import Buyer
from attraction import Attraction
from advertisement import Advertisement

# Stub for contact validation
@pytest.fixture(autouse=True)
def patch_contact(monkeypatch):
    from utils import is_valid_contact
    monkeypatch.setattr('utils.is_valid_contact', lambda c: True)
    yield

@pytest.fixture
def empty_manager(tmp_path):
    path = tmp_path / "state.json"
    return MarketplaceManager(save_file=str(path))

# --- create_trader ---
def test_create_trader_sets_id_and_saves(empty_manager, tmp_path):
    mgr = empty_manager
    trader = mgr.create_trader(name="Alice", contact="alice@example.com")
    assert isinstance(trader, Trader)
    assert trader.trader_id == 1
    # Check file exists
    data = json.loads((tmp_path / "state.json").read_text())
    assert any(t['trader_id'] == 1 for t in data['traders'])

# --- add_product & update_product_price ---
def test_add_and_update_product(empty_manager):
    mgr = empty_manager
    trader = mgr.create_trader(name="Bob", contact="bob@example.com")
    prod = mgr.add_product(trader_id=trader.trader_id, product_data={
        'name':'X','description':'D','price':100.0
    })
    assert isinstance(prod, Product)
    assert prod.product_id == 1
    # update price
    mgr.update_product_price(product_id=prod.product_id, new_price=150.0)
    assert prod.price == 150.0

# --- create_buyer ---
def test_create_buyer_assigns_id_and_saves(empty_manager, tmp_path):
    mgr = empty_manager
    buyer = mgr.create_buyer(name="Charlie", contact="charlie@example.com")
    assert isinstance(buyer, Buyer)
    assert buyer.buyer_id == 1
    data = json.loads((tmp_path / "state.json").read_text())
    assert any(b['buyer_id'] == 1 for b in data['buyers'])

# --- negotiations ---
def test_create_and_duplicate_negotiation(empty_manager):
    mgr = empty_manager
    buyer = mgr.create_buyer(name="D", contact="d@example.com")
    trader = mgr.create_trader(name="E", contact="e@example.com")
    prod = mgr.add_product(trader_id=trader.trader_id, product_data={'name':'P','description':'D','price':50.0})
    req_id = mgr.create_negotiation(buyer_id=buyer.buyer_id, product_id=prod.product_id, price=40.0)
    assert req_id == 1
    # duplicate
    with pytest.raises(MarketplaceError):
        mgr.create_negotiation(buyer_id=buyer.buyer_id, product_id=prod.product_id, price=45.0)

def test_accept_negotiation_moves_to_cart_and_updates_capital(empty_manager):
    mgr = empty_manager
    buyer = mgr.create_buyer(name="F", contact="f@example.com")
    trader = mgr.create_trader(name="G", contact="g@example.com")
    prod = mgr.add_product(trader_id=trader.trader_id, product_data={'name':'Z','description':'D','price':60.0})
    req_id = mgr.create_negotiation(buyer_id=buyer.buyer_id, product_id=prod.product_id, price=55.0)
    mgr.accept_negotiation(request_id=req_id)
    # buyer cart contains
    assert buyer.cart.has_product(prod.product_id)
    assert buyer.cart.negotiated_prices[prod.product_id] == 55.0
    # trader capital increased
    assert trader.capital >= 55.0

# --- advertisements ---
def test_create_advertisement(empty_manager):
    mgr = empty_manager
    ad = mgr.create_advertisement(description="Sale!")
    assert isinstance(ad, Advertisement)
    assert ad.ad_id == 1
    assert ad.description == "Sale!"

# --- attractions ---
def test_create_attraction(empty_manager):
    mgr = empty_manager
    trader = mgr.create_trader(name="H", contact="h@example.com")
    attraction = mgr.create_attraction(name="Ride", description="Fun", ticket_price=5.0, seller=trader)
    assert isinstance(attraction, Attraction)
    assert attraction.attraction_id == 1
    assert attraction.seller_id == trader.trader_id

# --- persistence load_state ---
def test_save_and_load_state(tmp_path):
    path = tmp_path / "state2.json"
    mgr = MarketplaceManager(save_file=str(path))
    mgr.create_trader(name="I", contact="i@example.com")
    mgr.create_buyer(name="J", contact="j@example.com")
    mgr2 = MarketplaceManager(save_file=str(path))
    mgr2.load_state()
    assert any(t.trader_id == 1 for t in mgr2.traders)
    assert any(b.buyer_id == 1 for b in mgr2.buyers)

# --- getters ---
def test_get_all_products_and_stands_and_ads(empty_manager):
    mgr = empty_manager
    trader = mgr.create_trader(name="K", contact="k@example.com")
    prod = mgr.add_product(trader_id=trader.trader_id, product_data={'name':'X','description':'D','price':20.0})
    ads = mgr.create_advertisement(description="AdX")
    buyer = mgr.create_buyer(name="L", contact="l@example.com")
    # getter
    assert prod in mgr.get_all_products()
    assert trader.stand in mgr.get_stands()
    # monkeypatch ad.is_active
    ad = mgr.advertisements[0]
    ad.is_active = lambda: False
    assert ads not in mgr.get_active_ads()
    ad.is_active = lambda: True
    assert ads in mgr.get_active_ads()
