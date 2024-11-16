#ifndef PRESCRIPTION_H
#define PRESCRIPTION_H

#include <string>
#include <vector>
#include "Pharmacy.h"

class Pharmacy;

class Prescription {
private:
    std::string prescriptionID;
    std::string doctorID;
    std::string patientID;
    std::vector<std::string> medications;
    std::vector<std::string> dosage;
    std::vector<int> duration;
    Pharmacy* pharmacy; // Ассоциация с аптекой

public:
    Prescription(const std::string& prescriptionID, const std::string& doctorID, const std::string& patientID);
    void addMedication(const std::string& medication, const std::string& dosage, int duration);
    void updateDosage(const std::string& medication, const std::string& newDosage);
    void printPrescription() const;
    void sendToPharmacy(Pharmacy* pharmacy);

    const std::vector<std::string>& getMedications() const;
    const std::vector<std::string>& getDosage() const;
    const std::vector<int>& getDuration() const;
    Pharmacy* getPharmacy() const;
};

#endif
