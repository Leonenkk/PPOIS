#include "fraction.h"

Fraction::Fraction() : sign('+'), up(0), down(1) {}

Fraction::Fraction(char sign, int up, int down) : sign(sign) {
    if (down == 0) {
        throw std::invalid_argument("denominator cannot be equal to zero");
    }

    this->up = up;
    this->down = down;
    simplify();
}

Fraction::Fraction(const Sign& s, int u, int d) : sign(s), up(u), down(d) {
        if (down == 0) {
            throw std::invalid_argument("denominator cannot be equal to zero");
        }
        simplify();
    }

Fraction::Fraction(int num) : sign(num < 0 ? '-' : '+'), up(std::abs(num)), down(1) {}

void Fraction::simplify() {
    int gcd_value = std::gcd(std::abs(up), std::abs(down));
    up /= gcd_value;
    down /= gcd_value;

    if (down < 0) {
        down = -down;
        up = -up;
    }
}

int Fraction::getNumerator() const { return sign * up; }
int Fraction::getDenominator() const { return down; }
int Fraction::getIntegerPart() const { return (sign * up) / down; }

double Fraction::getDouble() const {
    return static_cast<double>(sign * up) / down;
}

Fraction& Fraction::operator+=(const Fraction& other) { *this = *this + other; return *this; }
Fraction Fraction::operator+(const Fraction& other) const {
    int new_up = sign * up * other.down + other.sign * other.up * down;
    int new_down = down * other.down;
    char new_sign = (new_up < 0 ? '-' : '+');
    return Fraction(new_sign, std::abs(new_up), new_down);
}

Fraction& Fraction::operator+=(int num) { *this = *this + num; return *this; }
Fraction Fraction::operator+(int num) const { return *this + Fraction(num); }
Fraction operator+(int num, const Fraction& frac) { return Fraction(num) + frac; }

Fraction& Fraction::operator-=(const Fraction& other) { *this = *this - other; return *this; }
Fraction Fraction::operator-(const Fraction& other) const { return *this + (-other); }

Fraction Fraction::operator-() const { return Fraction(sign.get_visual() == '+' ? '-' : '+', up, down); }
Fraction& Fraction::operator-=(int num) { *this = *this - num; return *this; }
Fraction Fraction::operator-(int num) const { return *this + (-num); }
Fraction operator-(int num, const Fraction& frac) { return Fraction(num) - frac; }

Fraction& Fraction::operator*=(const Fraction& other) { *this = *this * other; return *this; }
Fraction Fraction::operator*(const Fraction& other) const {
    int new_up = sign * up * (other.sign * other.up);
    int new_down = down * other.down;
    char new_sign = (new_up < 0 ? '-' : '+');
    return Fraction(new_sign, std::abs(new_up), new_down);
}

Fraction& Fraction::operator*=(int num) { *this = *this * num; return *this; }
Fraction Fraction::operator*(int num) const { return *this * Fraction(num); }
Fraction operator*(int num, const Fraction& frac) { return Fraction(num) * frac; }

Fraction& Fraction::operator/=(const Fraction& other) { *this = *this / other; return *this; }
Fraction Fraction::operator/(const Fraction& other) const {
    if (other.up == 0) throw std::runtime_error("Division by zero");
    return *this * Fraction(other.sign, other.down, other.up);
}

Fraction& Fraction::operator/=(int num) { *this = *this / num; return *this; }
Fraction Fraction::operator/(int num) const {
    if (num == 0) throw std::runtime_error("Division by zero");
    return *this / Fraction(num);
}

Fraction operator/(int num, const Fraction& frac) {
    if (frac.up == 0) throw std::runtime_error("Division by zero");
    return Fraction(num) / frac;
}

Fraction& Fraction::operator++() { *this += 1; return *this; } // prefix increment
Fraction Fraction::operator++(int) { Fraction temp = *this; ++(*this); return temp; } // postfix increment

Fraction& Fraction::operator--() { *this -= 1; return *this; } // prefix decrement
Fraction Fraction::operator--(int) { Fraction temp = *this; --(*this); return temp; } // postfix decrement

bool Fraction::operator>(const Fraction& other) const { return this->getDouble() > other.getDouble(); }
bool Fraction::operator>=(const Fraction& other) const { return this->getDouble() >= other.getDouble(); }
bool Fraction::operator<(const Fraction& other) const { return this->getDouble() < other.getDouble(); }
bool Fraction::operator<=(const Fraction& other) const { return this->getDouble() <= other.getDouble(); }

bool Fraction::operator==(const Fraction& other) const { return this->getDouble() == other.getDouble(); }
bool Fraction::operator!=(const Fraction& other) const { return !(*this == other); }

std::ostream& operator<<(std::ostream& os, const Fraction& fraction) {
    os << fraction.sign << static_cast<const int>(fraction.up) << '/' << static_cast<const int>(fraction.down);
    return os;
}