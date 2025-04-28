from datetime import date
from typing import Optional, List, Tuple
import sqlite3
import xml.etree.ElementTree as ET
from PyQt5.QtCore import pyqtSignal, QObject
from PyQt5.QtGui import QStandardItemModel, QStandardItem
from PyQt5.QtWidgets import QTreeView
from src.exceptions.exceptions import PlayerNotFoundError, DeletionFailedError
from src.models.player import Player
from src.repositories.database_repository import DatabaseRepository


class PlayerController(QObject):
    player_added = pyqtSignal(Player)
    search_results = pyqtSignal(list)
    deletion_results = pyqtSignal(int)
    players_updated = pyqtSignal()

    def __init__(self, db_path: str):
        super().__init__()
        self.db_repo = DatabaseRepository(db_path)

    def add_player(self, full_name: str, birth_date: date, team: str, home_city: str, squad: str, position: str):
        try:
            if not all([full_name.strip(), team.strip(), home_city.strip(), squad.strip(), position.strip()]):
                raise ValueError("All fields must be filled")

            if birth_date > date.today():
                raise ValueError("Birth date cannot be in the future")

            player = Player(
                full_name=full_name,
                birth_date=birth_date,
                team=team,
                home_city=home_city,
                squad=squad,
                position=position
            )
            self.db_repo.add_player(player)
            self.player_added.emit(player)
        except sqlite3.Error as e:
            raise RuntimeError(f"Database error: {str(e)}")


    def delete_players(self, full_name: Optional[str] = None, birth_date: Optional[date] = None,
                       team: Optional[str] = None, home_city: Optional[str] = None,
                       squad: Optional[str] = None, position: Optional[str] = None) -> int:
        try:
            deleted_count = self.db_repo.delete_players(
                full_name=full_name,
                birth_date=birth_date,
                team=team,
                home_city=home_city,
                squad=squad,
                position=position
            )
            if deleted_count == 0:
                raise DeletionFailedError("No matching players found for deletion")
            self.deletion_results.emit(deleted_count)
            return deleted_count
        except sqlite3.Error as e:
            raise RuntimeError(f"Database error: {str(e)}")