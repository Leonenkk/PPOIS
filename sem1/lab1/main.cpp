#include "fraction.h"
#include "sign.h"
#include <gtest/gtest.h>


int main() {

Fraction f1('+',1, 2);
Fraction f2(Sign('-'), 3, 4);
Fraction f3(5);

std::cout << "f1: " << f1 << std::endl;
std::cout << "f2: " << f2 << std::endl;
std::cout << "f3: " << f3 << std::endl;

Fraction sum = f1 + f2;
std::cout << "f1 + f2: " << sum << std::endl;

Fraction diff = f3 - f2;
std::cout << "f3 - f2: " << diff << std::endl;

Fraction prod = f1 * f2;
std::cout << "f1 * f2: " << prod << std::endl;

Fraction quot = f3 / f2;
std::cout << "f3 / f2: " << quot << std::endl;

Fraction f4(Sign('-'), 6, -3);
std::cout << "f4: " << f4 << std::endl;

}
// g++ -o main main.cpp fraction.cpp sign.cpp
// ./main
// g++ -o fraction_test fraction_test.cpp fraction.cpp sign.cpp -lgtest -lgtest_main -pthread
// ./fraction_test
