#ifndef TECHNICALDEPARTMENT_H
#define TECHNICALDEPARTMENT_H

#include "Department.h"
#include "Aircraft.h"
#include <vector>

class TechnicalDepartment : public Department {
private:
    std::vector<Aircraft> aircraftsOnRepair;

public:
    TechnicalDepartment(const std::vector<Employee>& employees, const std::vector<Aircraft>& aircraftsOnRepair);

    std::vector<Aircraft> getAircraftsOnRepair() const;
    void setAircraftsOnRepair(const std::vector<Aircraft>& aircraftsOnRepair);

    void addAircraftToRepair(const Aircraft& aircraft);
};

#endif

