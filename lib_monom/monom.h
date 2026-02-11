#ifndef LIB_MONOM_MONOM_H_
#define LIB_MONOM_MONOM_H_

#include <iostream>
#include <cmath>

struct Monom {
    double coef; // Коэффициент
    int degree;  // Свернутая степень (напр. 231 для x^2 y^3 z^1)

    Monom(double c = 0.0, int d = 0) : coef(c), degree(d) {}

    // Сравнение мономов (нужно для сравнения полиномов в тестах)
    bool operator==(const Monom& other) const {
        // Для double используем малую погрешность
        return degree == other.degree && std::abs(coef - other.coef) < 1e-10;
    }

    bool operator!=(const Monom& other) const {
        return !(*this == other);
    }
};

#endif
