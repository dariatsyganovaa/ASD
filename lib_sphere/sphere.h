#ifndef LIB_SPHERE_SPHERE_H_
#define LIB_SPHERE_SPHERE_H_

#pragma once
#include "../lib_point3d/point3d.h"

class Sphere {
	float _r;
	Point3D _center;
public:
	Sphere();
	Sphere(Point3D, float);
	Sphere(const Sphere&);

	void set_r(float);
	void set_center(Point3D);
	float get_r();
	Point3D get_center();

	bool operator == (const Sphere&) const;
	bool operator != (const Sphere&) const;
};

#endif  // LIB_SPHERE_SPHERE_H_