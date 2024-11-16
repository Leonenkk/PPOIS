#include "gtest/gtest.h"
#include "Ward.h"
#include "Nurse.h"
#include "Patient.h"

TEST(WardTest, Admission) {
    Ward ward("W001", "General", "Surgical", 2);

    Patient patient1("John", "Doe", 30, "Male", "123 Main St", "555-1234", "001", "Basic Insurance");
    Patient patient2("Jane", "Smith", 25, "Female", "456 Oak St", "555-5678", "002", "Premium Insurance");

    ward.admitPatient(&patient1);
    ward.admitPatient(&patient2);

    EXPECT_FALSE(ward.checkAvailability());

    Patient patient3("Bob", "Johnson", 40, "Male", "789 Pine St", "555-8765", "003", "Basic Insurance");
    ward.admitPatient(&patient3);
}

TEST(WardTest, Discharge) {
    Ward ward("W001", "General", "Surgical", 2);
    Patient patient("John", "Doe", 30, "Male", "123 Main St", "555-1234", "001", "Basic Insurance");

    ward.admitPatient(&patient);

    ward.dischargePatient(&patient);

    EXPECT_TRUE(ward.checkAvailability());

    ward.dischargePatient(&patient);
}

TEST(WardTest, NurseAssignment) {
    Ward ward("W001", "General", "Surgical", 2);
    Nurse nurse("Alice", "Johnson", 35, "Female", "234 Birch St", "555-2345", "N001", 8, "General");

    ward.assignNurse(&nurse);
}
