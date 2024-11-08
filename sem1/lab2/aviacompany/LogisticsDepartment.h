#ifndef LOGISTICSDEPARTMENT_H
#define LOGISTICSDEPARTMENT_H

#include <vector>
#include "Department.h"
#include "Aircraft.h"
#include "TechnicalDepartment.h"

class LogisticsDepartment : public Department {
private:
    std::vector<Aircraft> aircraftOnBase;
    std::vector<Aircraft> aircraftInTransit;
    TechnicalDepartment* technicalDepartment;

public:
    LogisticsDepartment(const std::vector<Employee>& employees,
                        const std::vector<Aircraft>& aircraftOnBase,
                        const std::vector<Aircraft>& aircraftInTransit,
                        TechnicalDepartment* technicalDepartment = nullptr);

    std::vector<Aircraft> getAircraftOnBase() const;
    void setAircraftOnBase(const std::vector<Aircraft>& aircraftOnBase);

    std::vector<Aircraft> getAircraftInTransit() const;
    void setAircraftInTransit(const std::vector<Aircraft>& aircraftInTransit);

    void sendAircraftToTransit();
    void returnAircraftToBase();
    void sendAircraftToTechnicalDepartment(const std::string& model);
};

#endif