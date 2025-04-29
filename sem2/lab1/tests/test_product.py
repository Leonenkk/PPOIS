import pytest
from product import Product
from utils import MarketplaceError

# Tests for Product initialization

def test_product_valid():
    prod = Product(product_id=1, name="Widget", description="A useful widget", price=100.0)
    assert prod.product_id == 1
    assert prod.name == "Widget"
    assert prod.description == "A useful widget"
    assert prod.price == 100.0

@pytest.mark.parametrize("bad_id", [0, -1])
def test_product_invalid_id(bad_id):
    with pytest.raises(MarketplaceError) as exc:
        Product(product_id=bad_id, name="X", description="Desc", price=10.0)
    assert "Идентификатор продукта" in str(exc.value)

@pytest.mark.parametrize("too_high_price", [2000.01, 5000])
def test_product_price_too_high(too_high_price):
    with pytest.raises(MarketplaceError) as exc:
        Product(product_id=1, name="X", description="Desc", price=too_high_price)
    assert "должна быть меньше 2000" in str(exc.value)

@pytest.mark.parametrize("negative_price", [-0.01, -100])
def test_product_negative_price(negative_price):
    with pytest.raises(MarketplaceError) as exc:
        Product(product_id=1, name="X", description="Desc", price=negative_price)
    assert "не может быть отрицательной" in str(exc.value)

# Tests for update_price

def test_update_price_valid():
    prod = Product(product_id=2, name="Gadget", description="A gadget", price=50.0)
    prod.update_price(75.5)
    assert prod.price == 75.5

@pytest.mark.parametrize("invalid_price", [-10, -1])
def test_update_price_negative(invalid_price):
    prod = Product(product_id=3, name="Gizmo", description="A gizmo", price=20.0)
    with pytest.raises(MarketplaceError) as exc:
        prod.update_price(invalid_price)
    assert "не может быть отрицательной" in str(exc.value)

# Tests for to_dict/from_dict

def test_to_dict_and_from_dict():
    original = Product(product_id=4, name="Item", description="An item", price=15.0)
    data = original.to_dict()
    clone = Product.from_dict(data)
    assert clone == original
    assert clone.name == original.name
    assert clone.description == original.description
    assert clone.price == original.price

# Tests for __str__, __eq__, __hash__

def test_str():
    prod = Product(product_id=5, name="Thing", description="A thing", price=30.0)
    assert str(prod) == "Thing ($30.0)"

def test_eq_and_hash():
    p1 = Product(product_id=6, name="A", description="Desc A", price=10.0)
    p2 = Product(product_id=6, name="A2", description="Desc A2", price=20.0)
    p3 = Product(product_id=7, name="B", description="Desc B", price=10.0)
    # Equal by id
    assert p1 == p2
    assert hash(p1) == hash(p2)
    # Not equal
    assert p1 != p3
    assert hash(p1) != hash(p3)
