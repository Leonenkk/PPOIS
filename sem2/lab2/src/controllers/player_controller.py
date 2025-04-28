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

    def search_players(self, full_name: Optional[str] = None, birth_date: Optional[date] = None,
                       team: Optional[str] = None, home_city: Optional[str] = None,
                       squad: Optional[str] = None, position: Optional[str] = None) -> List[Player]:
        try:
            players = self.db_repo.find_players(
                full_name=full_name,
                birth_date=birth_date,
                team=team,
                home_city=home_city,
                squad=squad,
                position=position
            )
            if not players:
                raise PlayerNotFoundError("No players found with specified criteria")
            self.search_results.emit(players) # type: ignore
            return players
        except sqlite3.Error as e:
            raise RuntimeError(f"Database error: {str(e)}")

    def get_all_players(self) -> List[Player]:
        try:
            players = self.db_repo.get_players()
            self.players_updated.emit()
            return players
        except sqlite3.Error as e:
            raise RuntimeError(f"Database error: {str(e)}")

    def format_player_for_display(self, player: Player) -> str:
        return f"{player.full_name} | {player.birth_date} | {player.team} | {player.home_city} | {player.squad} | {player.position}"

    def display_all_players(self) -> List[str]:
        try:
            return [self.format_player_for_display(p) for p in self.get_all_players()]
        except RuntimeError as e:
            return [str(e)]

    def display_search_results(self, search_conditions: dict) -> List[str]:
        try:
            return [self.format_player_for_display(p) for p in self.search_players(**search_conditions)]
        except (PlayerNotFoundError, RuntimeError) as e:
            return [str(e)]

    def display_deleted_count(self, delete_conditions: dict) -> int:
        try:
            return self.delete_players(**delete_conditions)
        except (DeletionFailedError, RuntimeError):
            return 0

    def convert_players_to_tree(self, players: List[Player]) -> QStandardItemModel:
        model = QStandardItemModel()
        model.setHorizontalHeaderLabels(["Full Name", "Birth Date", "Team", "Home City", "Squad", "Position"])
        for player in players:
            model.appendRow([
                QStandardItem(player.full_name),
                QStandardItem(str(player.birth_date)),
                QStandardItem(player.team),
                QStandardItem(player.home_city),
                QStandardItem(player.squad),
                QStandardItem(player.position)
            ])
        return model

    def display_players_in_tree(self, tree_view: QTreeView):
        try:
            model = self.convert_players_to_tree(self.get_all_players())
            tree_view.setModel(model)
        except RuntimeError as e:
            error_model = QStandardItemModel()
            error_model.appendRow([QStandardItem(str(e))])
            tree_view.setModel(error_model)