#ifndef ITDEPARTMENT_H
#define ITDEPARTMENT_H

#include "Department.h"
#include <vector>

class ItDepartment : public Department {
private:
    int countOfComputers;

public:
    ItDepartment(const std::vector<Employee>& employees, int countOfComputers);

    int getCountOfComputers() const;
    void setCountOfComputers(int countOfComputers);
};

#endif // ITDEPARTMENT_H
