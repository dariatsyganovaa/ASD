#ifndef LIB_CIRCLE_CIRCLE_H_
#define LIB_CIRCLE_CIRCLE_H_

#pragma once
#include "..\lib_point\point.h"

class Circle {
	float _r;
	Point _center;
public:
	Circle();
	Circle(Point, float);
	Circle(const Circle&);

	void set_r(float);
	void set_center(Point);
	float get_r();
	Point get_center();

	bool operator == (const Circle&) const;
	bool operator != (const Circle&) const;
};

#endif  // LIB_CIRCLE_CIRCLE_H_