#include <iostream>
#include <cmath>
#include "point.h"

Point::Point() : _x(0), _y(0) {}

Point::Point(float x, float y) : _x(x), _y(y) {}

Point::Point(const Point& other) : _x(other._x), _y(other._y) {}

void Point::set_x(float x) {
	_x = x;
}

void Point::set_y(float y) {
	_y = y;
}

float Point::get_x() {
	return _x;
}

float Point::get_y() {
	return _y;
}

float Point::distance(const Point& other) const {
	float dx = _x - other._x;
	float dy = _y - other._y;

	return sqrt(dx * dx + dy * dy);
}

bool Point::operator == (const Point& other) const {
	return (_x == other._x) && (_y == other._y);
}

bool Point::operator != (const Point& other) const {
	return !(*this == other);
}

Point& Point::operator = (const Point& other) {
	if (this != &other) {
		_x = other._x;
		_y = other._y;
	}
	return *this;
}