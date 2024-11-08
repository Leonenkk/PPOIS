#include "gtest/gtest.h"
#include "LogisticsDepartment.h"
#include "Employee.h"
#include "Aircraft.h"
#include "TechnicalDepartment.h"

class LogisticsDepartmentTest : public ::testing::Test {
protected:
    LogisticsDepartment* logisticsDepartment;
    TechnicalDepartment* technicalDepartment;
    std::vector<Employee> employees;
    std::vector<Aircraft> aircraftOnBase;
    std::vector<Aircraft> aircraftInTransit;

    void SetUp() override {
        employees.push_back(Employee("Alice", 30, 5000, 5, 1));
        employees.push_back(Employee("Bob", 40, 6000, 10, 2));

        Aircraft aircraft1("White", "Boeing 737", "TurboJet", 900, 10000, 25000, 2);
        Aircraft aircraft2("Blue", "Airbus A320", "JetEngine", 850, 8000, 22000, 2);

        aircraftOnBase.push_back(aircraft1);
        aircraftOnBase.push_back(aircraft2);

        technicalDepartment = new TechnicalDepartment(employees, {});
        logisticsDepartment = new LogisticsDepartment(employees, aircraftOnBase, aircraftInTransit, technicalDepartment);
    }

    void TearDown() override {
        delete logisticsDepartment;
        delete technicalDepartment;
    }
};

TEST_F(LogisticsDepartmentTest, ConstructorAndGetters) {
    EXPECT_EQ(logisticsDepartment->getAircraftOnBase().size(), 2);
    EXPECT_EQ(logisticsDepartment->getAircraftInTransit().size(), 0);
}

TEST_F(LogisticsDepartmentTest, SendAircraftToTransit) {
    logisticsDepartment->sendAircraftToTransit();

    EXPECT_EQ(logisticsDepartment->getAircraftOnBase().size(), 1);
    EXPECT_EQ(logisticsDepartment->getAircraftInTransit().size(), 1);
}

TEST_F(LogisticsDepartmentTest, ReturnAircraftToBase) {
    logisticsDepartment->sendAircraftToTransit();
    logisticsDepartment->returnAircraftToBase();

    EXPECT_EQ(logisticsDepartment->getAircraftOnBase().size(), 2);
    EXPECT_EQ(logisticsDepartment->getAircraftInTransit().size(), 0);
}

TEST_F(LogisticsDepartmentTest, SendAircraftToTechnicalDepartment) {
    Aircraft aircraftToRepair = logisticsDepartment->getAircraftOnBase()[0];
    logisticsDepartment->sendAircraftToTechnicalDepartment(aircraftToRepair.getModel());

    EXPECT_EQ(technicalDepartment->getAircraftsOnRepair().size(), 1);
    EXPECT_EQ(logisticsDepartment->getAircraftOnBase().size(), 1);
    EXPECT_EQ(logisticsDepartment->getAircraftInTransit().size(), 0);
}

TEST_F(LogisticsDepartmentTest, SendAircraftToTechnicalDepartmentWhenAircraftNotFound) {
    logisticsDepartment->sendAircraftToTechnicalDepartment("NonExistentModel");

    EXPECT_EQ(technicalDepartment->getAircraftsOnRepair().size(), 0);
    EXPECT_EQ(logisticsDepartment->getAircraftOnBase().size(), 2);
}