#include "gtest/gtest.h"
#include "FinanceDepartment.h"
#include "Employee.h"

class FinanceDepartmentTest : public ::testing::Test {
protected:
    FinanceDepartment* financeDepartment;
    std::vector<Employee> employees;

    void SetUp() override {
        employees.push_back(Employee("Alice", 30, 5000, 5, 1));
        employees.push_back(Employee("Bob", 40, 6000, 10, 2));
        financeDepartment = new FinanceDepartment(employees, 10000);
    }

    void TearDown() override {
        delete financeDepartment;
    }
};

TEST_F(FinanceDepartmentTest, GetAndSetBudget) {
    EXPECT_EQ(financeDepartment->getBudget(), 10000);
    financeDepartment->setBudget(15000);
    EXPECT_EQ(financeDepartment->getBudget(), 15000);
}

TEST_F(FinanceDepartmentTest, AddMoneyToBudget) {
    financeDepartment->addMoneyToBudget(5000);
    EXPECT_EQ(financeDepartment->getBudget(), 15000);
    financeDepartment->addMoneyToBudget(2000);
    EXPECT_EQ(financeDepartment->getBudget(), 17000);
}

TEST_F(FinanceDepartmentTest, Constructor) {
    FinanceDepartment newFinanceDepartment(employees, 20000);
    EXPECT_EQ(newFinanceDepartment.getBudget(), 20000);
    EXPECT_EQ(newFinanceDepartment.getEmployees().size(), 2);
}