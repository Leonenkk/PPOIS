#ifndef RECEPTIONIST_H
#define RECEPTIONIST_H

#include "Person.h"
#include <string>
#include "Patient.h"

class Receptionist : public Person {
private:
    std::string employeeID;
    int shiftHours;
    int deskNumber;

public:
    Receptionist(const std::string& name, const std::string& surname, int age,
                 const std::string& gender, const std::string& address, const std::string& phone,
                 const std::string& employeeID, int shiftHours, int deskNumber);

    void scheduleAppointment(Patient* patient, Doctor* doctor);

    static void updateContactInfo(Person* person, const std::string& newAddress, const std::string& newPhone);

    void processInsurance(Patient* patient);

};

#endif
