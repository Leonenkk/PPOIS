#include "People.h"

People::People(const std::string& name, int age) : name(name), age(age) {}

std::string People::getName() const {
    return name;
}

void People::setName(const std::string& name) {
    this->name = name;
}

int People::getAge() const {
    return age;
}

void People::setAge(int age) {
    this->age = age;
}
