import pytest
from dataclasses import asdict
import random

from utils import MarketplaceError, is_valid_contact
from trader import Trader
from product import Product
from stand import Stand

# Stub for is_valid_contact
class DummyContactValidator:
    @staticmethod
    def valid(contact):
        return contact == "valid@trader.com"

@pytest.fixture(autouse=True)
def patch_contact_validator(monkeypatch):
    monkeypatch.setattr('trader.is_valid_contact', DummyContactValidator.valid)
    yield

# Utility for product
def make_product(pid=1, price=10.0):
    return Product(product_id=pid, name=f"P{pid}", description="Desc", price=price)

# Tests for initialization

def test_trader_valid(tmp_path, monkeypatch):
    # Fix random capital
    monkeypatch.setattr(random, 'uniform', lambda a,b: 1234.56)
    trader = Trader(trader_id=1, name="Alice", contact_info="valid@trader.com")
    assert trader.trader_id == 1
    assert trader.name == "Alice"
    assert trader.contact_info == "valid@trader.com"
    assert trader.capital == 1234.56
    # Stand auto-created
    assert isinstance(trader.stand, Stand)
    assert trader.stand.trader is trader

@pytest.mark.parametrize("bad_id,name,contact", [
    (0, "A", "valid@trader.com"),
    (-1, "A", "valid@trader.com"),
])
def test_trader_invalid_id(bad_id, name, contact):
    with pytest.raises(MarketplaceError) as exc:
        Trader(trader_id=bad_id, name=name, contact_info=contact)
    assert "идентификатор торговца" in str(exc.value)

@pytest.mark.parametrize("bad_name", ["", None])
def test_trader_empty_name(bad_name):
    with pytest.raises(MarketplaceError) as exc:
        Trader(trader_id=1, name=bad_name, contact_info="valid@trader.com")
    assert "Имя торговца" in str(exc.value)

@pytest.mark.parametrize("bad_contact, expected_msg", [
    ("", "Контактная информация торговца не может быть пустой"),
    ("no-at-symbol", "Проверьте корректность введенных данных"),
])
def test_trader_invalid_contact(bad_contact, expected_msg):
    with pytest.raises(MarketplaceError) as exc:
        Trader(trader_id=2, name="Bob", contact_info=bad_contact)
    assert expected_msg in str(exc.value)

# Tests for add_product and remove_product(empty_contact=None):
    trader = Trader(trader_id=3, name="Charlie", contact_info="valid@trader.com")
    p1 = make_product(1)
    # add
    trader.add_product(p1)
    assert p1 in trader.products
    # duplicate
    with pytest.raises(MarketplaceError):
        trader.add_product(p1)
    # remove
    trader.remove_product(p1.product_id)
    assert p1 not in trader.products
    # remove non-existing
    with pytest.raises(MarketplaceError):
        trader.remove_product(99)

# Tests for list_products

def test_list_products_returns_list():
    trader = Trader(trader_id=4, name="Dana", contact_info="valid@trader.com")
    assert trader.list_products() == []
    p1 = make_product(5)
    trader.add_product(p1)
    assert trader.list_products() == [p1]

# Tests for to_dict and from_dict

def test_to_dict_and_from_dict_roundtrip(monkeypatch):
    monkeypatch.setattr(random, 'uniform', lambda a,b: 1500.0)
    trader = Trader(trader_id=5, name="Eve", contact_info="valid@trader.com")
    p1 = make_product(10)
    trader.add_product(p1)
    data = trader.to_dict()
    # shallow stand present
    assert data['stand']['stand_id'] == trader.stand.stand_id
    # reconstruct
    new_trader = Trader.from_dict(data)
    assert new_trader.trader_id == trader.trader_id
    assert new_trader.name == trader.name
    assert new_trader.contact_info == trader.contact_info
    assert any(prod.product_id == 10 for prod in new_trader.products)
    # stand linked
    assert isinstance(new_trader.stand, Stand)
    assert new_trader.stand.trader is new_trader

# Test __str__

def test_str():
    trader = Trader(trader_id=6, name="Frank", contact_info="valid@trader.com")
    assert str(trader) == "Frank-valid@trader.com"
