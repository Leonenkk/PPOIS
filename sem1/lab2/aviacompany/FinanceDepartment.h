#ifndef FINANCEDEPARTMENT_H
#define FINANCEDEPARTMENT_H

#include "Department.h"
#include <vector>

class FinanceDepartment : public Department {
private:
    int budget;

public:
    FinanceDepartment(const std::vector<Employee>& employees, int budget);

    int getBudget() const;
    void setBudget(int budget);

    void addMoneyToBudget(int amount);
};

#endif
