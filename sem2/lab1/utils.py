import re

class MarketplaceError(Exception):
    pass


def is_valid_contact(contact: str) -> bool:
    email_regex = re.compile(r"^[^@]+@[^@]+\.[^@]+$")
    phone_regex = re.compile(r"^\+?[\d\s\-\(\)]{7,}$")
    return bool(email_regex.fullmatch(contact)) or bool(phone_regex.fullmatch(contact))
