#include "gtest/gtest.h"
#include "SecurityDepartment.h"
#include "Employee.h"

class SecurityDepartmentTest : public ::testing::Test {
protected:
    SecurityDepartment* securityDepartment;
    std::vector<Employee> employees;
    std::vector<std::string> logOfReflectedAttacks;
    std::vector<std::string> instruments;

    void SetUp() override {
        employees.push_back(Employee("Alice", 30, 5000, 5, 1));
        employees.push_back(Employee("Bob", 40, 6000, 10, 2));

        logOfReflectedAttacks.push_back("Attack 1");
        logOfReflectedAttacks.push_back("Attack 2");

        instruments.push_back("Firewall");
        instruments.push_back("Intrusion Detection System");

        securityDepartment = new SecurityDepartment(employees, logOfReflectedAttacks, instruments);
    }

    void TearDown() override {
        delete securityDepartment;
    }
};

TEST_F(SecurityDepartmentTest, ConstructorAndGetters) {
    EXPECT_EQ(securityDepartment->getLogOfReflectedAttacks().size(), 2);
    EXPECT_EQ(securityDepartment->getInstruments().size(), 2);

    EXPECT_EQ(securityDepartment->getLogOfReflectedAttacks()[0], "Attack 1");
    EXPECT_EQ(securityDepartment->getInstruments()[0], "Firewall");
}

TEST_F(SecurityDepartmentTest, SetAndGetLogOfReflectedAttacks) {
    std::vector<std::string> newLog = {"New Attack 1", "New Attack 2"};
    securityDepartment->setLogOfReflectedAttacks(newLog);

    EXPECT_EQ(securityDepartment->getLogOfReflectedAttacks().size(), 2);
    EXPECT_EQ(securityDepartment->getLogOfReflectedAttacks()[0], "New Attack 1");
}

TEST_F(SecurityDepartmentTest, SetAndGetInstruments) {
    std::vector<std::string> newInstruments = {"Antivirus", "Encryption"};
    securityDepartment->setInstruments(newInstruments);

    EXPECT_EQ(securityDepartment->getInstruments().size(), 2);
    EXPECT_EQ(securityDepartment->getInstruments()[0], "Antivirus");
}

TEST_F(SecurityDepartmentTest, AddToLogOfReflectedAttacks) {
    std::vector<std::string> updatedLog = securityDepartment->getLogOfReflectedAttacks();
    updatedLog.push_back("Attack 3");
    securityDepartment->setLogOfReflectedAttacks(updatedLog);

    EXPECT_EQ(securityDepartment->getLogOfReflectedAttacks().size(), 3);
    EXPECT_EQ(securityDepartment->getLogOfReflectedAttacks()[2], "Attack 3");
}

TEST_F(SecurityDepartmentTest, AddToInstruments) {
    std::vector<std::string> updatedInstruments = securityDepartment->getInstruments();
    updatedInstruments.push_back("VPN");
    securityDepartment->setInstruments(updatedInstruments);

    EXPECT_EQ(securityDepartment->getInstruments().size(), 3);
    EXPECT_EQ(securityDepartment->getInstruments()[2], "VPN");
}
