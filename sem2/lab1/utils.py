import re

class MarketplaceError(Exception):
    pass


def is_valid_contact(contact: str) -> bool:
    email_regex = re.compile(r"^[^@]+@[^@]+\.[^@]+$")
    phone_regex = re.compile(r'^\+375(17|25|29|33|44)\d{7}$')
    return bool(email_regex.fullmatch(contact)) or bool(phone_regex.fullmatch(contact))
