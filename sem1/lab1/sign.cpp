#include "sign.h"

Sign::Sign() : visual('+') {}
Sign::Sign(const char& v) : visual(v) {
    if (v != '+' && v != '-') {
        visual = '+';
    }
}
std::ostream& operator<<(std::ostream& os, const Sign& sign) {
    os << sign.visual;
    return os;
}
int Sign::operator*(int number) const {
    return (visual == '+' ? number : -number);
}
char Sign::get_visual() const {
    return visual;
}
