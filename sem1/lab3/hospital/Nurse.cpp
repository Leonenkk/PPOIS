#include "Nurse.h"
#include "Ward.h"
#include "Doctor.h"
#include "Patient.h"
#include <iostream>

Nurse::Nurse(const std::string& name, const std::string& surname, int age,
             const std::string& gender, const std::string& address, const std::string& phone,
             const std::string& nurseID, int shiftHours, const std::string& assignedWard)
    : Person(name, surname, age, gender, address, phone), nurseID(nurseID), shiftHours(shiftHours),
      assignedWard(assignedWard), ward(nullptr) {}

void Nurse::assistDoctor(Doctor* doctor) {
    std::cout << "Nurse " << getFullName() << " is assisting doctor " << doctor->getFullName() << std::endl;
}

void Nurse::updateWard(Ward* newWard) {
    ward = newWard;
    assignedWard = newWard->getWardName();
    std::cout << "Nurse " << getFullName() << " is now assigned to " << assignedWard << " ward." << std::endl;
}

void Nurse::logPatientCare(Patient* patient) {
    std::cout << "Nurse " << getFullName() << " is logging care for patient " << patient->getFullName() << std::endl;
}
