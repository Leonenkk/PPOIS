#include <gtest/gtest.h>
#include "MedicalRecord.h"
#include "Patient.h"
#include "Doctor.h"

TEST(MedicalRecordTest, TestConstructorAndAddMethods) {
    Patient patient("John", "Doe", 30, "Male", "123 Street", "555-5555", "P001", "XYZ Insurance");
    MedicalRecord record("R001", patient.getPatientID());
    EXPECT_EQ(record.getPatientID(), "P001");
    record.addDiagnosis("Flu");
    record.addDiagnosis("Cold");
    record.addTreatment("Rest");
    record.addTreatment("Medication");
    record.addNote("Patient recovering well");

    std::string expectedRecord = "Record ID: R001\n";
    expectedRecord += "Patient ID: P001\n\n";
    expectedRecord += "Diagnoses:\n- Flu\n- Cold\n\n";
    expectedRecord += "Treatments:\n- Rest\n- Medication\n\n";
    expectedRecord += "Notes:\n- Patient recovering well\n";

    EXPECT_EQ(record.getRecord(), expectedRecord);
}

TEST(MedicalRecordTest, TestEmptyRecord) {
    Patient patient("Jane", "Smith", 40, "Female", "456 Avenue", "555-1234", "P002", "ABC Insurance");
    MedicalRecord record("R002", patient.getPatientID());

    std::string expectedRecord = "Record ID: R002\n";
    expectedRecord += "Patient ID: P002\n\n";
    expectedRecord += "Diagnoses:\n";
    expectedRecord += "\nTreatments:\n";
    expectedRecord += "\nNotes:\n";

    EXPECT_EQ(record.getRecord(), expectedRecord);
}

TEST(MedicalRecordTest, TestPatientAllergies) {
    Patient patient("Mark", "Taylor", 50, "Male", "789 Road", "555-9876", "P003", "DEF Insurance");
    MedicalRecord record("R003", patient.getPatientID());

    EXPECT_EQ(patient.getMedicalHistory(), "No medical record available.");
    patient.addAllergy("Peanuts");
    patient.addAllergy("Penicillin");
    EXPECT_EQ(patient.getMedicalHistory(), "No medical record available.");
}

TEST(MedicalRecordTest, TestAssignDoctorToPatient) {
    Patient patient("Alice", "Johnson", 25, "Female", "1011 Lane", "555-1111", "P004", "GHI Insurance");
    Doctor doctor("Dr. Sarah", "Connor", 45, "Female", "1234 Medical St.", "555-1010", "D001", "Cardiology", "LIC123");
    doctor.addPatient(&patient);
    EXPECT_EQ(patient.getMedicalRecord(), nullptr);
    EXPECT_EQ(patient.getMedicalHistory(), "No medical record available.");
}

TEST(MedicalRecordTest, TestDoctorSchedule) {
    Doctor doctor("Dr. Mark", "Smith", 40, "Male", "4321 Health Ave.", "555-2222", "D002", "Neurology", "LIC456");
    doctor.updateSchedule("Monday", "9 AM - 12 PM");
    doctor.updateSchedule("Wednesday", "1 PM - 4 PM");
    EXPECT_EQ(doctor.getDoctorID(), "D002");
}