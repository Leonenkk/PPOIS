from dataclasses import dataclass, field
from datetime import datetime, timedelta
from typing import Optional, Any, Dict

from product import MarketplaceError

DEFAULT_PRICE=100.0
DEFAULT_DURATION=600

@dataclass
class Advertisement:
    ad_id: int
    description: str
    price: float = DEFAULT_PRICE
    start_time: datetime = field(default_factory=lambda: datetime.now())
    duration: int = DEFAULT_DURATION

    def __post_init__(self):
        if self.ad_id <= 0:
            raise MarketplaceError("Advertisement id must be greater than zero")
        if not self.description.strip():
            raise MarketplaceError("Description cannot be empty or whitespace")
        if self.price < 0:
            raise MarketplaceError("Price cannot be negative")
        if self.duration < 0:
            raise MarketplaceError("Duration cannot be negative")

    def is_active(self, current_time: Optional[datetime] = None) -> bool:
        if current_time is None:
            current_time = datetime.now()
        elif not isinstance(current_time, datetime):
            raise TypeError("current_time must be a datetime object")
        end_time = self.start_time + timedelta(seconds=self.duration)
        return self.start_time <= current_time < end_time

    def to_dict(self) -> Dict[str, Any]:
        return {
            'ad_id': self.ad_id,
            'description': self.description,
            'price': self.price,
            'start_time': self.start_time.isoformat(),
            'duration': self.duration,
        }

    @classmethod
    def from_dict(cls, data: Dict[str, Any]) -> 'Advertisement':
        try:
            start_time = (
                datetime.fromisoformat(data['start_time'])
                if "start_time" in data
                else datetime.now()
            )
            return cls(
                ad_id=data['ad_id'],
                description=data['description'],
                price=data.get('price', DEFAULT_PRICE),
                start_time=start_time,
                duration=data.get('duration', DEFAULT_DURATION),
            )
        except KeyError as e:
            raise MarketplaceError(f"Missing required field: {e}") from e
        except (TypeError, ValueError) as e:
            raise MarketplaceError(f"Invalid data: {e}") from e

