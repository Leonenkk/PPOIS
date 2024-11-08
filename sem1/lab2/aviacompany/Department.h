#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <vector>
#include <string>
#include "Employee.h"

class Department {
protected:
    std::vector<Employee> employees;
    int countOfEmployees;
    std::vector<std::string> tasks;

public:
    explicit Department(const std::vector<Employee>& employees);

    std::vector<Employee> getEmployees() const;
    void setEmployees(const std::vector<Employee>& employees);

    int getCountOfEmployees() const;

    std::vector<std::string> getTasks() const;
    void addTasks(const std::vector<std::string>& tasks);

    void addEmployee(const Employee& employee);
    void removeEmployee(int id);

    void addTask(const std::string& task);
    void removeTask(const std::string& task);

    std::string toString() const;
};

#endif // DEPARTMENT_H
