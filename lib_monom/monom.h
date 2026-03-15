#ifndef LIB_MONOM_MONOM_H_
#define LIB_MONOM_MONOM_H_

#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>

#define VARS_COUNT 3

class Monom {
    double _coeff;
    int _powers[VARS_COUNT];

public:
    Monom();
    Monom(double coeff, const int powers[VARS_COUNT]);
    Monom(const Monom& other);

    double get_coeff() const noexcept { return _coeff; }
    const int* get_powers() const noexcept { return _powers; }

    Monom& operator=(const Monom& other);
    bool operator==(const Monom& other) const;
    bool operator!=(const Monom& other) const;

    bool operator>(const Monom& other) const;
    bool operator<(const Monom& other) const;

    Monom operator+(const Monom& other) const;
    Monom operator-(const Monom& other) const;

    Monom operator*(const Monom& other) const;
    Monom operator/(const Monom& other) const;

    Monom operator*(double scalar) const;
    Monom operator/(double scalar) const;

    Monom operator-() const;

    Monom& operator+=(const Monom& other);
    Monom& operator-=(const Monom& other);
    Monom& operator*=(const Monom& other);
    Monom& operator/=(const Monom& other);
    Monom& operator*=(double scalar);
    Monom& operator/=(double scalar);

    double evaluate(const double values[VARS_COUNT]) const;
    double calculate(double x, double y, double z) const;

    friend Monom operator*(double scalar, const Monom& m);

    friend std::ostream& operator<<(std::ostream& out, const Monom& m);
    friend std::istream& operator>>(std::istream& in, Monom& m);
};
#endif
