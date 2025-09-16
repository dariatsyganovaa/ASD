#pragma once
#include "../lib_point/point.h"

class Point3D : public Point {
	float _z;
public:
	Point3D();
	Point3D(float, float, float);
	Point3D(const Point3D&);

	void set_z(float);
	float get_z();

	float distance(const Point3D&) const;

	bool operator == (const Point3D&) const;
	bool operator != (const Point3D&) const;
	Point3D& operator = (const Point3D&);
};