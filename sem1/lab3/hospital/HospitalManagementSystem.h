#ifndef HOSPITALMANAGEMENTSYSTEM_H
#define HOSPITALMANAGEMENTSYSTEM_H

#include <vector>
#include <string>
#include "Patient.h"
#include "Doctor.h"
#include "Appointment.h"
#include "MedicalRecord.h"
#include "Billing.h"

class HospitalManagementSystem {
private:
    std::vector<Patient> patients;
    std::vector<Doctor> doctors;
    std::vector<Appointment> appointments;
    std::vector<MedicalRecord> medicalRecords;
    std::vector<Billing> billings;

public:
    void addPatient(const Patient& patient);
    void removePatient(const std::string& patientID);
    Patient* findPatient(const std::string& patientID);

    void addDoctor(const Doctor& doctor);
    Doctor* findDoctor(const std::string& doctorID);

    void scheduleAppointment(const std::string& patientID, const std::string& doctorID, const std::string& date, const std::string& time);
    void cancelAppointment(const std::string& appointmentID);
    Appointment* findAppointment(const std::string& appointmentID);

    void addMedicalRecord(const MedicalRecord& record);
    MedicalRecord* getMedicalRecord(const std::string& patientID);

    void generateBilling(const Billing& bill);
    Billing* getBilling(const std::string& patientID);
};

#endif
