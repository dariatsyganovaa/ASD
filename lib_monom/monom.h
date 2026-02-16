#ifndef LIB_MONOM_MONOM_H_
#define LIB_MONOM_MONOM_H_

#include <iostream>
#include <cmath>

struct Monom {
    double coef;
    int degree;  

    Monom(double c = 0.0, int d = 0) : coef(c), degree(d) {}

    bool operator==(const Monom& other) const {
        return degree == other.degree && std::abs(coef - other.coef) < 1e-10;
    }

    bool operator!=(const Monom& other) const {
        return !(*this == other);
    }
};

#endif
