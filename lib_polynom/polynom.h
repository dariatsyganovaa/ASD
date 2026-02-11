#ifndef LIB_POLYNOM_POLYNOM_H_
#define LIB_POLYNOM_POLYNOM_H_

#include "../lib_tvector/tvector.h"
#include "../lib_monom/monom.h"
#include <string>
#include <algorithm>

class Polynom {
    TVector<Monom> monoms;
public:
    Polynom() = default;
    Polynom(const TVector<Monom>& m) : monoms(m) {
        // В реальной жизни тут должна быть нормализация (сложение подобных)
    }

    // Метод добавления монома (упрощенный)
    void addMonom(double c, int d) {
        if (std::abs(c) < 1e-10) return; // Нулевые коэффициенты не храним
        monoms.push_back_elem(Monom(c, d));
    }

    // Оператор сравнения для gtest (важно!)
    bool operator==(const Polynom& other) const {
        if (monoms.size() != other.monoms.size()) return false;
        for (size_t i = 0; i < monoms.size(); ++i) {
            if (monoms[i] != other.monoms[i]) return false;
        }
        return true;
    }

    // Оператор вывода для работы оператора << таблицы
    friend std::ostream& operator<<(std::ostream& out, const Polynom& p) {
        if (p.monoms.is_empty()) {
            out << "0";
            return out;
        }
        for (size_t i = 0; i < p.monoms.size(); ++i) {
            if (i > 0 && p.monoms[i].coef > 0) out << " + ";
            out << p.monoms[i].coef << "(deg:" << p.monoms[i].degree << ")";
        }
        return out;
    }
};
#endif