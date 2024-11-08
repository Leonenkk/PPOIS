#include "TechnicalDepartment.h"

TechnicalDepartment::TechnicalDepartment(const std::vector<Employee>& employees, const std::vector<Aircraft>& aircraftsOnRepair)
    : Department(employees), aircraftsOnRepair(aircraftsOnRepair) {}

std::vector<Aircraft> TechnicalDepartment::getAircraftsOnRepair() const {
    return aircraftsOnRepair;
}

void TechnicalDepartment::setAircraftsOnRepair(const std::vector<Aircraft>& aircraftsOnRepair) {
    this->aircraftsOnRepair = aircraftsOnRepair;
}

void TechnicalDepartment::addAircraftToRepair(const Aircraft& aircraft) {
    aircraftsOnRepair.push_back(aircraft);
}
