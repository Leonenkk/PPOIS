#include "Receptionist.h"
#include "Patient.h"
#include "Doctor.h"
#include <iostream>

Receptionist::Receptionist(const std::string& name, const std::string& surname, int age,
                           const std::string& gender, const std::string& address, const std::string& phone,
                           const std::string& employeeID, int shiftHours, int deskNumber)
    : Person(name, surname, age, gender, address, phone), employeeID(employeeID), shiftHours(shiftHours),
      deskNumber(deskNumber) {}

void Receptionist::scheduleAppointment(Patient* patient, Doctor* doctor) {
    std::cout << "Receptionist " << getFullName() << " is scheduling an appointment for patient "
              << patient->getFullName() << " with doctor " << doctor->getFullName() << std::endl;
}

void Receptionist::updateContactInfo(Person* person, const std::string& newAddress, const std::string& newPhone) {
    person->setAddress(newAddress);
    person->setPhone(newPhone);
    std::cout << "Updated contact information for " << person->getFullName() << ": "
              << "Address: " << newAddress << ", Phone: " << newPhone << std::endl;
}

void Receptionist::processInsurance(Patient* patient) {
    std::cout << "Receptionist " << getFullName() << " is processing insurance for patient "
              << patient->getFullName() << std::endl;
}
