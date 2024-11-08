#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "People.h"

class Employee : public People {
private:
    int salary;
    int experience;
    int employeeId;

public:
    Employee(const std::string& name, int age, int salary, int experience, int employeeId);

    int getSalary() const;
    void setSalary(int salary);

    int getExperience() const;
    void setExperience(int experience);

    int getEmployeeId() const;
    void setEmployeeId(int employeeId);

    void addSalary(int allowance);
};

#endif // EMPLOYEE_H
