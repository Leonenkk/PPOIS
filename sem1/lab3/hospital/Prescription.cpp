#include "Prescription.h"
#include "Pharmacy.h"
#include <iostream>

Prescription::Prescription(const std::string& prescriptionID, const std::string& doctorID, const std::string& patientID)
    : prescriptionID(prescriptionID), doctorID(doctorID), patientID(patientID), pharmacy(nullptr) {}

void Prescription::addMedication(const std::string& medication, const std::string& dosage, int duration) {
    medications.push_back(medication);
    this->dosage.push_back(dosage);
    this->duration.push_back(duration);
}

void Prescription::updateDosage(const std::string& medication, const std::string& newDosage) {
    for (size_t i = 0; i < medications.size(); ++i) {
        if (medications[i] == medication) {
            dosage[i] = newDosage;
            std::cout << "Updated dosage for " << medication << " to " << newDosage << std::endl;
            return;
        }
    }
    std::cout << "Medication " << medication << " not found in prescription." << std::endl;
}

// Печать рецепта
void Prescription::printPrescription() const {
    std::cout << "Prescription ID: " << prescriptionID << std::endl;
    std::cout << "Doctor ID: " << doctorID << std::endl;
    std::cout << "Patient ID: " << patientID << std::endl;
    std::cout << "Medications: " << std::endl;
    for (size_t i = 0; i < medications.size(); ++i) {
        std::cout << "  - " << medications[i] << ", Dosage: " << dosage[i] << ", Duration: " << duration[i] << " days" << std::endl;
    }
}

void Prescription::sendToPharmacy(Pharmacy* pharmacy) {
    this->pharmacy = pharmacy;
    std::cout << "Prescription sent to pharmacy " << pharmacy->getLocation() << std::endl;
}

const std::vector<std::string>& Prescription::getMedications() const {
    return medications;
}

const std::vector<std::string>& Prescription::getDosage() const {
    return dosage;
}

const std::vector<int>& Prescription::getDuration() const {
    return duration;
}

Pharmacy* Prescription::getPharmacy() const {
    return pharmacy;
}
