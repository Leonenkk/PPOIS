#ifndef MEDICATION_H
#define MEDICATION_H

#include <string>
#include <ctime>  // Для работы с датами

class Medication {
private:
    std::string medicationID;
    std::string name;
    std::string type;
    double price;
    std::tm expiryDate;

public:
    Medication(const std::string& medicationID, const std::string& name, const std::string& type,
               double price, const std::tm& expiryDate);

    double getPrice() const;
    bool checkExpiry() const;

    std::string getMedicationID() const;
    std::string getName() const;
    std::string getType() const;
    std::tm getExpiryDate() const;

    void setExpiryDate(const std::tm& expiryDate);
};

#endif
