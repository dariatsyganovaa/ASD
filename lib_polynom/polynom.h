#ifndef LIB_POLYNOM_POLYNOM_H_
#define LIB_POLYNOM_POLYNOM_H_

#include "../lib_list/list.h"
#include "../lib_monom/monom.h"
#include <string>
#include <algorithm>

class Polynom {
    List<Monom> _monoms;
public:
    Polynom();
    Polynom(const Monom& m);
    Polynom(const std::string& str);
    Polynom(const Polynom& other);

    Monom parse_monoms(const std::string&);
    const List<Monom>& get_monoms() const noexcept { return _monoms; }

    Polynom& operator=(const Polynom& other);

    bool operator==(const Polynom& other) const;
    bool operator!=(const Polynom& other) const;
    bool operator<(const Polynom& other) const;
    bool operator>(const Polynom& other) const;

    Polynom operator-() const;

    Polynom operator+(const Polynom& other) const;
    Polynom operator-(const Polynom& other) const;
    Polynom operator*(const Polynom& other) const;

    Polynom& operator+=(const Polynom& other);
    Polynom& operator-=(const Polynom& other);
    Polynom& operator*=(const Polynom& other);

    Polynom operator+(const Monom& m) const;
    Polynom operator-(const Monom& m) const;
    Polynom operator*(const Monom& m) const;
    Polynom operator/(const Monom& m) const;

    Polynom& operator+=(const Monom& m);
    Polynom& operator-=(const Monom& m);
    Polynom& operator*=(const Monom& m);
    Polynom& operator/=(const Monom& m);

    Polynom operator+(double scalar) const;
    Polynom operator-(double scalar) const;
    Polynom operator*(double scalar) const;
    Polynom operator/(double scalar) const;

    Polynom& operator+=(double scalar);
    Polynom& operator-=(double scalar);
    Polynom& operator*=(double scalar);
    Polynom& operator/=(double scalar);

    friend Polynom operator+(double scalar, const Polynom& p);
    friend Polynom operator*(double scalar, const Polynom& p);
    friend Polynom operator+(const Monom& m, const Polynom& p);
    friend Polynom operator-(const Monom& m, const Polynom& p);
    friend Polynom operator*(const Monom& m, const Polynom& p);

    double calculate(double x, double y, double z) const;
    double evaluate(const double values[VARS_COUNT]) const;

    std::string toString() const;
    friend std::ostream& operator<<(std::ostream& out, const Polynom& p);
    friend std::istream& operator>>(std::istream& in, Polynom& p);

private:
    void add_monom(const Monom& m);
};
#endif