#ifndef PHARMACY_H
#define PHARMACY_H

#include <string>
#include <unordered_map>
#include <vector>
#include "Prescription.h"
class Prescription;
class Pharmacy {
private:
    std::string pharmacyID;
    std::unordered_map<std::string, int> inventory;
    std::string location;
    std::vector<Prescription*> prescriptions;  // Ассоциация с рецептами

public:
    Pharmacy(const std::string& pharmacyID, const std::string& location);

    void dispenseMedication(const Prescription& prescription);
    void restock(const std::string& medication, int quantity);
    void checkInventory(const std::string& medication) const;
    void receivePrescription(Prescription* prescription);

    const std::string& getLocation() const;
    const std::unordered_map<std::string, int>& getInventory() const;
    const std::vector<Prescription*>& getPrescriptions() const;
};

#endif
