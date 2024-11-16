#include "MedicalRecord.h"
#include "Patient.h"
#include <iostream>

// Конструктор
MedicalRecord::MedicalRecord(const std::string& recordID, const std::string& patientID)
    : recordID(recordID), patientID(patientID) {}

// Метод для добавления диагноза
void MedicalRecord::addDiagnosis(const std::string& diagnosis) {
    diagnoses.push_back(diagnosis);
}

// Метод для добавления лечения
void MedicalRecord::addTreatment(const std::string& treatment) {
    treatments.push_back(treatment);
}

// Метод для добавления заметки
void MedicalRecord::addNote(const std::string& note) {
    notes.push_back(note);
}

// Метод для получения записи (диагнозы, лечения, заметки)
std::string MedicalRecord::getRecord() const {
    std::string record = "Record ID: " + recordID + "\n";
    record += "Patient ID: " + patientID + "\n";

    record += "\nDiagnoses:\n";
    for (const auto& diagnosis : diagnoses) {
        record += "- " + diagnosis + "\n";
    }

    record += "\nTreatments:\n";
    for (const auto& treatment : treatments) {
        record += "- " + treatment + "\n";
    }

    record += "\nNotes:\n";
    for (const auto& note : notes) {
        record += "- " + note + "\n";
    }

    return record.empty() ? "No records available." : record;
}

// Метод для получения ID пациента
const std::string& MedicalRecord::getPatientID() const {
    return patientID;
}
