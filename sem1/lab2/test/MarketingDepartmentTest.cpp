#include "gtest/gtest.h"
#include "MarketingDepartment.h"
#include "Employee.h"
#include "FinanceDepartment.h"

class MarketingDepartmentTest : public ::testing::Test {
protected:
    MarketingDepartment* marketingDepartment;
    FinanceDepartment* financeDepartment;
    std::vector<Employee> employees;
    std::vector<std::string> promotions;
    std::vector<std::string> areasOfAnalysis;

    void SetUp() override {
        employees.push_back(Employee("Alice", 30, 5000, 5, 1));
        employees.push_back(Employee("Bob", 40, 6000, 10, 2));

        promotions.push_back("Promo1");
        promotions.push_back("Promo2");

        areasOfAnalysis.push_back("Area1");
        areasOfAnalysis.push_back("Area2");

        marketingDepartment = new MarketingDepartment(employees, promotions, areasOfAnalysis);
        financeDepartment = new FinanceDepartment(employees, 0);
    }

    void TearDown() override {
        delete marketingDepartment;
        delete financeDepartment;
    }
};

TEST_F(MarketingDepartmentTest, ConstructorAndGetters) {
    EXPECT_EQ(marketingDepartment->getPromotions().size(), 2);
    EXPECT_EQ(marketingDepartment->getPromotions()[0], "Promo1");
    EXPECT_EQ(marketingDepartment->getPromotions()[1], "Promo2");

    EXPECT_EQ(marketingDepartment->getAreasOfAnalysis().size(), 2);
    EXPECT_EQ(marketingDepartment->getAreasOfAnalysis()[0], "Area1");
    EXPECT_EQ(marketingDepartment->getAreasOfAnalysis()[1], "Area2");
}

TEST_F(MarketingDepartmentTest, SetFinanceDepartment) {
    marketingDepartment->setFinanceDepartment(financeDepartment);
}

TEST_F(MarketingDepartmentTest, SendMoneyToFinanceDepartment) {
    marketingDepartment->setFinanceDepartment(financeDepartment);
    int initialBudget = financeDepartment->getBudget();
    marketingDepartment->sendMoneyToFinanceDepartment(1000);
    EXPECT_EQ(financeDepartment->getBudget(), initialBudget + 1000);
}

TEST_F(MarketingDepartmentTest, SendMoneyToFinanceDepartmentWhenNull) {
    marketingDepartment->sendMoneyToFinanceDepartment(1000);
    EXPECT_EQ(financeDepartment->getBudget(), 0);
}
