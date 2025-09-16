#include <iostream>
#include "sphere.h"

Sphere::Sphere() : _center(0, 0, 0), _r(0) {}

Sphere::Sphere(Point3D center, float r) {
	if (r < 0) {
		throw std::invalid_argument("The radius must be greater than zero");
	}
	_r = r;
	_center = center;
}

Sphere::Sphere(const Sphere& other) : _center(other._center), _r(other._r) {}

void Sphere::set_r(float r) {
	_r = r;
}

void Sphere::set_center(Point3D center) {
	_center = center;
}

float Sphere::get_r() {
	return _r;
}

Point3D Sphere::get_center() {
	return _center;
}

bool Sphere::operator == (const Sphere& other) const {
	return (_center == other._center) && (_r == other._r);
}

bool Sphere::operator != (const Sphere& other) const {
	return !(*this == other);
}
