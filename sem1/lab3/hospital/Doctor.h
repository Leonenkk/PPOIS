#ifndef DOCTOR_H
#define DOCTOR_H

#include "Person.h"
#include <vector>
#include <string>

class Patient;

class Doctor : public Person {
private:
    std::string doctorID;
    std::string specialization;
    std::string licenseNumber;
    std::vector<std::string> schedule;
    std::vector<Patient*> patientsUnderCare; // Ассоциация с пациентами
public:
    Doctor(const std::string& name, const std::string& surname, int age,
           const std::string& gender, const std::string& address, const std::string& phone,
           const std::string& doctorID, const std::string& specialization, const std::string& licenseNumber);
    std::string getDoctorID() const;
    static void diagnose(Patient& patient);
    static void prescribeTreatment(Patient& patient, const std::string& treatment);
    void updateSchedule(const std::string& day, const std::string& hours);
    void addPatient(Patient* patient);

    ~Doctor() override = default;
};

#endif
