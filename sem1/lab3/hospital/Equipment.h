#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <string>
#include <ctime>  // Для работы с датами

class Equipment {
private:
    std::string equipmentID;
    std::string name;
    std::string type;
    std::tm maintenanceDate;

public:
    Equipment(const std::string& equipmentID, const std::string& name, const std::string& type, const std::tm& maintenanceDate);

    void scheduleMaintenance(const std::tm& date);
    void checkStatus() const;

    std::string getEquipmentID() const;
    std::string getName() const;
    std::string getType() const;
    std::tm getMaintenanceDate() const;
};

#endif
