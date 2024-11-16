#include "Patient.h"
#include "Doctor.h"
#include "MedicalRecord.h"

// Конструктор
Patient::Patient(const std::string& name, const std::string& surname, int age,
                 const std::string& gender, const std::string& address, const std::string& phone,
                 const std::string& patientID, const std::string& insurance)
    : Person(name, surname, age, gender, address, phone), patientID(patientID), insurance(insurance), doctor(nullptr), medicalRecord(nullptr) {}

std::string Patient::getMedicalHistory() const {
    std::string history;
    if (medicalRecord) {
        history = medicalRecord->getRecord();
    } else {
        history = "No medical record available.";
    }
    return history;
}

void Patient::addAllergy(const std::string& allergy) {
    allergies.push_back(allergy);
}

std::string Patient::getInsuranceInfo() const {
    return "Insurance: " + insurance;
}

void Patient::assignDoctor(Doctor* doc) {
    doctor = doc;
}

void Patient::assignMedicalRecord(MedicalRecord* record) {
    medicalRecord = record;
}

const MedicalRecord* Patient::getMedicalRecord() const {
    return medicalRecord;

}
std::string Patient::getPatientID() const {
    return patientID;
}
