import xml.etree.ElementTree as ET
from datetime import date
from src.models.player import Player
from src.repositories.database_repository import DatabaseRepository


class XMLHandler:
    def __init__(self, db_repository: DatabaseRepository):
        self.db_repository = db_repository

    def import_from_xml(self, xml_file_path: str):
        try:
            tree = ET.parse(xml_file_path)
            root = tree.getroot()

            for player_element in root.findall("player"):
                full_name = player_element.find("full_name").text
                birth_date = date.fromisoformat(player_element.find("birth_date").text)
                team = player_element.find("team").text
                home_city = player_element.find("home_city").text
                squad = player_element.find("squad").text
                position = player_element.find("position").text

                player = Player(
                    full_name=full_name,
                    birth_date=birth_date,
                    team=team,
                    home_city=home_city,
                    squad=squad,
                    position=position,
                )

                self.db_repository.add_player(player)

            print("Data imported from XML successfully.")
        except Exception as e:
            print(f"Error importing from XML: {e}")