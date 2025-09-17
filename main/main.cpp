#include <iostream>
#include <iomanip>

//#define EASY_EXAMPLE
//#define CIRCLE
#define SPHERE

#ifdef EASY_EXAMPLE

#include "../lib_easy_example/easy_example.h"

int main() {
    int a, b;
    float result;

    a = 1; b = 4;

    try {
        result = division(a, b);
        std::cout << a << " / " << b << " = "
            << std::setprecision(2) << result << std::endl;
    }
    catch (std::exception err) {
        std::cerr << err.what() << std::endl;
    }

    a = 1; b = 0;

    try {
        result = division(a, b);
        std::cout << a << " / " << b << " = "
            << std::setprecision(2) << result << std::endl;
    }
    catch (std::exception err) {
        std::cerr << err.what() << std::endl;
    }

    return 0;
}

#endif  // EASY_EXAMPLE

#ifdef CIRCLE

#include "../lib_circle/circle.h"
#include "../lib_point/point.h"

enum PointType { Intersect, NotIntersect, Coincidence, PointMatch, Inside };

PointType arrangement_circles(Circle circle_1, Circle circle_2) {
    Point center1 = circle_1.get_center();
    float r1 = circle_1.get_r();

    Point center2 = circle_2.get_center();
    float r2 = circle_2.get_r();

    if (center1.distance(center2) > r1 + r2) {
        return NotIntersect;
    }
    else if (center1.distance(center2) < r1 - r2) {
        return Inside;
    }
    else if ((center1.distance(center2) < r1 + r2) && (center1.distance(center2) > r1 - r2)) {
        return Intersect;
    }
    else if (center1.distance(center2) == r1 + r2) {
        return PointMatch;
    }
    else if (r1 == r2 && center1.distance(center2) == 0) {
        return Coincidence;
    }
}

std::string PointTypeToString(PointType type) {
    switch (type) {
    case Intersect: return "Intersect"; 
    case NotIntersect: return "NotIntersect";
    case Coincidence: return "Coincidence";
    case PointMatch: return "PointMatch";
    case Inside: return "Inside";
    }
}

int main() {
    int x1, y1, radius1;
    int x2, y2, radius2;

    x1 = 1; y1 = 4; radius1 = 5;
    x2 = 1; y2 = 4; radius2 = 5;

    try {
        Point point_1(x1, y1);
        Circle circle_1(point_1, radius1);

        Point point_2(x2, y2);
        Circle circle_2(point_2, radius2);

        PointType result = arrangement_circles(circle_1, circle_2);
        std::cout << "PointType: " << PointTypeToString(result) << std::endl;
    }
    catch (std::exception err) {
        std::cerr << err.what() << std::endl;
    }

    x1 = 1; y1 = 4; radius1 = -5;
    x2 = 1; y2 = 4; radius2 = 5;

    try {
        Point point_1(x1, y1);
        Circle circle_1(point_1, radius1);

        Point point_2(x2, y2);
        Circle circle_2(point_2, radius2);

        PointType result = arrangement_circles(circle_1, circle_2);
        std::cout << " PointType " << PointTypeToString(result) << std::endl;
    }
    catch (std::exception err) {
        std::cerr << err.what() << std::endl;
    }

	return 0;
}

#endif  // CIRCLE

#ifdef SPHERE

#include "../lib_sphere/sphere.h"
#include "../lib_point3d/point3d.h"

enum PointType { Intersect, NotIntersect, Coincidence, PointMatch, Inside };

PointType arrangement_spheres(Sphere sphere_1, Sphere sphere_2) {
    Point3D center1 = sphere_1.get_center();
    float r1 = sphere_1.get_r();

    Point3D center2 = sphere_2.get_center();
    float r2 = sphere_2.get_r();

    if (center1.distance(center2) > r1 + r2) {
        return NotIntersect;
    }
    else if (center1.distance(center2) < r1 - r2) {
        return Inside;
    }
    else if ((center1.distance(center2) < r1 + r2) && (center1.distance(center2) > r1 - r2)) {
        return Intersect;
    }
    else if (center1.distance(center2) == r1 + r2) {
        return PointMatch;
    }
    else if (r1 == r2 && center1.distance(center2) == 0) {
        return Coincidence;
    }
}

std::string PointTypeToString(PointType type) {
    switch (type) {
    case Intersect: return "Intersect";
    case NotIntersect: return "NotIntersect";
    case Coincidence: return "Coincidence";
    case PointMatch: return "PointMatch";
    case Inside: return "Inside";
    }
}

int main() {
    int x1, y1, z1, radius1;
    int x2, y2, z2, radius2;

    x1 = 1; y1 = 4; z1 = 0; radius1 = 5;
    x2 = 1; y2 = 4; z2 = 1; radius2 = 5;

    try {
        Point3D point_1(x1, y1, z1);
        Sphere sphere_1(point_1, radius1);

        Point3D point_2(x2, y2, z2);
        Sphere sphere_2(point_2, radius2);

        PointType result = arrangement_spheres(sphere_1, sphere_2);
        std::cout << "PointType: " << PointTypeToString(result) << std::endl;
    }
    catch (std::exception err) {
        std::cerr << err.what() << std::endl;
    }

    x1 = 1; y1 = 4; z1 = 0; radius1 = -5;
    x2 = 1; y2 = 4; z2 = 1; radius2 = 5;

    try {
        Point3D point_1(x1, y1, z1);
        Sphere sphere_1(point_1, radius1);

        Point3D point_2(x2, y2, z2);
        Sphere sphere_2(point_2, radius2);

        PointType result = arrangement_spheres(sphere_1, sphere_2);
        std::cout << "PointType: " << PointTypeToString(result) << std::endl;
    }
    catch (std::exception err) {
        std::cerr << err.what() << std::endl;
    }
    return 0;
}

#endif  // SPHERE