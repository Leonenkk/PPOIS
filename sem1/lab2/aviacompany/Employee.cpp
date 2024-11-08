#include "Employee.h"

Employee::Employee(const std::string& name, int age, int salary, int experience, int employeeId)
    : People(name, age), salary(salary), experience(experience), employeeId(employeeId) {}

int Employee::getSalary() const {
    return salary;
}

void Employee::setSalary(int salary) {
    this->salary = salary;
}

int Employee::getExperience() const {
    return experience;
}

void Employee::setExperience(int experience) {
    this->experience = experience;
}


int Employee::getEmployeeId() const {
    return employeeId;
}


void Employee::setEmployeeId(int employeeId) {
    this->employeeId = employeeId;
}

void Employee::addSalary(int allowance) {
    salary += allowance;
}
