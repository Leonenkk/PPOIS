#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person {
protected:
    std::string name;
    std::string surname;
    int age;
    std::string gender;
    std::string address;
    std::string phone;

public:
    Person(const std::string& name, const std::string& surname, int age,
           const std::string& gender, const std::string& address, const std::string& phone);
    std::string getFullName() const;

    std::string getContactInfo() const;

    void setAddress(const std::string& newAddress);
    void setPhone(const std::string& newPhone);

    virtual ~Person() = default;
};

#endif // PERSON_H
