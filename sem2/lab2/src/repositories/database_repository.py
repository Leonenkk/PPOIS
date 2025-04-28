import sqlite3


class DatabaseRepository:
    def __init__(self, db_path: str):
        self.db_path = db_path
        self.connection = sqlite3.connect(self.db_path)
        self.cursor = self.connection.cursor()
        self._initialize_db()

    def _initialize_db(self):
        self.cursor.execute("""
            CREATE TABLE IF NOT EXISTS players (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                full_name TEXT NOT NULL,
                birth_date DATE NOT NULL,
                age INTEGER NOT NULL,
                team TEXT NOT NULL,
                home_city TEXT NOT NULL,
                squad TEXT NOT NULL,
                position TEXT NOT NULL
            )
        """)
        self.connection.commit()

    