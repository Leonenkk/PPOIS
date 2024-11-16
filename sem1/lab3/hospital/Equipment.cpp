#include "Equipment.h"
#include <iostream>
#include <ctime>

Equipment::Equipment(const std::string& equipmentID, const std::string& name, const std::string& type, const std::tm& maintenanceDate)
    : equipmentID(equipmentID), name(name), type(type), maintenanceDate(maintenanceDate) {}

void Equipment::scheduleMaintenance(const std::tm& date) {
    maintenanceDate = date;
    std::cout << "Scheduled maintenance for equipment " << name << " on "
              << date.tm_mday << "/" << (date.tm_mon + 1) << "/" << (date.tm_year + 1900) << std::endl;
}

void Equipment::checkStatus() const {
    std::cout << "Equipment: " << name << std::endl;
    std::cout << "Type: " << type << std::endl;
    std::cout << "Last maintenance date: " << maintenanceDate.tm_mday << "/"
              << (maintenanceDate.tm_mon + 1) << "/" << (maintenanceDate.tm_year + 1900) << std::endl;
}

// Геттеры
std::string Equipment::getEquipmentID() const {
    return equipmentID;
}

std::string Equipment::getName() const {
    return name;
}

std::string Equipment::getType() const {
    return type;
}

std::tm Equipment::getMaintenanceDate() const {
    return maintenanceDate;
}
