#include "FinanceDepartment.h"

FinanceDepartment::FinanceDepartment(const std::vector<Employee>& employees, int budget)
    : Department(employees), budget(budget) {}

int FinanceDepartment::getBudget() const {
    return budget;
}

void FinanceDepartment::setBudget(int budget) {
    this->budget = budget;
}

void FinanceDepartment::addMoneyToBudget(int amount) {
    budget += amount;
}
