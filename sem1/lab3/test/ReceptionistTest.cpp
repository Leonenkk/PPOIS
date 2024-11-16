#include "Receptionist.h"
#include "Patient.h"
#include "Doctor.h"
#include <gtest/gtest.h>

class ReceptionistTest : public ::testing::Test {
protected:
    void SetUp() override {
        receptionist = new Receptionist("Alice", "Johnson", 30, "Female", "123 Main St", "555-1234", "R001", 8, 1);
        patient = new Patient("John", "Doe", 25, "Male", "456 Elm St", "555-5678", "P001", "HealthInsurance");
        doctor = new Doctor("Dr. Smith", "Jones", 40, "Male", "789 Oak St", "555-9876", "D001", "Cardiology", "L12345");
    }

    void TearDown() override {
        delete receptionist;
        delete patient;
        delete doctor;
    }

    Receptionist* receptionist;
    Patient* patient;
    Doctor* doctor;
};

TEST_F(ReceptionistTest, ScheduleAppointmentTest) {
    testing::internal::CaptureStdout();

    receptionist->scheduleAppointment(patient, doctor);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "Receptionist Alice Johnson is scheduling an appointment for patient John Doe with doctor Dr. Smith Jones\n");
}

TEST_F(ReceptionistTest, UpdateContactInfoTest) {
    testing::internal::CaptureStdout();

    receptionist->updateContactInfo(patient, "123 New Address", "555-0000");

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "Updated contact information for John Doe: Address: 123 New Address, Phone: 555-0000\n");
}

TEST_F(ReceptionistTest, ProcessInsuranceTest) {
    testing::internal::CaptureStdout();

    receptionist->processInsurance(patient);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "Receptionist Alice Johnson is processing insurance for patient John Doe\n");
}

