from dataclasses import dataclass, field
from datetime import datetime, timedelta
from typing import Optional, Any, Dict
from utils import MarketplaceError

DEFAULT_PRICE = 100.0
DEFAULT_DURATION = 600

@dataclass
class Advertisement:
    ad_id: int
    description: str
    price: float = DEFAULT_PRICE
    start_time: datetime = field(default_factory=lambda: datetime.now())
    duration: int = DEFAULT_DURATION
    stand: Optional[Dict[str, Any]] = field(default=None)

    def __post_init__(self):
        if self.ad_id <= 0:
            raise MarketplaceError("Идентификатор должен быть больше нуля")
        if not self.description.strip():
            raise MarketplaceError("Описание не может быть пустым или содержать только пробелы")
        if self.price < 0:
            raise MarketplaceError("Цена не может быть отрицательной")
        if self.duration < 0:
            raise MarketplaceError("Время не может быть отрицательным")

    def is_active(self, current_time: Optional[datetime] = None) -> bool:
        if current_time is None:
            current_time = datetime.now()
        end_time = self.start_time + timedelta(seconds=self.duration)
        return self.start_time <= current_time < end_time

    def to_dict(self) -> Dict[str, Any]:
        data = {
            'ad_id': self.ad_id,
            'description': self.description,
            'price': self.price,
            'start_time': self.start_time.isoformat(),
            'duration': self.duration,
        }
        if self.stand:
            data["stand"] = self.stand
        return data

    @classmethod
    def from_dict(cls, data: Dict[str, Any]) -> 'Advertisement':
        try:
            start_time = datetime.fromisoformat(data['start_time']) if "start_time" in data else datetime.now()
            ad = cls(
                ad_id=data['ad_id'],
                description=data['description'],
                price=data.get('price', DEFAULT_PRICE),
                start_time=start_time,
                duration=data.get('duration', DEFAULT_DURATION),
            )
            if "stand" in data:
                ad.stand = data["stand"]
            return ad
        except KeyError as e:
            raise MarketplaceError(f"Отсутствует обязательное поле: {e}") from e
        except (TypeError, ValueError) as e:
            raise MarketplaceError(f"Неверные данные: {e}") from e
