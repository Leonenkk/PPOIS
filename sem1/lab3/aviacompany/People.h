#ifndef PEOPLE_H
#define PEOPLE_H

#include <string>

class People {
protected:
    std::string name;
    int age;

public:
    People(const std::string& name, int age);

    std::string getName() const;
    void setName(const std::string& name);

    int getAge() const;
    void setAge(int age);
};

#endif