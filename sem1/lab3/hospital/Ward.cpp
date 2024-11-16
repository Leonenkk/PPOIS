#include "Ward.h"
#include "Nurse.h"
#include "Patient.h"
#include <iostream>


Ward::Ward(const std::string& wardID, const std::string& name, const std::string& type, int capacity)
    : wardID(wardID), name(name), type(type), capacity(capacity), occupancy(0) {}

void Ward::admitPatient(Patient* patient) {
    if (checkAvailability()) {
        occupancy++;
        std::cout << "Patient " << patient->getFullName() << " admitted to ward " << name << std::endl;
    } else {
        std::cout << "No available space in ward " << name << " for patient " << patient->getFullName() << std::endl;
    }
}

void Ward::dischargePatient(Patient* patient) {
    if (occupancy > 0) {
        occupancy--;
        std::cout << "Patient " << patient->getFullName() << " discharged from ward " << name << std::endl;
    } else {
        std::cout << "No patients to discharge from ward " << name << std::endl;
    }
}

bool Ward::checkAvailability() const {
    return occupancy < capacity;
}

void Ward::assignNurse(Nurse* nurse) {
    nurses.push_back(nurse);
    std::cout << "Nurse " << nurse->getFullName() << " assigned to ward " << name << std::endl;
}

std::string Ward::getWardName() const {
    return name;
}
