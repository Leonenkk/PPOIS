#include "gtest/gtest.h"
#include "HospitalManagementSystem.h"
#include "Patient.h"
#include "Doctor.h"
#include "Appointment.h"
#include "MedicalRecord.h"
#include "Prescription.h"
#include "Billing.h"


TEST(HospitalManagementSystemTest, ScheduleAppointment) {
    HospitalManagementSystem hospital;
    Patient patient("Jane", "Smith", 25, "Female", "456 Oak St", "555-5678", "P54321", "InsuranceY");
    Doctor doctor("John", "Doe", 45, "Male", "123 Main St", "555-1234", "D001", "Cardiology", "LN123");
    hospital.addPatient(patient);
    hospital.addDoctor(doctor);

    hospital.scheduleAppointment("P54321", "D12345", "2024-11-15", "10:00");

    Appointment* appointment = hospital.findAppointment("1");
    ASSERT_NE(appointment, nullptr);
    EXPECT_EQ(appointment->getStatus(), "Scheduled");
}

