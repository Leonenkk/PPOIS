from PyQt5.QtWidgets import QApplication
from src.views.add_player_window import AddPlayerDialog


def main():
    app = QApplication([])
    window = AddPlayerDialog()
    window.show()
    app.exec_()


if __name__ == "__main__":
    main()