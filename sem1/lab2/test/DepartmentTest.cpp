#include "gtest/gtest.h"
#include "Department.h"
#include "Employee.h"

class DepartmentTest : public ::testing::Test {
protected:
    Department* department;
    std::vector<Employee> employees;

    void SetUp() override {
        employees.push_back(Employee("Alice", 30, 5000, 5, 1));
        employees.push_back(Employee("Bob", 40, 6000, 10, 2));
        department = new Department(employees);
    }

    void TearDown() override {
        delete department;
    }
};

TEST_F(DepartmentTest, ConstructorAndGetters) {
    EXPECT_EQ(department->getCountOfEmployees(), 2);
    EXPECT_EQ(department->getEmployees().size(), 2);
    EXPECT_EQ(department->getTasks().size(), 0);
}

TEST_F(DepartmentTest, SetEmployees) {
    std::vector<Employee> newEmployees;
    newEmployees.push_back(Employee("Charlie", 35, 7000, 8, 3));
    department->setEmployees(newEmployees);

    EXPECT_EQ(department->getCountOfEmployees(), 1);
    EXPECT_EQ(department->getEmployees().size(), 1);
}

TEST_F(DepartmentTest, AddEmployee) {
    Employee newEmployee("Charlie", 35, 7000, 8, 3);
    department->addEmployee(newEmployee);

    EXPECT_EQ(department->getCountOfEmployees(), 3);
    EXPECT_EQ(department->getEmployees().size(), 3);
}
TEST_F(DepartmentTest, RemoveEmployee) {
    department->removeEmployee(1);

    EXPECT_EQ(department->getCountOfEmployees(), 1);
    EXPECT_EQ(department->getEmployees().size(), 1);
    EXPECT_EQ(department->getEmployees()[0].getEmployeeId(), 2);
}

TEST_F(DepartmentTest, AddTask) {
    department->addTask("Complete budget analysis");

    EXPECT_EQ(department->getTasks().size(), 1);
    EXPECT_EQ(department->getTasks()[0], "Complete budget analysis");
}

TEST_F(DepartmentTest, RemoveTask) {
    department->addTask("Complete budget analysis");
    department->removeTask("Complete budget analysis");

    EXPECT_EQ(department->getTasks().size(), 0);
}

TEST_F(DepartmentTest, ToString) {
    std::string departmentStr = department->toString();
    EXPECT_TRUE(departmentStr.find("Department") != std::string::npos);
    EXPECT_TRUE(departmentStr.find("employees=2") != std::string::npos);
    EXPECT_TRUE(departmentStr.find("tasks=0") != std::string::npos);
}