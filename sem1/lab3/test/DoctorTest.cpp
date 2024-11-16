#include <gtest/gtest.h>
#include "Doctor.h"
#include "Patient.h"

TEST(DoctorTest, TestConstructorAndGetters) {
    Doctor doctor("John", "Doe", 45, "Male", "123 Main St", "555-1234", "D001", "Cardiology", "LN123");
    EXPECT_EQ(doctor.getDoctorID(), "D001");
}

TEST(DoctorTest, TestAddPatient) {
    Doctor doctor("John", "Doe", 45, "Male", "123 Main St", "555-1234", "D001", "Cardiology", "LN123");
    Patient patient("Jane", "Smith", 30, "Female", "456 Elm St", "555-5678", "P001", "Ailment");
    EXPECT_NO_THROW(doctor.addPatient(&patient));
}

TEST(DoctorTest, TestDiagnosePatient) {
    Doctor doctor("John", "Doe", 45, "Male", "123 Main St", "555-1234", "D001", "Cardiology", "LN123");
    Patient patient("Jane", "Smith", 30, "Female", "456 Elm St", "555-5678", "P001", "Ailment");
    EXPECT_NO_THROW(doctor.diagnose(patient));
}

TEST(DoctorTest, TestPrescribeTreatment) {
    Doctor doctor("John", "Doe", 45, "Male", "123 Main St", "555-1234", "D001", "Cardiology", "LN123");
    Patient patient("Jane", "Smith", 30, "Female", "456 Elm St", "555-5678", "P001", "Ailment");
    EXPECT_NO_THROW(doctor.prescribeTreatment(patient, "Medication"));
}

TEST(DoctorTest, TestUpdateSchedule) {
    Doctor doctor("John", "Doe", 45, "Male", "123 Main St", "555-1234", "D001", "Cardiology", "LN123");
    EXPECT_NO_THROW(doctor.updateSchedule("Monday", "9:00 AM - 5:00 PM"));
}