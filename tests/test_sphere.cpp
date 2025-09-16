#include <gtest/gtest.h>
#include "../lib_sphere/sphere.h"

TEST(TestSphereLib, default_constructor_sphere) {
    Sphere sphere;

    EXPECT_TRUE((sphere.get_center() == Point3D(0.0f, 0.0f, 0.0f)) && (sphere.get_r() == 0.0f));
}

TEST(TestSphereLib, init_constructor_sphere) {
    // Arrange
    float x = 10;
    float y = 2;
    float z = 1;
    float radius = 5;
    Point3D p1(x, y, z);

    // Act & Assert
    ASSERT_NO_THROW(Sphere(p1, radius));
}

TEST(TestSphereLib, invalid_init_constructor_sphere) {
    // Arrange
    float x = 10;
    float y = 2;
    float z = 1;
    float radius = -5;
    Point3D p1(x, y, z);

    // Act & Assert
    ASSERT_ANY_THROW(Sphere(p1, radius));
}

TEST(TestSphereLib, copy_constructor_sphere) {
    // Arrange
    float x = 10;
    float y = 2;
    float z = 1;
    float radius = 5;

    Point3D p1(x, y, z);
    Sphere sphere_1(p1, radius);
    Sphere sphere_2(sphere_1);

    // Act
    Sphere actual_result = sphere_2;

    // Assert
    Sphere expected_result = Sphere(Point3D(10, 2, 1), 5);
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestSphereLib, create_sphere_with_zero_radius) {
    // Arrange
    Point3D center(1, 1, 1);

    // Act & Assert
    ASSERT_NO_THROW(Sphere sphere_1(center, 0));
}

TEST(TestSphereLib, equality_of_spheres) {
    // Arrange
    Sphere sphere_1(Point3D(1, 2, 3), 4);
    Sphere sphere_2(Point3D(1, 2, 3), 4);

    // Act & Assert
    EXPECT_TRUE(sphere_1 == sphere_2);
}

TEST(TestSphereLib, not_equality_of_spheres) {
    // Arrange
    Sphere sphere_1(Point3D(1, 2, 3), 4);
    Sphere sphere_2(Point3D(4, 7, 3), 1);

    // Act & Assert
    EXPECT_TRUE(sphere_1 != sphere_2);
}

TEST(TestSphereLib, throw_when_radius_less_by_zero) {
    // Arrange
    Point3D center(1, 1, 1);

    // Act & Assert
    ASSERT_ANY_THROW(Sphere sphere_1(center, -2));
}

TEST(TestSphereLib, no_throw_when_radius_greater_by_zero) {
    // Arrange
    Point3D center(1, 1, 1);

    // Act & Assert
    ASSERT_NO_THROW(Sphere sphere_1(center, 2));
}