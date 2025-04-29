import pytest

from utils import MarketplaceError
from stand import Stand
from product import Product

# Dummy Trader class
class DummyTrader:
    def __init__(self, trader_id, name, contact_info, products=None):
        self.trader_id = trader_id
        self.name = name
        self.contact_info = contact_info
        self.products = products or []

@pytest.fixture
def dummy_products():
    p1 = Product(product_id=1, name="Prod1", description="D1", price=10.0)
    p2 = Product(product_id=2, name="Prod2", description="D2", price=20.0)
    return p1, p2

@pytest.fixture
def dummy_trader(dummy_products):
    p1, p2 = dummy_products
    trader = DummyTrader(trader_id=1, name="Trader", contact_info="contact", products=[p1, p2])
    return trader

# Tests for initialization

def test_stand_valid(dummy_trader):
    stand = Stand(stand_id=1, location="Hall A", trader=dummy_trader)
    assert stand.stand_id == 1
    assert stand.location == "Hall A"
    assert stand.trader == dummy_trader
    assert stand.products == []

@pytest.mark.parametrize("bad_id", [0, -1])
def test_stand_invalid_id(bad_id, dummy_trader):
    with pytest.raises(MarketplaceError) as exc:
        Stand(stand_id=bad_id, location="Loc", trader=dummy_trader)
    assert 'stand_id' in str(exc.value)

@pytest.mark.parametrize("bad_loc", ["", None])
def test_stand_invalid_location(bad_loc, dummy_trader):
    with pytest.raises(MarketplaceError):
        Stand(stand_id=2, location=bad_loc, trader=dummy_trader)

# Tests for add_product

def test_add_product_success(dummy_trader, dummy_products):
    stand = Stand(stand_id=1, location="L", trader=dummy_trader)
    p1, _ = dummy_products
    stand.add_product(p1)
    assert p1 in stand.products

def test_add_product_not_assigned(dummy_trader):
    # product not in trader.products
    stand = Stand(stand_id=1, location="L", trader=dummy_trader)
    p3 = Product(product_id=3, name="Prod3", description="D3", price=15.0)
    with pytest.raises(MarketplaceError) as exc:
        stand.add_product(p3)
    assert 'не назначен торговцу' in str(exc.value)

def test_add_product_duplicate(dummy_trader, dummy_products):
    stand = Stand(stand_id=1, location="L", trader=dummy_trader)
    p1, _ = dummy_products
    stand.add_product(p1)
    with pytest.raises(MarketplaceError) as exc:
        stand.add_product(p1)
    assert 'уже на стенде' in str(exc.value)

# Tests for remove_product

def test_remove_product_success(dummy_trader, dummy_products):
    stand = Stand(stand_id=1, location="L", trader=dummy_trader)
    p1, _ = dummy_products
    stand.add_product(p1)
    stand.remove_product(p1.product_id)
    assert p1 not in stand.products

def test_remove_product_not_found(dummy_trader):
    stand = Stand(stand_id=1, location="L", trader=dummy_trader)
    with pytest.raises(MarketplaceError) as exc:
        stand.remove_product(99)
    assert 'не найден на стенде' in str(exc.value)

# Tests for to_dict

def test_to_dict_shallow(dummy_trader, dummy_products):
    stand = Stand(stand_id=1, location="L", trader=dummy_trader)
    p1, _ = dummy_products
    stand.add_product(p1)
    data = stand.to_dict(shallow=True)
    assert 'trader' not in data
    assert data['stand_id'] == 1
    assert data['location'] == "L"
    assert isinstance(data['products'], list)

def test_to_dict_deep(dummy_trader, dummy_products):
    stand = Stand(stand_id=1, location="L", trader=dummy_trader)
    p1, _ = dummy_products
    stand.add_product(p1)
    data = stand.to_dict(shallow=False)
    assert 'trader' in data
    assert data['trader']['trader_id'] == dummy_trader.trader_id

# Tests for from_dict

def test_from_dict_valid(dummy_trader, dummy_products):
    stand = Stand(stand_id=1, location="L", trader=dummy_trader)
    p1, _ = dummy_products
    stand.add_product(p1)
    data = stand.to_dict(shallow=False)
    new_stand = Stand.from_dict(data)
    assert new_stand.stand_id == stand.stand_id
    assert new_stand.location == stand.location
    assert any(prod.product_id == p1.product_id for prod in new_stand.products)

def test_from_dict_missing_field():
    data = {'location': 'X'}  # missing stand_id
    with pytest.raises(MarketplaceError) as exc:
        Stand.from_dict(data)
    assert 'Отсутствует обязательное поле' in str(exc.value)

def test_from_dict_invalid_data():
    data = {'stand_id': 'abc', 'location': 'L'}
    with pytest.raises(MarketplaceError) as exc:
        Stand.from_dict(data)
    assert 'Неверные данные' in str(exc.value)
