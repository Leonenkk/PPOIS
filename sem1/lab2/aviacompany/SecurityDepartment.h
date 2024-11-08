#ifndef SECURITYDEPARTMENT_H
#define SECURITYDEPARTMENT_H

#include "Department.h"
#include <vector>
#include <string>

class SecurityDepartment : public Department {
private:
    std::vector<std::string> logOfReflectedAttacks;
    std::vector<std::string> instruments;

public:
    SecurityDepartment(const std::vector<Employee>& employees, const std::vector<std::string>& logOfReflectedAttacks, const std::vector<std::string>& instruments);

    std::vector<std::string> getLogOfReflectedAttacks() const;
    void setLogOfReflectedAttacks(const std::vector<std::string>& logOfReflectedAttacks);

    std::vector<std::string> getInstruments() const;
    void setInstruments(const std::vector<std::string>& instruments);
};

#endif
