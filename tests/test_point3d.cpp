#include <gtest/gtest.h>
#include "../lib_point3d/point3d.h"

#define EPSILON 0.0001

TEST(TestPoint3DLib, default_constructor_point3d) {
    Point3D point;

    EXPECT_TRUE((point.get_x() == 0.0f) && (point.get_y() == 0.0f) && (point.get_z() == 0.0f));
}

TEST(TestPoint3DLib, create_point3d_with_initializator) {
    // Arrange
    float x = 10;
    float y = 2;
    float z = 5;

    // Act & Assert
    ASSERT_NO_THROW(Point3D(x, y, z));
}

TEST(TestPoint3DLib, copy_constructor_point3d) {
    // Arrange
    float x = 6;
    float y = 2;
    float z = 3;
    Point3D p1(x, y, z);
    Point3D p2(p1);

    // Act
    Point3D actual_result = p2;

    // Assert
    Point3D expected_result = Point3D(x, y, z);
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestPoint3DLib, distance_point3d) {
    // Arrange
    Point3D p1(5, 2, 1);
    Point3D p2(5, 2, 1);

    // Act
    float actual_result = 0;

    // Assert
    float expected_result = p1.distance(p2);
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestPoint3DLib, can_calculate_distance_with_remainder) {
    // Arrange
    Point3D p1(1, 1, 1);
    Point3D p2(2, 2, 2);

    // Act
    float actual_result = 1.732;

    // Assert
    float expected_result = p1.distance(p2);
    EXPECT_NEAR(expected_result, actual_result, EPSILON);
}

TEST(TestPoint3DLib, equality_of_points3d) {
    // Arrange
    Point3D p1(5, 2, 1);
    Point3D p2(5, 2, 1);

    // Act & Assert
    EXPECT_TRUE(p1 == p2);
}

TEST(TestPoint3DLib, not_equality_of_points3d) {
    // Arrange
    Point3D p1(-6, -18, 1);
    Point3D p2(6, 18, -1);

    // Act & Assert
    EXPECT_TRUE(p1 != p2);
}

TEST(TestPoint3DLib, assignment_of_points3d) {
    // Arrange
    Point3D p1(0, 0, 0);
    Point3D p2(6, 3, 1);

    // Act
    p1 = p2;

    // Assert
    EXPECT_EQ(p1, p2);
}
