#include "monom.h"

Monom::Monom() : _coeff(0.0) {
    for (int i = 0; i < VARS_COUNT; i++) {
        _powers[i] = 0;
    }
}

Monom::Monom(double coeff, const int powers[VARS_COUNT]) : _coeff(coeff) {
    for (int i = 0; i < VARS_COUNT; i++) {
        _powers[i] = powers[i];
    }
}

Monom::Monom(const Monom& other) : _coeff(other._coeff) {
    for (int i = 0; i < VARS_COUNT; i++) {
        _powers[i] = other._powers[i];
    }
}

Monom& Monom::operator=(const Monom& other) {
    if (this != &other) {
        _coeff = other._coeff;
        for (int i = 0; i < VARS_COUNT; i++) {
            _powers[i] = other._powers[i];
        }
    }
    return *this;
}

bool Monom::operator==(const Monom& other) const {
    for (int i = 0; i < VARS_COUNT; i++) {
        if (_powers[i] != other._powers[i]) {
            return false;
        }
    }
    return true;
}

bool Monom::operator!=(const Monom& other) const {
    return !(*this == other);
}

bool Monom::operator>(const Monom& other) const {
    for (int i = 0; i < VARS_COUNT; i++) {
        if (_powers[i] > other._powers[i]) {
            return true;
        }

        if (_powers[i] < other._powers[i]) {
            return false;
        }
    }
    return _coeff > other._coeff;
}

bool Monom::operator<(const Monom& other) const {
    return other > *this;
}

Monom Monom::operator+(const Monom& other) const {
    Monom res(*this);
    res += other;
    return res;
}

Monom Monom::operator-(const Monom& other) const {
    Monom res(*this);
    res -= other;
    return res;
}

Monom Monom::operator*(const Monom& other) const {
    Monom res(*this);
    res *= other;
    return res;
}

Monom Monom::operator/(const Monom& other) const {
    Monom res(*this);
    res /= other;
    return res;
}

Monom& Monom::operator+=(const Monom& other) {
    if (*this != other) {
        throw std::invalid_argument("Monom::operator+= : Monomes are not similar for addition!");
    }
    _coeff += other._coeff;
    return *this;
}

Monom& Monom::operator-=(const Monom& other) {
    if (*this != other) {
        throw std::invalid_argument("Monom::operator+= : Monomes are not similar for subtraction!");
    }
    _coeff -= other._coeff;
    return *this;
}

Monom& Monom::operator*=(const Monom& other) {
    _coeff *= other._coeff;
    for (int i = 0; i < VARS_COUNT; i++) {
        _powers[i] += other._powers[i];
    }
    return *this;
}

Monom& Monom::operator/=(const Monom& other) {
    if (other._coeff == 0.0) {
        throw std::invalid_argument("Monom::operator/= : You can't divide by a monomial with a zero coefficient!");
    }
    _coeff /= other._coeff;
    for (int i = 0; i < VARS_COUNT; i++) {
        _powers[i] -= other._powers[i];
    }
    return *this;
}

Monom Monom::operator*(double scalar) const {
    Monom res(*this);
    res *= scalar;
    return res;
}

Monom& Monom::operator*=(double scalar) {
    _coeff *= scalar;
    return *this;
}

Monom Monom::operator/(double scalar) const {
    Monom res(*this);
    res /= scalar;
    return res;
}

Monom& Monom::operator/=(double scalar) {
    if (scalar == 0) {
        throw std::invalid_argument("Monom::operator/= : Division by zero!");
    }
    _coeff /= scalar;
    return *this;
}

Monom Monom::operator-() const {
    return *this * (-1.0);
}

double Monom::evaluate(const double values[VARS_COUNT]) const {
    double result = _coeff;
    for (size_t i = 0; i < VARS_COUNT; i++) {
        result *= std::pow(values[i], _powers[i]);
    }
    return result;
}

double Monom::calculate(double x, double y, double z) const {
    double values[VARS_COUNT] = { x, y, z };
    return evaluate(values);
}

Monom operator*(double scalar, const Monom& m) {
    return m * scalar;
}

std::ostream& operator<<(std::ostream& out, const Monom& m) {
    out << std::fixed << std::setprecision(3) << m._coeff; 

    const char names[] = { 'x', 'y', 'z' };
    for (int i = 0; i < VARS_COUNT; i++)
        if (m._powers[i] != 0) {
            out << names[i];
            if (m._powers[i] != 1) {
                out << '^' << m._powers[i];
            }
        }
    return out;
}

std::istream& operator>>(std::istream& in, Monom& m) {
    in >> m._coeff;
    for (int i = 0; i < VARS_COUNT; i++) {
        in >> m._powers[i];
    }
    return in;
}