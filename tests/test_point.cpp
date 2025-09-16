#include <gtest/gtest.h>
#include "../lib_point/point.h"

#define EPSILON 0.0001

TEST(TestPointLib, default_constructor_point) {
    // Arrange
    Point point;

    // Act & Assert
    EXPECT_TRUE((point.get_x() == 0.0f) && (point.get_y() == 0.0f));
}

TEST(TestPointLib, create_point_with_initializator) {
    // Arrange
    float x = 10;
    float y = 2;

    // Act & Assert
    ASSERT_NO_THROW(Point(x, y));
}

TEST(TestPointLib, copy_constructor_point) {
    // Arrange
    float x = 6;
    float y = 2;

    Point p1(x, y);
    Point p2(p1);

    // Act
    Point actual_result = p2;

    // Assert
    Point expected_result = Point(x, y);
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestPointLib, distance_point) {
    // Arrange
    Point p1(5, 8);
    Point p2(2, 4);

    // Act
    float actual_result = 5;

    // Assert
    float expected_result = p1.distance(p2);
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestPointLib, can_calculate_distance_with_remainder) {
    // Arrange
    Point p1(1, 1);
    Point p2(2, 2);

    // Act
    float actual_result = 1.4142;

    // Assert
    float expected_result = p1.distance(p2);
    EXPECT_NEAR(expected_result, actual_result, EPSILON);
}

TEST(TestPointLib, equality_of_points) { 
    // Arrange
    Point p1(6, 2);
    Point p2(6, 2);

    // Act & Assert
    EXPECT_TRUE(p1 == p2);
}

TEST(TestPointLib, not_equality_of_points) {
    // Arrange
    Point p1(6, 2);
    Point p2(7, 0);

    // Act & Assert
    EXPECT_TRUE(p1 != p2);
}

TEST(TestPointLib, assignment_of_points) {
    // Arrange
    Point p1(0, 0);
    Point p2(6, 2);

    // Act
    p1 = p2;

    // Assert
    EXPECT_EQ(p1, p2);
}
