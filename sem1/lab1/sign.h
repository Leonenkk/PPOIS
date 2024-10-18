#ifndef SIGN_H
#define SIGN_H

#include <iostream>

struct Sign {
    char visual;
    Sign();
    Sign(const char& v);
    friend std::ostream& operator<<(std::ostream& os, const Sign& sign);
    int operator*(int number) const;
};

#endif // SIGN_H