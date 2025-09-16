#pragma once
class Point {
protected:
	float _x;
	float _y;
public:
	Point();
	Point(float, float);
	Point(const Point&);

	void set_x(float);
	void set_y(float);

	float get_x();
	float get_y();

	float distance(const Point&) const;

	bool operator == (const Point&) const;
	bool operator != (const Point&) const;
	Point& operator = (const Point&);
};