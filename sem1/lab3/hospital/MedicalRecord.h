#ifndef MEDICALRECORD_H
#define MEDICALRECORD_H

#include <string>
#include <vector>

class Patient;

class MedicalRecord {
private:
    std::string recordID;
    std::string patientID;
    std::vector<std::string> diagnoses;
    std::vector<std::string> treatments;
    std::vector<std::string> notes;

public:
    MedicalRecord(const std::string& recordID, const std::string& patientID);

    void addDiagnosis(const std::string& diagnosis);
    void addTreatment(const std::string& treatment);
    void addNote(const std::string& note);
    std::string getRecord() const;

    // Ассоциация с пациентом
    const std::string& getPatientID() const;

    virtual ~MedicalRecord() = default;
};

#endif // MEDICALRECORD_H
