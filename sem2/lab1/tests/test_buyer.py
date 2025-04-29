import pytest
from dataclasses import asdict

from utils import MarketplaceError
from buyer import Buyer
from cart import Cart

# Stub for is_valid_contact
class DummyContactValidator:
    @staticmethod
    def valid(contact):
        return contact == "valid@example.com"

# Monkeypatch is_valid_contact in buyer module
import buyer as buyer_module

@pytest.fixture(autouse=True)
def patch_contact_validator(monkeypatch):
    monkeypatch.setattr(buyer_module, 'is_valid_contact', DummyContactValidator.valid)
    yield

# Tests for Buyer

def test_buyer_valid():
    cart = Cart()
    buyer = Buyer(buyer_id=1, name="Alice", contact_info="valid@example.com", cart=cart, balance=1500.0)
    assert buyer.buyer_id == 1
    assert buyer.name == "Alice"
    assert buyer.contact_info == "valid@example.com"
    assert isinstance(buyer.cart, Cart)
    assert buyer.balance == 1500.0
    d = buyer.to_dict()
    assert d['cart'] == cart.to_dict()
    assert d['balance'] == 1500.0
    buyer2 = Buyer.from_dict(d)
    assert buyer2.buyer_id == buyer.buyer_id
    assert buyer2.name == buyer.name
    assert buyer2.contact_info == buyer.contact_info
    assert isinstance(buyer2.cart, Cart)

@pytest.mark.parametrize("bad_contact", ["", "invalid-contact"])
def test_buyer_invalid_contact(bad_contact):
    with pytest.raises(MarketplaceError):
        Buyer(buyer_id=1, name="Bob", contact_info=bad_contact)

@pytest.mark.parametrize("bad_name", ["", None])
def test_buyer_missing_name(bad_name):
    with pytest.raises(MarketplaceError):
        Buyer(buyer_id=1, name=bad_name, contact_info="valid@example.com")

@pytest.mark.parametrize("bad_id", [0, -10])
def test_buyer_invalid_id(bad_id):
    with pytest.raises(MarketplaceError):
        Buyer(buyer_id=bad_id, name="Test", contact_info="valid@example.com")


def test_buyer_negative_balance():
    with pytest.raises(MarketplaceError):
        Buyer(buyer_id=1, name="Charlie", contact_info="valid@example.com", balance=-100.0)
