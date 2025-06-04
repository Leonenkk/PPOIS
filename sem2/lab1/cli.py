from marketplace import MarketplaceManager
from utils import MarketplaceError
from typing import Optional
from trader import Trader
from buyer import Buyer

class CLI:
    def __init__(self):
        self.manager = MarketplaceManager()
        self.manager.load_state()
        self.current_trader: Optional[Trader] = None
        self.current_buyer: Optional[Buyer] = None

    def main_menu(self):
        while True:
            print("\n=== Ярмарка ===")
            print("1. Продавец")
            print("2. Покупатель")
            print("3. Выход")
            choice = input("> ").strip()
            if choice == "1":
                self.current_trader = self.authenticate_trader()
                if self.current_trader:
                    self.trader_menu()
            elif choice == "2":
                self.current_buyer = self.authenticate_buyer()
                if self.current_buyer:
                    self.buyer_menu()
            elif choice == "3":
                self.manager.save_state()
                exit()
            else:
                print("Неверный выбор. Попробуйте снова.")

    def authenticate_trader(self) -> Optional[Trader]:
        contact_info = input("Введите email/телефон: ").strip()
        if any(b.contact_info == contact_info for b in self.manager.buyers):
            print("Этот email/телефон уже зарегистрирован как покупатель.")
            return None

        trader = next((t for t in self.manager.traders if t.contact_info == contact_info), None)
        try:
            if not trader:
                create = input("Продавец не найден. Создать? (y/n): ").strip().lower()
                if create == 'y':
                    name = input("Введите имя: ").strip()
                    trader = self.manager.create_trader(name, contact_info)
            return trader
        except MarketplaceError as e:
            print(e)

    def authenticate_buyer(self) -> Optional[Buyer]:
        contact_info = input("Введите email/телефон: ").strip()
        if any(t.contact_info == contact_info for t in self.manager.traders):
            print("Этот email/телефон уже зарегистрирован как продавец.")
            return None

        buyer = next((b for b in self.manager.buyers if b.contact_info == contact_info), None)
        try:
            if not buyer:
                create = input("Покупатель не найден. Создать? (y/n): ").strip().lower()
                if create == 'y':
                    name = input("Введите имя: ").strip()
                    buyer = self.manager.create_buyer(name, contact_info)
            return buyer
        except MarketplaceError as e:
            print(e)

    def trader_menu(self):
        while True:
            print(f"\n=== Меню продавца {self.current_trader.name} ===")
            print("1. Добавить товар")
            print("2. Управление стендом")
            print("3. Инвентарь продавца")
            print("4. Показать баланс")
            print("5. Создать рекламу")
            print("6. Создать аттракцион")
            print("7. Запросы на торг")
            print("8. Назад")
            choice = input("> ").strip()
            if choice == "1":
                self.add_product_flow()
            elif choice == "2":
                self.manage_stand()
            elif choice == "3":
                self.view_inventory()
            elif choice == "4":
                self.view_trader_balance()
            elif choice == "5":
                self.create_ad_flow()
            elif choice == "6":
                self.create_attraction_flow()
            elif choice == "7":
                self.view_negotiations()
            elif choice == "8":
                break
            else:
                print("Неверный выбор. Попробуйте снова.")

    def add_product_flow(self):
        name = input("Название товара: ").strip()
        desc = input("Описание: ").strip()
        try:
            price = float(input("Цена: ").strip())
        except ValueError:
            print("Неверное значение цены. Попробуйте снова.")
            return
        try:
            product = self.manager.add_product(self.current_trader.trader_id, {
                "name": name,
                "description": desc,
                "price": price
            })
            print("Товар добавлен в инвентарь продавца!")
            add_now = input("Добавить товар на стенд сразу? (y/n): ").strip().lower()
            if add_now == 'y':
                try:
                    self.current_trader.stand.add_product(product)
                    print("Товар добавлен на стенд!")
                except MarketplaceError as e:
                    print(f"Ошибка при добавлении на стенд: {e}")
        except MarketplaceError as e:
            print(e)

    def view_inventory(self):
        while True:
            print("\n=== Инвентарь продавца ===")
            if not self.current_trader.products:
                print("У вас нет товаров в инвентаре.")
                break

            for i, product in enumerate(self.current_trader.products, 1):
                print(f"{i}. ID: {product.product_id} | {product.name} | Цена: {product.price} руб. | Описание: {product.description}")

            print("\n1. Удалить товар")
            print("2. Изменить цену товара")
            print("3. Назад")
            choice = input("> ").strip()

            if choice == "1":
                idx = input("Введите номер товара для удаления (или 'n' для отмены): ").strip()
                if idx.lower() == 'n':
                    continue
                if idx.isdigit() and 1 <= int(idx) <= len(self.current_trader.products):
                    prod = self.current_trader.products[int(idx)-1]
                    try:
                        self.current_trader.remove_product(prod.product_id)
                        self.current_trader.stand.remove_product(prod.product_id)
                    except MarketplaceError as e:
                        print(e)
                        pass
                    print(f"Товар «{prod.name}» удалён из инвентаря.")
                    self.manager.save_state()
                else:
                    print("Неверный ввод.")

            elif choice == "2":
                idx = input("Введите номер товара для изменения цены (или 'n' для отмены): ").strip()
                if idx.lower() == 'n':
                    continue
                if idx.isdigit() and 1 <= int(idx) <= len(self.current_trader.products):
                    prod = self.current_trader.products[int(idx)-1]
                    new_price_str = input(f"Новая цена для «{prod.name}» (текущая {prod.price}): ").strip()
                    try:
                        new_price = float(new_price_str)
                        self.manager.update_product_price(prod.product_id, new_price)
                        print(f"Цена товара «{prod.name}» изменена на {new_price} руб.")
                        self.manager.save_state()
                    except ValueError:
                        print("Неверное значение цены.")
                    except MarketplaceError as e:
                        print(f"Ошибка: {e}")
                else:
                    print("Неверный ввод.")

            elif choice == "3":
                break

            else:
                print("Неверный выбор. Попробуйте снова.")

    def view_trader_balance(self):
        print(f"\nВаш баланс: {self.current_trader.capital} руб.")

    def manage_stand(self):
        stand = self.current_trader.stand
        while True:
            self._print_stand_management(stand)
            action = input("> ").strip()
            if action == "1":
                self._handle_add_to_stand(stand)
            elif action == "2":
                self._handle_remove_from_stand(stand)
            elif action == "3":
                break
            else:
                print("Неверный выбор. Попробуйте снова.")

    def _print_stand_management(self, stand):
        print("\n=== Управление стендом ===")
        if stand.products:
            print("Товары на стенде:")
            for p in stand.products:
                print(f"[Товар] {p.name} | Цена: {p.price} руб. | ID: {p.product_id}")
        else:
            print("На стенде нет товаров.")
        print("\n1. Добавить товар на стенд")
        print("2. Удалить товар со стенда")
        print("3. Назад")

    def _handle_add_to_stand(self, stand):
        products = [p for p in self.current_trader.products if p not in stand.products]
        if not products:
            print("Нет товаров для добавления.")
            return
        self._show_available_products(products)
        self._add_selected_product(stand, products)

    def _show_available_products(self, products):
        print("Товары, доступные для добавления:")
        for i, p in enumerate(products, 1):
            print(f"{i}. {p.name} | Цена: {p.price} руб.")

    def _add_selected_product(self, stand, products):
        idx = input("Введите номер товара (или 'n' для отмены): ").strip()
        if idx.lower() == 'n':
            return
        if idx.isdigit() and 0 < int(idx) <= len(products):
            try:
                stand.add_product(products[int(idx) - 1])
                print("Товар добавлен на стенд!")
            except MarketplaceError as e:
                print(f"Ошибка: {e}")
        else:
            print("Неверный ввод.")

    def _handle_remove_from_stand(self, stand):
        pid = input("Введите ID товара для удаления (или 'n' для отмены): ").strip()
        if pid.lower() == 'n':
            return
        if pid.isdigit():
            try:
                stand.remove_product(int(pid))
                print("Товар удален со стенда!")
            except MarketplaceError as e:
                print(f"Ошибка: {e}")
        else:
            print("Неверный ввод.")

    def create_ad_flow(self):
        desc = input("Текст рекламы: ").strip()
        try:
            ad = self.manager.create_advertisement(desc)
            if self.current_trader.capital < ad.price:
                print("Недостаточно средств для размещения рекламы!")
                return
            self.current_trader.capital -= ad.price
            ad.stand = {
                "trader_name": self.current_trader.name,
                "location": self.current_trader.stand.location
            }
            print(f"Реклама создана! С вашего счета списано {ad.price} руб.")
        except MarketplaceError as e:
            print(e)

    def create_attraction_flow(self):
        name = input("Название аттракциона: ").strip()
        desc = input("Описание аттракциона: ").strip()
        try:
            price = float(input("Цена билета: ").strip())
        except ValueError:
            print("Неверное значение цены. Попробуйте снова.")
            return
        try:
            self.manager.create_attraction(name, desc, price, self.current_trader)
            print("Аттракцион создан!")
        except MarketplaceError as e:
            print(e)

    def view_negotiations(self):
        found = False
        for req_id, req in list(self.manager.negotiations.items()):
            product = next((p for p in self.manager.get_all_products() if p.product_id == req['product_id']), None)
            if product and product in self.current_trader.products:
                print(f"Товар {req['product_id']}-{product.name} - Предложение {req['price']} руб.")
                found = True
                choice = input("Принять? (y) или отклонить (n): ").strip().lower()
                if choice == 'y':
                    self.manager.accept_negotiation(req_id)
                    print("Запрос принят!")
                elif choice == 'n':
                    del self.manager.negotiations[req_id]
                    print("Запрос отклонён и удалён.")
        if not found:
            print("Нет запросов на торг, относящихся к вашим товарам.")

    def buyer_menu(self):
        while True:
            print(f"\n=== Меню покупателя {self.current_buyer.name} ===")
            print("1. Список стендов")
            print("2. Корзина")
            print("3. Баланс")
            print("4. Аттракционы")
            print("5. Реклама")
            print("6. Назад")
            choice = input("> ").strip()
            if choice == "1":
                self.view_stands()
            elif choice == "2":
                self.manage_cart()
            elif choice == "3":
                print(f"Ваш баланс: {self.current_buyer.balance} руб.")
            elif choice == "4":
                self.view_attractions()
            elif choice == "5":
                self.view_ads()
            elif choice == "6":
                break
            else:
                print("Неверный выбор. Попробуйте снова.")

    def view_stands(self):
        stands = self.manager.get_stands()
        if not stands:
            print("Нет доступных стендов.")
            return

        self._print_stands_list(stands)
        stand = self._select_stand(stands)
        if not stand:
            return

        self._show_stand_products(stand)
        self._handle_stand_actions(stand)

    def _print_stands_list(self, stands):
        print("\n=== Список стендов ===")
        for i, stand in enumerate(stands, 1):
            print(f"{i}. {stand.trader.name} (на стенде {len(stand.products)} товаров)")

    def _select_stand(self, stands):
        idx = input("Введите номер стенда (или 'n' для отмены): ").strip()
        if idx.lower() == 'n':
            return None
        if not idx.isdigit() or not (0 < int(idx) <= len(stands)):
            print("Неверный ввод.")
            return None
        return stands[int(idx) - 1]

    def _show_stand_products(self, stand):
        print(f"\n=== Стенд: {stand.trader.name} ===")
        if not stand.products:
            print("На стенде нет товаров.")
        else:
            for p in stand.products:
                print(f"[Товар] {p.name} | Цена: {p.price} руб. | ID: {p.product_id}")

    def _handle_stand_actions(self, stand):
        action = input("\n1. Предложить цену\n2. Добавить в корзину\n3. Назад\n> ").strip()
        if action == "1":
            self._handle_price_negotiation(stand)
        elif action == "2":
            self._handle_add_to_cart(stand)
        elif action != "3":
            print("Неверный выбор.")

    def _handle_price_negotiation(self, stand):
        pid = input("Введите ID товара: ").strip()
        new_price = input("Ваше предложение: ").strip()
        if pid.isdigit() and new_price.replace('.', '', 1).isdigit():
            product = next((p for p in stand.products if p.product_id == int(pid)), None)
            self._process_price_negotiation(product, pid, new_price)
        else:
            print("Неверный ввод.")

    def _process_price_negotiation(self, product, pid, new_price):
        if not product:
            print("Товар не найден.")
            return
        if self.current_buyer.cart.has_product(product.product_id):
            print("Невозможно предложить цену: товар уже в корзине.")
            return
        for req in self.manager.negotiations.values():
            if req['product_id'] == product.product_id and req['buyer_id'] == self.current_buyer.buyer_id:
                print(" Вы уже отправили предложение по этому товару. Дождитесь ответа продавца.")
                return
        try:
            self.manager.create_negotiation(self.current_buyer.buyer_id, product.product_id, float(new_price))
            print("Предложение отправлено!")
        except MarketplaceError as e:
            print(f"Ошибка: {e}")

    def _handle_add_to_cart(self, stand):
        pid = input("Введите ID товара для добавления в корзину: ").strip()
        if pid.isdigit():
            product = next((p for p in stand.products if p.product_id == int(pid)), None)
            self._add_product_to_cart(product, pid)
        else:
            print("Неверный ввод.")

    def _add_product_to_cart(self, product, pid):
        if not product:
            print("Товар не найден.")
            return
        if self.current_buyer.cart.has_product(product.product_id):
            print("Товар уже был добавлен в корзину.")
            return
        self.current_buyer.cart.negotiated_prices.pop(product.product_id, None)
        try:
            self.current_buyer.cart.add_to_cart(product)
            print("Товар добавлен в корзину!")
        except MarketplaceError as e:
            print(f"Ошибка: {e}")

    def manage_cart(self):
        cart = self.current_buyer.cart
        while True:
            print("\n=== Корзина ===")
            if not cart.cart_items:
                print("В корзине нет товаров.")
                return

            for i, p in enumerate(cart.cart_items, 1):
                price = cart.negotiated_prices.get(p.product_id, p.price)
                print(f"{i}. {p.name} | Цена: {price} руб. | ID: {p.product_id}")

            total = cart.get_total_price()
            print(f"Общая сумма: {total} руб.")

            print("\n1. Оплатить")
            print("2. Удалить товар из корзины")
            print("3. Очистить корзину")
            print("4. Назад")
            choice = input("> ").strip()

            if choice == "1":
                if self.current_buyer.balance >= total:
                    self.current_buyer.balance -= total
                    for product in cart.cart_items:
                        purchase_price = cart.negotiated_prices.get(product.product_id, product.price)
                        seller = next((t for t in self.manager.traders if product in t.products), None)
                        if seller:
                            seller.capital += purchase_price
                    print("Оплата прошла успешно!")
                    cart.clear_cart()
                    self.manager.save_state()
                    return
                else:
                    print("Недостаточно средств!")

            elif choice == "2":
                idx = input("Введите номер товара для удаления (или 'n' для отмены): ").strip()
                if idx.lower() == 'n':
                    continue
                if idx.isdigit() and 1 <= int(idx) <= len(cart.cart_items):
                    prod = cart.cart_items[int(idx) - 1]
                    try:
                        cart.remove_from_cart(prod)
                        print(f"Товар «{prod.name}» удалён из корзины.")
                        self.manager.save_state()
                    except MarketplaceError as e:
                        print(f"Ошибка: {e}")
                else:
                    print("Неверный ввод.")

            elif choice == "3":
                cart.clear_cart()
                print("Корзина очищена!")
                self.manager.save_state()
                return

            elif choice == "4":
                return

            else:
                print("Неверный выбор. Попробуйте снова.")

    def view_attractions(self):
        if not self.manager.attractions:
            print("Нет доступных аттракционов.")
            return
        print("\n=== Список аттракционов ===")
        for i, attraction in enumerate(self.manager.attractions, 1):
            print(f"{i}. {attraction.name} | Цена билета: {attraction.ticket_price} руб.")
        idx = input("Введите номер аттракциона для посещения (или 'n' для отмены): ").strip()
        if idx.lower() == 'n':
            return
        if not idx.isdigit() or not (0 < int(idx) <= len(self.manager.attractions)):
            print("Неверный ввод.")
            return
        selected = self.manager.attractions[int(idx) - 1]
        if self.current_buyer.balance >= selected.ticket_price:
            self.current_buyer.balance -= selected.ticket_price
            seller = next((t for t in self.manager.traders if t.trader_id == selected.seller_id), None)
            if seller:
                seller.capital += selected.ticket_price
            print("Вы успешно посетили аттракцион!")
        else:
            print("Недостаточно средств!")

    def view_ads(self):
        ads = self.manager.get_active_ads()
        if not ads:
            print("Нет активной рекламы.")
            return
        print("\n=== Реклама ===")
        for ad in ads:
            if ad.stand:
                print(f"Реклама: {ad.description} [{ad.stand.get('location', '')}]")
            else:
                print(f"Реклама: {ad.description}")

if __name__ == "__main__":
    cli = CLI()
    cli.main_menu()