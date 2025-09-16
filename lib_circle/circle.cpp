#include <iostream>
#include "circle.h"

Circle::Circle() : _center(0, 0), _r(0) {}

Circle::Circle(Point center, float r) {
	if (r < 0) {
		throw std::invalid_argument("The radius must be greater than zero");
	}
	_r = r;
	_center = center;
}

Circle::Circle(const Circle& other) : _center(other._center), _r(other._r) {}

void Circle::set_r(float r) {
	_r = r;
}

void Circle::set_center(Point center) {
	_center = center;
}

float Circle::get_r() {
	return _r;
}

Point Circle::get_center() {
	return _center;
}

bool Circle::operator == (const Circle& other) const {
	return (_center == other._center) && (_r == other._r);
}

bool Circle::operator != (const Circle& other) const {
	return !(*this == other);
}
