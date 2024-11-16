#include "Person.h"

Person::Person(const std::string& name, const std::string& surname, int age,
               const std::string& gender, const std::string& address, const std::string& phone)
    : name(name), surname(surname), age(age), gender(gender), address(address), phone(phone) {}

std::string Person::getFullName() const {
    return name + " " + surname;
}

std::string Person::getContactInfo() const {
    return "Address: " + address + ", Phone: " + phone;
}

void Person::setAddress(const std::string& newAddress) {
    address = newAddress;
}

void Person::setPhone(const std::string& newPhone) {
    phone = newPhone;
}
