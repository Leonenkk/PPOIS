#include "Pharmacy.h"
#include "Prescription.h"
#include <iostream>

Pharmacy::Pharmacy(const std::string& pharmacyID, const std::string& location)
    : pharmacyID(pharmacyID), location(location) {}

void Pharmacy::dispenseMedication(const Prescription& prescription) {
    std::cout << "Dispensing medications for Prescription ID: " << prescription.getMedications().size() << " medications." << std::endl;
    for (const auto& medication : prescription.getMedications()) {
        if (inventory.find(medication) != inventory.end() && inventory[medication] > 0) {
            inventory[medication]--;
            std::cout << "Dispensed " << medication << std::endl;
        } else {
            std::cout << "Medication " << medication << " is out of stock." << std::endl;
        }
    }
}

void Pharmacy::restock(const std::string& medication, int quantity) {
    inventory[medication] += quantity;
    std::cout << "Restocked " << quantity << " units of " << medication << std::endl;
}

void Pharmacy::checkInventory(const std::string& medication) const {
    if (inventory.find(medication) != inventory.end()) {
        std::cout << "Inventory of " << medication << ": " << inventory.at(medication) << " units" << std::endl;
    } else {
        std::cout << "Medication " << medication << " is not available in the inventory." << std::endl;
    }
}

void Pharmacy::receivePrescription(Prescription* prescription) {
    prescriptions.push_back(prescription);
    std::cout << "Pharmacy received Prescription with medications: ";
    for (const auto& medication : prescription->getMedications()) {
        std::cout << medication << " ";
    }
    std::cout << std::endl;
}

const std::string& Pharmacy::getLocation() const {
    return location;
}

const std::unordered_map<std::string, int>& Pharmacy::getInventory() const {
    return inventory;
}

const std::vector<Prescription*>& Pharmacy::getPrescriptions() const {
    return prescriptions;
}
