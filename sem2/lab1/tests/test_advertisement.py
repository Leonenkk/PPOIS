import pytest
from datetime import datetime, timedelta
from advertisement import Advertisement, MarketplaceError

class TestAdvertisement:
    def test_valid_creation(self):
        ad = Advertisement(ad_id=1, description="Test ad")
        assert ad.ad_id == 1
        assert ad.description == "Test ad"
        assert ad.price == 100.0
        assert isinstance(ad.start_time, datetime)
        assert ad.duration == 600
        assert ad.stand is None

    def test_invalid_ad_id(self):
        with pytest.raises(MarketplaceError, match="Идентификатор должен быть больше нуля"):
            Advertisement(ad_id=0, description="Test")

    def test_empty_description(self):
        with pytest.raises(MarketplaceError, match="Описание не может быть пустым"):
            Advertisement(ad_id=1, description="   ")

    def test_negative_price(self):
        with pytest.raises(MarketplaceError, match="Цена не может быть отрицательной"):
            Advertisement(ad_id=1, description="Test", price=-10)

    def test_negative_duration(self):
        with pytest.raises(MarketplaceError, match="Время не может быть отрицательным"):
            Advertisement(ad_id=1, description="Test", duration=-100)

    def test_is_active(self):
        now = datetime.now()
        ad = Advertisement(ad_id=1, description="Test", start_time=now, duration=60)
        assert ad.is_active(now + timedelta(seconds=30)) is True
        assert ad.is_active(now + timedelta(seconds=61)) is False

    def test_to_dict(self):
        ad = Advertisement(ad_id=1, description="Test", stand={"size": "large"})
        data = ad.to_dict()
        assert data["ad_id"] == 1
        assert data["stand"]["size"] == "large"
        assert "start_time" in data

    def test_from_dict(self):
        test_time = datetime.now().isoformat()
        data = {
            "ad_id": 1,
            "description": "Test",
            "price": 200.0,
            "start_time": test_time,
            "duration": 300,
            "stand": {"location": "A1"}
        }
        ad = Advertisement.from_dict(data)
        assert ad.ad_id == 1
        assert ad.price == 200.0
        assert ad.stand["location"] == "A1"

    def test_from_dict_missing_required(self):
        with pytest.raises(MarketplaceError, match="Отсутствует обязательное поле"):
            Advertisement.from_dict({"description": "Test"})