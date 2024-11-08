#include "LogisticsDepartment.h"
#include <algorithm>

LogisticsDepartment::LogisticsDepartment(const std::vector<Employee>& employees,
                                         const std::vector<Aircraft>& aircraftOnBase,
                                         const std::vector<Aircraft>& aircraftInTransit,
                                         TechnicalDepartment* technicalDepartment)
    : Department(employees),
      aircraftOnBase(aircraftOnBase),
      aircraftInTransit(aircraftInTransit),
      technicalDepartment(technicalDepartment) {}

std::vector<Aircraft> LogisticsDepartment::getAircraftOnBase() const {
    return aircraftOnBase;
}

void LogisticsDepartment::setAircraftOnBase(const std::vector<Aircraft>& aircraftOnBase) {
    this->aircraftOnBase = aircraftOnBase;
}

std::vector<Aircraft> LogisticsDepartment::getAircraftInTransit() const {
    return aircraftInTransit;
}

void LogisticsDepartment::setAircraftInTransit(const std::vector<Aircraft>& aircraftInTransit) {
    this->aircraftInTransit = aircraftInTransit;
}

void LogisticsDepartment::sendAircraftToTransit() {
    if (!aircraftOnBase.empty()) {
        aircraftInTransit.push_back(aircraftOnBase.back());
        aircraftOnBase.pop_back();
    }
}

void LogisticsDepartment::returnAircraftToBase() {
    if (!aircraftInTransit.empty()) {
        aircraftOnBase.push_back(aircraftInTransit.back());
        aircraftInTransit.pop_back();
    }
}

void LogisticsDepartment::sendAircraftToTechnicalDepartment(const std::string& model) {
    auto it = std::find_if(aircraftOnBase.begin(), aircraftOnBase.end(),
                           [&model](const Aircraft& aircraft) { return aircraft.getModel() == model; });

    if (it != aircraftOnBase.end() && technicalDepartment) {
        technicalDepartment->addAircraftToRepair(*it);
        aircraftOnBase.erase(it);
    }
}