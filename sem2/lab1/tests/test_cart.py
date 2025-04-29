# File: tests/test_cart.py
import pytest

from utils import MarketplaceError
from cart import Cart
from product import Product

# Dummy Product class for testing
class DummyProduct(Product):
    def __init__(self, product_id=1, name="Test Product", description="Desc", price=10.0):
        super().__init__(product_id=product_id, name=name, description=description, price=price)

@pytest.fixture
def empty_cart():
    return Cart()

@pytest.fixture
def two_products():
    p1 = DummyProduct(product_id=1, name="Product A", description="Desc A", price=10.0)
    p2 = DummyProduct(product_id=2, name="Product B", description="Desc B", price=20.0)
    return p1, p2

# Tests for add_to_cart

def test_add_to_cart_success(empty_cart, two_products):
    p1, _ = two_products
    empty_cart.add_to_cart(p1)
    assert empty_cart.has_product(p1.product_id)
    assert empty_cart.get_total_price() == 10.0

@pytest.mark.parametrize("preserve", [True, False])
def test_add_to_cart_preserve_flag(empty_cart, two_products, preserve):
    p1, _ = two_products
    empty_cart.negotiated_prices[p1.product_id] = 5.0
    empty_cart.add_to_cart(p1, preserve_negotiated=preserve)
    if preserve:
        assert empty_cart.negotiated_prices[p1.product_id] == 5.0
    else:
        assert p1.product_id not in empty_cart.negotiated_prices


def test_add_duplicate_raises(empty_cart, two_products):
    p1, _ = two_products
    empty_cart.add_to_cart(p1)
    with pytest.raises(MarketplaceError):
        empty_cart.add_to_cart(p1)

# Tests for remove_from_cart

def test_remove_from_cart_success(empty_cart, two_products):
    p1, _ = two_products
    empty_cart.add_to_cart(p1)
    empty_cart.remove_from_cart(p1)
    assert not empty_cart.has_product(p1.product_id)


def test_remove_nonexistent_raises(empty_cart, two_products):
    p1, _ = two_products
    with pytest.raises(MarketplaceError):
        empty_cart.remove_from_cart(p1)

# Tests for view_cart

def test_view_cart_returns_list(empty_cart, two_products):
    p1, p2 = two_products
    empty_cart.add_to_cart(p1)
    empty_cart.add_to_cart(p2)
    items = empty_cart.view_cart()
    assert isinstance(items, list)
    assert items == [p1, p2]

# Tests for get_total_price with negotiated prices

def test_get_total_price_with_negotiated(empty_cart, two_products):
    p1, p2 = two_products
    empty_cart.add_to_cart(p1)
    empty_cart.add_to_cart(p2)
    empty_cart.negotiated_prices[p2.product_id] = 15.0
    total = empty_cart.get_total_price()
    assert total == 10.0 + 15.0

# Tests for clear_cart

def test_clear_cart(empty_cart, two_products):
    p1, p2 = two_products
    empty_cart.add_to_cart(p1)
    empty_cart.negotiated_prices[p1.product_id] = 5.0
    empty_cart.clear_cart()
    assert empty_cart.cart_items == []
    assert empty_cart.negotiated_prices == {}

# Tests for serialization round-trip

def test_to_from_dict_roundtrip(empty_cart, two_products):
    p1, p2 = two_products
    empty_cart.add_to_cart(p1)
    empty_cart.add_to_cart(p2)
    empty_cart.negotiated_prices[p1.product_id] = 8.0
    data = empty_cart.to_dict()
    new_cart = Cart.from_dict(data)
    assert new_cart.has_product(p1.product_id)
    assert new_cart.has_product(p2.product_id)
    assert new_cart.negotiated_prices[p1.product_id] == 8.0
    assert new_cart.get_total_price() == 8.0 + p2.price
