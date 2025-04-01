# attraction.py

from dataclasses import dataclass, field
from datetime import datetime, timedelta
from typing import List, Dict, Any
from product import MarketplaceError
from buyer import Buyer

DEFAULT_COST=100.0
DEFAULT_DURATION=600

@dataclass
class Attraction:
    attraction_id: int
    name: str
    description: str
    cost: DEFAULT_COST
    start_time: datetime = field(default_factory=datetime.now)
    duration: int = DEFAULT_DURATION
    participants: List[str] = field(default_factory=list)

    def __post_init__(self) -> None:
        if self.attraction_id <= 0:
            raise MarketplaceError("Attraction id must be a positive integer.")
        if not self.name:
            raise MarketplaceError("Attraction name cannot be empty.")
        if self.cost < 0:
            raise MarketplaceError("Attraction cost cannot be negative.")
        if self.duration <= 0:
            raise MarketplaceError("Attraction duration must be positive.")

    def is_active(self, current_time: datetime = None) -> bool:
        if current_time is None:
            current_time = datetime.now()
        elif not isinstance(current_time, datetime):
            raise TypeError("current_time must be a datetime object")
        end_time = self.start_time + timedelta(seconds=self.duration)
        return self.start_time <= current_time < end_time

    def add_participant(self, buyer: 'Buyer') -> None:
        if buyer.name in self.participants:
            raise MarketplaceError(f"Buyer '{buyer.name}' is already registered for this attraction.")
        self.participants.append(buyer.name)

    def remove_participant(self, buyer: 'Buyer') -> None:

        if buyer.name not in self.participants:
            raise MarketplaceError(f"Buyer '{buyer.name}' is not registered for this attraction.")
        self.participants.remove(buyer.name)

    def to_dict(self) -> Dict[str, Any]:
        return {
            "attraction_id": self.attraction_id,
            "name": self.name,
            "description": self.description,
            "cost": self.cost,
            "start_time": self.start_time.isoformat(),
            "duration": self.duration,
            "participants": self.participants,
        }

    @classmethod
    def from_dict(cls, data: Dict[str, Any]) -> 'Attraction':
        try:
            start_time = datetime.fromisoformat(data["start_time"]) if "start_time" in data else datetime.now()
            return cls(
                attraction_id=data["attraction_id"],
                name=data["name"],
                description=data["description"],
                cost=data["cost"],
                start_time=start_time,
                duration=data.get("duration", 3600),
                participants=data.get("participants", [])
            )
        except KeyError as e:
            raise MarketplaceError(f"Missing required field: {e}") from e
        except (TypeError, ValueError) as e:
            raise MarketplaceError(f"Invalid data: {e}") from e

