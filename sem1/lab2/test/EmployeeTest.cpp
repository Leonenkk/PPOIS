#include "gtest/gtest.h"
#include "Employee.h"
#include "People.h"

class EmployeeTest : public ::testing::Test {
protected:
    Employee* employee;

    void SetUp() override {
        employee = new Employee("Alice", 30, 5000, 5, 1);
    }

    void TearDown() override {
        delete employee;
    }
};

TEST_F(EmployeeTest, GetAndSetSalary) {
    EXPECT_EQ(employee->getSalary(), 5000);
    employee->setSalary(6000);
    EXPECT_EQ(employee->getSalary(), 6000);
}

TEST_F(EmployeeTest, AddSalary) {
    employee->addSalary(500);
    EXPECT_EQ(employee->getSalary(), 5500);
}

TEST_F(EmployeeTest, GetAndSetExperience) {
    EXPECT_EQ(employee->getExperience(), 5);
    employee->setExperience(10);
    EXPECT_EQ(employee->getExperience(), 10);
}

TEST_F(EmployeeTest, GetAndSetEmployeeId) {
    EXPECT_EQ(employee->getEmployeeId(), 1);
    employee->setEmployeeId(2);
    EXPECT_EQ(employee->getEmployeeId(), 2);
}

TEST_F(EmployeeTest, Constructor) {
    Employee newEmployee("Bob", 40, 7000, 8, 3);
    EXPECT_EQ(newEmployee.getSalary(), 7000);
    EXPECT_EQ(newEmployee.getExperience(), 8);
    EXPECT_EQ(newEmployee.getEmployeeId(), 3);
}