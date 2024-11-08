#include "gtest/gtest.h"
#include "TechnicalDepartment.h"
#include "Employee.h"
#include "Aircraft.h"

class TechnicalDepartmentTest : public ::testing::Test {
protected:
    TechnicalDepartment* technicalDepartment;
    std::vector<Employee> employees;
    std::vector<Aircraft> aircraftsOnRepair;

    void SetUp() override {
        employees.push_back(Employee("Alice", 30, 5000, 5, 1));
        employees.push_back(Employee("Bob", 40, 6000, 10, 2));

        aircraftsOnRepair.push_back(Aircraft("Red", "ModelA", "EngineA", 500, 2000, 3000, 2));
        aircraftsOnRepair.push_back(Aircraft("Blue", "ModelB", "EngineB", 600, 2500, 3500, 4));

        technicalDepartment = new TechnicalDepartment(employees, aircraftsOnRepair);
    }

    void TearDown() override {
        delete technicalDepartment;
    }
};

TEST_F(TechnicalDepartmentTest, ConstructorAndGetters) {
    EXPECT_EQ(technicalDepartment->getAircraftsOnRepair().size(), 2);
    EXPECT_EQ(technicalDepartment->getAircraftsOnRepair()[0].getModel(), "ModelA");
    EXPECT_EQ(technicalDepartment->getAircraftsOnRepair()[1].getModel(), "ModelB");
}

TEST_F(TechnicalDepartmentTest, SetAircraftsOnRepair) {
    std::vector<Aircraft> newAircraftsOnRepair;
    newAircraftsOnRepair.push_back(Aircraft("Red", "ModelC", "EngineC", 700, 3000, 4000, 6));

    technicalDepartment->setAircraftsOnRepair(newAircraftsOnRepair);

    EXPECT_EQ(technicalDepartment->getAircraftsOnRepair().size(), 1);
    EXPECT_EQ(technicalDepartment->getAircraftsOnRepair()[0].getModel(), "ModelC");
}

TEST_F(TechnicalDepartmentTest, AddAircraftToRepair) {
    Aircraft newAircraft("Green", "ModelD", "EngineD", 800, 3500, 5000, 8);
    technicalDepartment->addAircraftToRepair(newAircraft);

    EXPECT_EQ(technicalDepartment->getAircraftsOnRepair().size(), 3);
    EXPECT_EQ(technicalDepartment->getAircraftsOnRepair()[2].getModel(), "ModelD");
}

TEST_F(TechnicalDepartmentTest, AddAircraftToRepairWhenEmpty) {
    std::vector<Aircraft> emptyAircrafts;
    technicalDepartment->setAircraftsOnRepair(emptyAircrafts);

    Aircraft newAircraft("Yellow", "ModelE", "EngineE", 900, 4000, 6000, 10);
    technicalDepartment->addAircraftToRepair(newAircraft);

    EXPECT_EQ(technicalDepartment->getAircraftsOnRepair().size(), 1);
    EXPECT_EQ(technicalDepartment->getAircraftsOnRepair()[0].getModel(), "ModelE");
}
