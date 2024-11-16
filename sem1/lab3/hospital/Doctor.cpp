#include <iostream>
#include "Doctor.h"
#include "Patient.h"

Doctor::Doctor(const std::string& name, const std::string& surname, int age,
               const std::string& gender, const std::string& address, const std::string& phone,
               const std::string& doctorID, const std::string& specialization, const std::string& licenseNumber)
    : Person(name, surname, age, gender, address, phone), doctorID(doctorID),
      specialization(specialization), licenseNumber(licenseNumber) {}

void Doctor::diagnose(Patient& patient) {
    std::cout << "Diagnosing patient: " << patient.getFullName() << std::endl;
}

void Doctor::prescribeTreatment(Patient& patient, const std::string& treatment) {
    std::cout << "Prescribing treatment to " << patient.getFullName() << ": " << treatment << std::endl;
}

void Doctor::updateSchedule(const std::string& day, const std::string& hours) {
    schedule.push_back(day + ": " + hours);
    std::cout << "Updated schedule: " << day << " " << hours << std::endl;
}

void Doctor::addPatient(Patient* patient) {
    patientsUnderCare.push_back(patient);
    patient->assignDoctor(this);
    std::cout << "Assigned patient " << patient->getFullName() << " to doctor " << getFullName() << std::endl;
}
std::string Doctor::getDoctorID() const {
    return doctorID;
}

