#include <iostream>
#include "point3d.h"

Point3D::Point3D() : Point(), _z(0) {}

Point3D::Point3D(float x, float y, float z) : Point(x, y), _z(z) {}

Point3D::Point3D(const Point3D& other) : Point(other._x, other._y), _z(other._z) {}

void Point3D::set_z(float z) {
	_z = z;
}

float Point3D::get_z() {
	return _z;
}

float Point3D::distance(const Point3D& other) const {
	float dx = _x - other._x;
	float dy = _y - other._y;
	float dz = _z - other._z;

	return sqrt(dx * dx + dy * dy + dz * dz);
}

bool Point3D::operator == (const Point3D& other) const {
	return (_x == other._x) && (_y == other._y) && (_z == other._z);
}

bool Point3D::operator != (const Point3D& other) const {
	return !(*this == other);
}

Point3D& Point3D::operator = (const Point3D& other) {
	if (this != &other) {
		_x = other._x;
		_y = other._y;
		_z = other._z;
	}
	return *this;
}