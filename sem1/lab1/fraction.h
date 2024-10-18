#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>
#include <numeric>
#include <stdexcept>
#include <cmath>
#include "sign.h"

class Fraction {
private:
    Sign sign;   
    int up; 
    int down; 

    void simplify();

public:
    Fraction();
    Fraction(char sign, int up, int down);
    Fraction(const Sign& s, int up, int down);
    Fraction(int num);

    int getNumerator() const;
    int getDenominator() const;
    int getIntegerPart() const;
    double getDouble() const;

    Fraction& operator+=(const Fraction& other);
    Fraction operator+(const Fraction& other) const;
    Fraction& operator+=(int num);
    Fraction operator+(int num) const;
    friend Fraction operator+(int num, const Fraction& frac);

    Fraction& operator-=(const Fraction& other);
    Fraction operator-(const Fraction& other) const;
    Fraction operator-() const;
    Fraction& operator-=(int num);
    Fraction operator-(int num) const;
    friend Fraction operator-(int num, const Fraction& frac);

    Fraction& operator*=(const Fraction& other);
    Fraction operator*(const Fraction& other) const;
    Fraction& operator*=(int num);
    Fraction operator*(int num) const;
    friend Fraction operator*(int num, const Fraction& frac);

    Fraction& operator/=(const Fraction& other);
    Fraction operator/(const Fraction& other) const;
    Fraction& operator/=(int num);
    Fraction operator/(int num) const;
    friend Fraction operator/(int num, const Fraction& frac);

    Fraction& operator++(); // prefix increment
    Fraction operator++(int); // postfix increment
    Fraction& operator--(); // prefix decrement
    Fraction operator--(int); // postfix decrement

    bool operator>(const Fraction& other) const;
    bool operator>=(const Fraction& other) const;
    bool operator<(const Fraction& other) const;
    bool operator<=(const Fraction& other) const;
    bool operator==(const Fraction& other) const;
    bool operator!=(const Fraction& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Fraction& fraction);
};

#endif // FRACTION_H