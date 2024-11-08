#include "Department.h"
#include <algorithm>

Department::Department(const std::vector<Employee>& employees)
    : employees(employees), countOfEmployees(employees.size()) {}

std::vector<Employee> Department::getEmployees() const { return employees; }

void Department::setEmployees(const std::vector<Employee>& employees) {
    this->employees = employees;
    countOfEmployees = employees.size();
}

int Department::getCountOfEmployees() const { return countOfEmployees; }

std::vector<std::string> Department::getTasks() const { return tasks; }

void Department::addTasks(const std::vector<std::string>& tasks) {
    this->tasks.insert(this->tasks.end(), tasks.begin(), tasks.end());
}

void Department::addEmployee(const Employee& employee) {
    employees.push_back(employee);
    countOfEmployees++;
}

void Department::removeEmployee(int id) {
    auto it = std::remove_if(employees.begin(), employees.end(),
                             [id](const Employee& emp) { return emp.getEmployeeId() == id; });
    if (it != employees.end()) {
        employees.erase(it, employees.end());
        countOfEmployees--;
    }
}

void Department::addTask(const std::string& task) { tasks.push_back(task); }

void Department::removeTask(const std::string& task) {
    tasks.erase(std::remove(tasks.begin(), tasks.end(), task), tasks.end());
}

std::string Department::toString() const {
    return "Department [employees=" + std::to_string(countOfEmployees) + ", tasks=" + std::to_string(tasks.size()) + "]";
}
