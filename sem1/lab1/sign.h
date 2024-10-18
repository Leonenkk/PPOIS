#ifndef SIGN_H
#define SIGN_H

#include <iostream>

class Sign {
public:
    char get_visual() const;

    Sign();

    Sign(const char &v);

    friend std::ostream &operator<<(std::ostream &os, const Sign &sign);

    int operator*(int number) const;

private:
    char visual;
};
#endif // SIGN_H
