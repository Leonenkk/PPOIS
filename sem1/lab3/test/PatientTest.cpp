#include "gtest/gtest.h"
#include "Patient.h"
#include <string>
#include <vector>

TEST(PatientTest, ConstructorAndAddAllergy) {
    Patient patient("John", "Doe", 30, "Male", "123 Main St", "555-1234", "P12345", "HealthInsurance");
    EXPECT_EQ(patient.getPatientID(), "P12345");
    EXPECT_EQ(patient.getInsuranceInfo(), "Insurance: HealthInsurance");
    patient.addAllergy("Peanuts");
    EXPECT_EQ(patient.getMedicalHistory(), "No medical record available.");
}

TEST(PatientTest, AddAllergy) {
    Patient patient("Alice", "Johnson", 28, "Female", "101 Pine St", "555-2345", "P22334", "Aetna");
    patient.addAllergy("Dust");
    EXPECT_EQ(patient.getMedicalHistory(), "No medical record available.");
}