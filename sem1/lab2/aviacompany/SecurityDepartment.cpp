#include "SecurityDepartment.h"

SecurityDepartment::SecurityDepartment(const std::vector<Employee>& employees, const std::vector<std::string>& logOfReflectedAttacks, const std::vector<std::string>& instruments)
    : Department(employees), logOfReflectedAttacks(logOfReflectedAttacks), instruments(instruments) {}

std::vector<std::string> SecurityDepartment::getLogOfReflectedAttacks() const {
    return logOfReflectedAttacks;
}

void SecurityDepartment::setLogOfReflectedAttacks(const std::vector<std::string>& logOfReflectedAttacks) {
    this->logOfReflectedAttacks = logOfReflectedAttacks;
}

std::vector<std::string> SecurityDepartment::getInstruments() const {
    return instruments;
}

void SecurityDepartment::setInstruments(const std::vector<std::string>& instruments) {
    this->instruments = instruments;
}
