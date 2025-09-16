#include <iostream>
#include <iomanip>

//#define EASY_EXAMPLE
//#define CIRCLE
//#define SPHERE
#define MATRIX


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

#ifdef MATRIX

#include "../lib_matrix/matrix.h"

template <typename T>
Matrix <T> add_matrix(Matrix <T> matrix_1, Matrix <T> matrix_2) {
    Matrix <T> result;
    std::cout << "TBD add_matrix";
    return result;
}

template <typename T>
Matrix <T> sub_matrix(Matrix <T> matrix_1, Matrix <T> matrix_2) {
    Matrix <T> result;
    std::cout << "TBD sub_matrix";
    return result;
}

template <typename T>
Matrix <T> mult_matrix(Matrix <T> matrix_1, Matrix <T> matrix_2) {
    Matrix <T> result;
    std::cout << "TBD mult_matrix";
    return result;
}

int main() {
    int N1, M1;
    int N2, M2;
    std::cout << "Hello! Specify the size of the matrix, where N is the number of rows, M is the number of columns" << std::endl;
    
    std::cout << "Enter the size of your first matrix separated by a space: " ;
    std::cin >> N1 >> M1;
    std::cout << "The size of your first matrix: " << N1 << "*" << M1 << std::endl;

    std::cout << "Enter the size of your second matrix separated by a space: ";
    std::cin >> N2 >> M2;
    std::cout << "The size of your second matrix: " << N2 << "*" << M2 << std::endl << std::endl;

    std::cout << "Select operation (+, -, *) : " << std::endl;
    char operation;
    std::cin >> operation;

    Matrix<int> matrix_1(N1, M1);
    Matrix<int> matrix_2(N2, M2);
    switch (operation) {
    case '+' : 
        add_matrix(matrix_1, matrix_2);
        break;
    case '-': 
        sub_matrix(matrix_1, matrix_2);
        break;
    case '*': 
        mult_matrix(matrix_1, matrix_2);
        break;
    }

    return 0;
}

#endif  // MATRIX