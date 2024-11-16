#ifndef NURSE_H
#define NURSE_H

#include "Person.h"
#include <string>


class Ward;
class Doctor;
class Patient;

class Nurse : public Person {
private:
    std::string nurseID;
    int shiftHours;
    std::string assignedWard;
    Ward* ward; // Ассоциация с отделом

public:
    Nurse(const std::string& name, const std::string& surname, int age,
          const std::string& gender, const std::string& address, const std::string& phone,
          const std::string& nurseID, int shiftHours, const std::string& assignedWard);

    void assistDoctor(Doctor* doctor);
    void updateWard(Ward* newWard);
    void logPatientCare(Patient* patient);
};

#endif
