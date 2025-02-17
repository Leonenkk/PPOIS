class User:
    def __init__(self, user_id: int, name: str, contact_info: str, balance: float):
        self._user_id: int = user_id
        self._name: str = name
        self._contact_info: str = contact_info
        self._balance: float = balance

    @property
    def user_id(self):
        return self._user_id

    @property
    def name(self):
        return self._name

    @property
    def contact_info(self):
        return self._contact_info

    @property
    def balance(self):
        return self._balance

    @balance.setter
    def balance(self, balance):
        if self._balance != balance:
            self._balance = balance
        else:
            raise ValueError("Balance cannot be the same")

    def get_info(self):
        return print(f' Name: {self._name}\n Contact_info:{self._contact_info}\n Balance:{self._balance}\n')

    @contact_info.setter
    def contact_info(self, new_contact_info):
        if self._contact_info != new_contact_info:
            self._contact_info = new_contact_info
        else:
            raise ValueError("Contact info cannot be the same")


class Seller(User):
    def __init__(self, user_id, name, contact_info, balance, stands: list[str]):
        super().__init__(user_id, name, contact_info, balance)
        self._stands: list[str] = stands

    @property
    def stands(self):
        return self._stands

    @stands.setter
    def stands(self, stands):
        if stands not in self._stands:
            self._stands.append(stands)
        else:
            raise ValueError("Stands cannot be the same")

    def get_info(self):
        pass

    @staticmethod
    def add_product(product, stand):
        pass

    @staticmethod
    def remove_product(product, stand):
        pass

    @staticmethod
    def start_negotiation(buyer, product):
        pass


class Buyer(User):
    def __init__(self, user_id, name, contact_info, balance, purchased_history: dict[str, int] = None):
        super().__init__(user_id, name, contact_info, balance)
        if purchased_history is None:
            self._purchased_history = {}
        self._purchased_history: dict[str, int] = purchased_history

    @property
    def purchased_history(self):
        return self._purchased_history

    @staticmethod
    def make_offer(product, price):
        pass

    @staticmethod
    def buy_product(product, seller):
        pass


class Product:
    def __init__(self, prodict_id:int, name:str, description:str,base_price:float,quantity:int,seller):
        self._prodict_id: int = prodict_id
        self._name: str = name
        self._description: str = description
        self._base_price: float = base_price
        self._quantity: int = quantity
        self._seller = seller #объект класса вызвать и пометить это явно в конструкторе,знач по умолч для description

    def update_price(self, price):
        pass

    def reserve(self,quantity):
        pass



user = User(1, 'Maksim', '+375296080896', 100.0)
user.get_info()
sellerr = Seller(1, 'Dima', 'd.str@gmail.com', 200, ['Zara', 'Bershka'])
sellerr.get_info()
sellerr.stands = 'ama'
print(sellerr.stands)
