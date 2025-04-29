import pytest
from dataclasses import asdict

from utils import MarketplaceError
from attraction import Attraction

# Tests for Attraction

def test_attraction_valid():
    attr = Attraction(attraction_id=1, name="Roller Coaster", description="Fast ride", ticket_price=50.0, seller_id=10)
    assert attr.attraction_id == 1
    assert attr.name == "Roller Coaster"
    assert attr.description == "Fast ride"
    assert attr.ticket_price == 50.0
    assert attr.seller_id == 10
    d = attr.to_dict()
    assert d == {
        "attraction_id": 1,
        "name": "Roller Coaster",
        "description": "Fast ride",
        "ticket_price": 50.0,
        "seller_id": 10
    }
    # Test from_dict
    attr2 = Attraction.from_dict(d)
    assert asdict(attr2) == asdict(attr)

@pytest.mark.parametrize("bad_id", [0, -5])
def test_attraction_invalid_id(bad_id):
    with pytest.raises(MarketplaceError):
        Attraction(attraction_id=bad_id, name="Test", description="Desc", ticket_price=10.0)

@pytest.mark.parametrize("bad_price", [-0.01, -100])
def test_attraction_invalid_price(bad_price):
    with pytest.raises(MarketplaceError):
        Attraction(attraction_id=1, name="Test", description="Desc", ticket_price=bad_price)