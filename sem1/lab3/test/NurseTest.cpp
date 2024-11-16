#include "gtest/gtest.h"
#include "Nurse.h"
#include "Ward.h"
#include "Doctor.h"
#include "Patient.h"
#include <iostream>

std::tm MakeTestDate(int day, int month, int year) {
    std::tm date = {};
    date.tm_mday = day;
    date.tm_mon = month - 1;
    date.tm_year = year - 1900;
    return date;
}

TEST(WardTest, TestAdmitAndDischargePatient) {
    Ward ward("W01", "General", "Medical", 2);
    Patient patient("John", "Doe", 30, "Male", "123 Main St", "555-1234", "P001", "Flu");

    ward.admitPatient(&patient);
    EXPECT_EQ(ward.checkAvailability(), true);

    Patient anotherPatient("Jane", "Doe", 28, "Female", "456 Maple St", "555-5678", "P002", "Cold");
    ward.admitPatient(&anotherPatient);
    EXPECT_EQ(ward.checkAvailability(), false);

    ward.dischargePatient(&patient);
    EXPECT_EQ(ward.checkAvailability(), true);
}

TEST(NurseTest, TestAssistDoctorAndLogCare) {
    Nurse nurse("Alice", "Smith", 35, "Female", "789 Oak St", "555-9876", "N001", 8, "General");
    Doctor doctor("Dr. Bob", "Johnson", 45, "Male", "123 Birch St", "555-4321", "D001", "Surgeon", "P001");
    Patient patient("John", "Doe", 30, "Male", "123 Main St", "555-1234", "P001", "Flu");

    nurse.assistDoctor(&doctor);
    nurse.logPatientCare(&patient);

    Ward ward("W01", "General", "Medical", 2);
    nurse.updateWard(&ward);
}