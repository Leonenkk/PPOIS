#ifndef WARD_H
#define WARD_H

#include <string>
#include <vector>

class Nurse;
class Patient;

class Ward {
private:
    std::string wardID;
    std::string name;
    std::string type;
    int capacity;
    int occupancy;
    std::vector<Nurse*> nurses; // Ассоциация с медсестрами, работающими в отделе

public:
    Ward(const std::string& wardID, const std::string& name, const std::string& type, int capacity);

    void admitPatient(Patient* patient);
    void dischargePatient(Patient* patient);
    bool checkAvailability() const;
    void assignNurse(Nurse* nurse);

    std::string getWardName() const;

    virtual ~Ward() = default;
};

#endif
