#include "HospitalManagementSystem.h"
#include <algorithm>

void HospitalManagementSystem::addPatient(const Patient& patient) {
    patients.push_back(patient);
}

void HospitalManagementSystem::removePatient(const std::string& patientID) {
    patients.erase(std::remove_if(patients.begin(), patients.end(), [&patientID](const Patient& p) {
        return p.getPatientID() == patientID;
    }), patients.end());
}

Patient* HospitalManagementSystem::findPatient(const std::string& patientID) {
    for (auto& patient : patients) {
        if (patient.getPatientID() == patientID) {
            return &patient;
        }
    }
    return nullptr;
}

void HospitalManagementSystem::addDoctor(const Doctor& doctor) {
    doctors.push_back(doctor);
}

Doctor* HospitalManagementSystem::findDoctor(const std::string& doctorID) {
    for (auto& doctor : doctors) {
        if (doctor.getDoctorID() == doctorID) {
            return &doctor;
        }
    }
    return nullptr;
}

void HospitalManagementSystem::scheduleAppointment(const std::string& patientID, const std::string& doctorID, const std::string& date, const std::string& time) {
    std::string appointmentID = std::to_string(appointments.size() + 1);  // Генерация уникального ID для назначения
    Appointment appointment(appointmentID, patientID, doctorID, date, time, "Scheduled");
    appointments.push_back(appointment);
}

void HospitalManagementSystem::cancelAppointment(const std::string& appointmentID) {
    appointments.erase(std::remove_if(appointments.begin(), appointments.end(), [&appointmentID](const Appointment& a) {
        return a.getAppointmentID() == appointmentID;
    }), appointments.end());
}

Appointment* HospitalManagementSystem::findAppointment(const std::string& appointmentID) {
    for (auto& appointment : appointments) {
        if (appointment.getAppointmentID() == appointmentID) {
            return &appointment;
        }
    }
    return nullptr;
}

void HospitalManagementSystem::addMedicalRecord(const MedicalRecord& record) {
    medicalRecords.push_back(record);
}

MedicalRecord* HospitalManagementSystem::getMedicalRecord(const std::string& patientID) {
    for (auto& record : medicalRecords) {
        if (record.getPatientID() == patientID) {
            return &record;
        }
    }
    return nullptr;
}

void HospitalManagementSystem::generateBilling(const Billing& bill) {
    billings.push_back(bill);
}

Billing* HospitalManagementSystem::getBilling(const std::string& patientID) {
    for (auto& bill : billings) {
        if (bill.getPatientID() == patientID) {
            return &bill;
        }
    }
    return nullptr;
}
