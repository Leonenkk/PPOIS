#include "Medication.h"
#include <iostream>

Medication::Medication(const std::string& medicationID, const std::string& name, const std::string& type,
                       double price, const std::tm& expiryDate)
    : medicationID(medicationID), name(name), type(type), price(price), expiryDate(expiryDate) {}

double Medication::getPrice() const {
    return price;
}

bool Medication::checkExpiry() const {
    std::time_t currentTime = std::time(nullptr);
    std::tm* currentDate = std::localtime(&currentTime);

    if (std::difftime(std::mktime(currentDate), std::mktime(const_cast<std::tm*>(&expiryDate))) > 0) {
        return false;
    }
    return true;
}

std::string Medication::getMedicationID() const {
    return medicationID;
}

std::string Medication::getName() const {
    return name;
}

std::string Medication::getType() const {
    return type;
}

std::tm Medication::getExpiryDate() const {
    return expiryDate;
}

void Medication::setExpiryDate(const std::tm& expiryDate) {
    this->expiryDate = expiryDate;
}
