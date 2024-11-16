#ifndef PATIENT_H
#define PATIENT_H

#include "Person.h"
#include "MedicalRecord.h"
#include <vector>

class Doctor;

class Patient : public Person {
private:
    std::string patientID;
    std::vector<std::string> medicalHistory;
    std::vector<std::string> allergies;
    std::string insurance;
    Doctor* doctor; // Ассоциация с лечащим врачом
    MedicalRecord* medicalRecord;  // Ассоциация с медкартой пациента

public:
    Patient(const std::string& name, const std::string& surname, int age,
            const std::string& gender, const std::string& address, const std::string& phone,
            const std::string& patientID, const std::string& insurance);
    std::string getPatientID() const;
    std::string getMedicalHistory() const;

    void addAllergy(const std::string& allergy);

    std::string getInsuranceInfo() const;

    void assignDoctor(Doctor* doc);

    void assignMedicalRecord(MedicalRecord* record);

    const MedicalRecord* getMedicalRecord() const;

};

#endif
