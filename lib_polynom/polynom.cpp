#include "polynom.h"

Polynom::Polynom() {
    add_monom(Monom());
}

Polynom::Polynom(const Monom& m) {
    add_monom(m);
}

Polynom::Polynom(const std::string& str) {
    int pos = 0;
    int len = str.length();
    while (pos < len) {
        std::string monom_str;
        if (str[pos] == '+' || str[pos] == '-') { 
            monom_str += str[pos];
            pos++; 
        }
        while (pos < len && str[pos] != '+' && str[pos] != '-') { 
            monom_str += str[pos];
            pos++; 
        }

        if (!monom_str.empty() && monom_str != "+" && monom_str != "-") {
            add_monom(parse_monoms(monom_str));
        }
    }
}

Polynom::Polynom(const Polynom& other) : _monoms(other._monoms) {}

Monom Polynom::parse_monoms(const std::string& str) {
    int p[VARS_COUNT] = { 0, 0, 0 };
    int pos = 0;
    int len = str.length();

    double sign = 1.0;
    if (pos < len) {
        if (str[pos] == '-') { 
            sign = -1.0; 
            pos++;
        }
        else if (str[pos] == '+') {
            pos++; 
        }
    }
    
    double coeff = 1.0;
    if (pos < len && isdigit(str[pos])) {
        double number = 0.0;
        double frac_val = 1.0;
        bool is_frac = false;

        while (pos < len) {
            if (isdigit(str[pos])) {
                int digit = str[pos] - '0'; 
                if (is_frac) {
                    frac_val *= 0.1;
                    number += digit * frac_val;
                }
                else {
                    number = number * 10.0 + digit;
                }
                pos++;
            }
            else if (str[pos] == '.'){
                is_frac = true;
                pos++;
            }
            else { break; }
        }
        coeff = number;
    }
    coeff = sign * coeff;

    while (pos < len) {
        int var_index = -1;
        if (str[pos] == 'x') { var_index = 0; }
        else if (str[pos] == 'y') { var_index = 1; }
        else if (str[pos] == 'z') { var_index = 2; }

        if (var_index != -1) {
            pos++;
            int power = 1;
            if (pos < len && str[pos] == '^') {
                pos++;
                if (pos >= len || !isdigit(str[pos])) {
                    throw std::invalid_argument("Expected digit after '^' in monom: " + str);
                }
                power = 0;
                while (pos < len && isdigit(str[pos])) {
                    int digit = str[pos] - '0';
                    power = power * 10 + digit;
                    pos++;
                }
            }
            p[var_index] = power;
        }
        else {
            pos++;
        }
    }
    return Monom(coeff, p);
}

Polynom& Polynom::operator=(const Polynom& other) {
    if (this != &other) {
        _monoms = other._monoms;
    }
    return *this;
}

bool Polynom::operator==(const Polynom& other) const {
    if (_monoms.count() != other._monoms.count()) return false;

    auto it1 = _monoms.begin(), it2 = other._monoms.begin();
    for (; it1 != _monoms.end(); it1++, it2++) {
        if (*it1 != *it2 || abs(it1->get_coeff() - it2->get_coeff()) > 1e-12) {
            return false;
        }
    }
    return true;
}

bool Polynom::operator!=(const Polynom& other) const { return !(*this == other); }

bool Polynom::operator>(const Polynom& other) const {
    if (_monoms.is_empty()) return false;
    if (other._monoms.is_empty()) return true;

    auto it1 = _monoms.begin(), it2 = other._monoms.begin();
    for (; it1 != _monoms.end() && it2 != other._monoms.end(); it1++, it2++) {
        if (*it1 > *it2) {
            return true;
        }
        if (*it1 < *it2) {
            return false;
        }
    }
    return it1 != _monoms.end();
}

bool Polynom::operator<(const Polynom& other) const { return other > *this; }

Polynom Polynom::operator-() const {
    Polynom res;
    for (auto it = _monoms.begin(); it != _monoms.end(); it++) {
        res.add_monom(-(*it));
    }
    return res;
}

Polynom Polynom::operator+(const Polynom& other) const {
    Polynom res(*this);
    res += other;
    return res;
}

Polynom Polynom::operator-(const Polynom& other) const {
    Polynom res(*this);
    res -= other;
    return res;
}

Polynom Polynom::operator*(const Polynom& other) const {
    Polynom res(*this);
    res *= other;
    return res;
}

Polynom& Polynom::operator+=(const Polynom& other) {
    for (auto it = other._monoms.begin(); it != other._monoms.end(); it++) {
        add_monom(*it);
    }
    return *this;
}

Polynom& Polynom::operator-=(const Polynom& other) {
    *this += (-other);
    return *this;
}

Polynom& Polynom::operator*=(const Polynom& other) {
    Polynom res;
    for (auto it1 = _monoms.begin(); it1 != _monoms.end(); it1++) {
        for (auto it2 = other._monoms.begin(); it2 != other._monoms.end(); it2++) {
            res.add_monom((*it1) * (*it2));
        }
    }
    *this = res;
    return *this;
}

Polynom Polynom::operator+(double scalar) const { 
    Polynom r(*this); 
    r += scalar; 
    return r;
}

Polynom Polynom::operator-(double scalar) const {
    Polynom r(*this); 
    r -= scalar; 
    return r;
}

Polynom Polynom::operator*(double scalar) const { 
    Polynom r(*this);
    r *= scalar;
    return r;
}

Polynom Polynom::operator/(double scalar) const {
    Polynom r(*this);
    r /= scalar; 
    return r; 
}

Polynom& Polynom::operator+=(double scalar) {
    int p[VARS_COUNT] = {};
    add_monom(Monom(scalar, p));
    return *this;
}

Polynom& Polynom::operator-=(double scalar) {
    int p[VARS_COUNT] = {};
    add_monom(Monom(-scalar, p));
    return *this;
}

Polynom& Polynom::operator*=(double scalar) {
    if (abs(scalar) < 1e-12) {
        _monoms.clear();
        int p[VARS_COUNT] = { 0, 0, 0 };
        _monoms.push_back(Monom(0.0, p));
        return *this;
    }

    Node<Monom>* cur = _monoms.head();
    while (cur != nullptr) {
        cur->data *= scalar;
        cur = cur->next;
    }
    return *this;
}

Polynom& Polynom::operator/=(double scalar) {
    if (abs(scalar) < 1e-12) {
        throw std::invalid_argument("Polynom::operator/= : Division by zero!");
    }

    Node<Monom>* cur = _monoms.head();
    while (cur != nullptr) {
        cur->data /= scalar;
        cur = cur->next;
    }
    return *this;
}

Polynom operator*(double scalar, const Polynom& p) { 
    return p * scalar;
}

Polynom operator+(double scalar, const Polynom& p) {
    return p + scalar; 
}

Polynom Polynom::operator+(const Monom& m) const {
    Polynom r(*this);
    r += m;
    return r;
}

Polynom Polynom::operator-(const Monom& m) const {
    Polynom r(*this);
    r -= m; 
    return r;
}

Polynom Polynom::operator*(const Monom& m) const { 
    Polynom r(*this); 
    r *= m; 
    return r;
}

Polynom Polynom::operator/(const Monom& m) const {
    Polynom r(*this);
    r /= m; 
    return r; 
}

Polynom& Polynom::operator+=(const Monom& m) {
    add_monom(m);
    return *this;
}

Polynom& Polynom::operator-=(const Monom& m) {
    add_monom(-m);
    return *this;
}

Polynom& Polynom::operator*=(const Monom& m) {
    Polynom res;
    for (auto it = _monoms.begin(); it != _monoms.end(); it++) {
        res.add_monom((*it) * m);
    }
    if (res._monoms.is_empty()) {
        int p[VARS_COUNT] = {};
        res._monoms.push_back(Monom(0.0, p));
    }
    *this = res;
    return *this;
}

Polynom& Polynom::operator/=(const Monom& m) {
    if (abs(m.get_coeff()) < 1e-12) {
        throw std::invalid_argument("Polynom::operator/= : Division by zero monom!");
    }
    Polynom res;
    for (auto it = _monoms.begin(); it != _monoms.end(); it++) {
        res.add_monom((*it) / m);
    }
    *this = res;
    return *this;
}

Polynom operator+(const Monom& m, const Polynom& p) { 
    return p + m;
}

Polynom operator-(const Monom& m, const Polynom& p) { 
    return -(p - m);
}

Polynom operator*(const Monom& m, const Polynom& p) {
    return p * m; 
}

double Polynom::evaluate(const double values[VARS_COUNT]) const {
    double result = 0.0;
    for (auto it = _monoms.begin(); it != _monoms.end(); it++) {
        result += (*it).evaluate(values);
    }
    return result;
}

double Polynom::calculate(double x, double y, double z) const {
    double values[VARS_COUNT] = { x, y, z };
    return evaluate(values);
}

std::string Polynom::toString() const {
    std::ostringstream out;
    auto it = _monoms.begin();
    if (it != _monoms.end()) {
        out << *it++;
        for (; it != _monoms.end(); it++) {
            if (it->get_coeff() >= 0) {
                out << '+';
            }
            out << *it;
        }
    }
    return out.str();
}

std::ostream& operator<<(std::ostream& out, const Polynom& p) {
    out << p.toString();
    return out;
}

std::istream& operator>>(std::istream& in, Polynom& p) {
    std::string line;
    if (std::getline(in, line)) { p = Polynom(line); }
    return in;
}

void Polynom::add_monom(const Monom& m) {
    if (_monoms.is_empty()) {
        _monoms.push_back(m);
        return;
    }

    if (_monoms.count() == 1 && abs(_monoms.head()->data.get_coeff()) < 1e-12) {
        _monoms.pop_front();
    }       

    if (abs(m.get_coeff()) < 1e-12) return;

    Node<Monom>* prev = nullptr;
    for (auto it = _monoms.begin(); it != _monoms.end(); ++it) {
        if (*it == m) {
            (*it) += m;
            if (abs((*it).get_coeff()) < 1e-12) {
                _monoms.erase(it.get_node());
            }                
            return;
        }
        if (m > *it) {
            if (prev == nullptr) {
                _monoms.push_front(m);
            }
            else {
                _monoms.insert(prev, m);
            }
            return;
        }
        prev = it.get_node();
    }
    _monoms.push_back(m);
}