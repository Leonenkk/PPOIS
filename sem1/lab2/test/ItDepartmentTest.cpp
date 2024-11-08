#include "gtest/gtest.h"
#include "ItDepartment.h"
#include "Employee.h"

class ItDepartmentTest : public ::testing::Test {
protected:
    ItDepartment* itDepartment;
    std::vector<Employee> employees;

    void SetUp() override {
        employees.push_back(Employee("Alice", 30, 5000, 5, 1));
        employees.push_back(Employee("Bob", 40, 6000, 10, 2));
        itDepartment = new ItDepartment(employees, 10);
    }

    void TearDown() override {
        delete itDepartment;
    }
};

TEST_F(ItDepartmentTest, GetAndSetCountOfComputers) {
    EXPECT_EQ(itDepartment->getCountOfComputers(), 10);
    itDepartment->setCountOfComputers(15);
    EXPECT_EQ(itDepartment->getCountOfComputers(), 15);
}

TEST_F(ItDepartmentTest, Constructor) {
    ItDepartment newItDepartment(employees, 20);
    EXPECT_EQ(newItDepartment.getCountOfComputers(), 20);
    EXPECT_EQ(newItDepartment.getEmployees().size(), 2);
}