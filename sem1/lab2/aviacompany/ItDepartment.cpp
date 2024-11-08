#include "ItDepartment.h"

ItDepartment::ItDepartment(const std::vector<Employee>& employees, int countOfComputers)
    : Department(employees), countOfComputers(countOfComputers) {}

int ItDepartment::getCountOfComputers() const {
    return countOfComputers;
}

void ItDepartment::setCountOfComputers(int countOfComputers) {
    this->countOfComputers = countOfComputers;
}
