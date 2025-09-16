#include <gtest/gtest.h>
#include "../lib_circle/circle.h"

TEST(TestCircleLib, default_constructor_circle) {
    Circle circle;

    EXPECT_TRUE((circle.get_center() == Point(0.0f, 0.0f)) && (circle.get_r() == 0.0f));
}

TEST(TestCircleLib, init_constructor_circle) {
    // Arrange
    float x = 10;
    float y = 2;
    float radius = 5;
    Point p1(x, y);

    // Act & Assert
    ASSERT_NO_THROW(Circle(p1, radius));
}

TEST(TestCircleLib, invalid_init_constructor_circle) {
    // Arrange
    float x = 10;
    float y = 2;
    float radius = -5;
    Point p1(x, y);

    // Act & Assert
    ASSERT_ANY_THROW(Circle(p1, radius));
}

TEST(TestCircleLib, copy_constructor_circle) {
    // Arrange
    float x = 10;
    float y = 2;
    float radius = 5;

    Point p1(x, y);
    Circle circle_1(p1, radius);
    Circle circle_2(circle_1);

    // Act
    Circle actual_result = circle_2;

    // Assert
    Circle expected_result = Circle(Point(10, 2), 5);
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestCircleLib, create_circle_with_zero_radius) {
    // Arrange
    Point center(1, 1);

    // Act & Assert
    ASSERT_NO_THROW(Circle circle_1(center, 0));
}

TEST(TestCircleLib, equality_of_circles) {
    // Arrange
    Circle circle_1(Point(6, 2), 2);
    Circle circle_2(Point(6, 2), 2);

    // Act & Assert
    EXPECT_TRUE(circle_1 == circle_2);
}

TEST(TestCircleLib, not_equality_of_circles) {
    // Arrange
    Circle circle_1(Point(6, 2), 5);
    Circle circle_2(Point(1, 3), 4);

    // Act & Assert
    EXPECT_TRUE(circle_1 != circle_2);
}

TEST(TestCircleLib, throw_when_radius_less_by_zero) {
    // Arrange
    Point center (1, 1);

    // Act & Assert
    ASSERT_ANY_THROW(Circle circle_1(center, -2));
}

TEST(TestCircleLib, no_throw_when_radius_greater_by_zero) {
    // Arrange
    Point center(1, 1);

    // Act & Assert
    ASSERT_NO_THROW(Circle circle_1(center, 2));
}