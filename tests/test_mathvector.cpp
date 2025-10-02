#include <gtest/gtest.h>
#include "../lib_mathvector/mathvector.h"

TEST(TestMathVectorLib, default_constructor) {
    MathVector<int> vec;
    EXPECT_TRUE((vec.size() == (size_t)0) && (vec.is_empty() == true) && (vec.start_index() == (size_t)0));
}

TEST(TestMathVectorLib, size_constructor) {
    MathVector<int> vec(7);
    EXPECT_EQ(vec.size(), 7);
    EXPECT_EQ(vec.capacity(), 15);
    EXPECT_EQ(vec.start_index(), 0);

    for (size_t i = 0; i < vec.capacity(); i++) {
        EXPECT_EQ(vec.states()[i], empty);
    }
}

TEST(TestMathVectorLib, size_constructor_with_start_index) {
    MathVector<int> vec(7, 0);
    EXPECT_EQ(vec.size(), 7);
    EXPECT_EQ(vec.capacity(), 15);
    EXPECT_EQ(vec.start_index(), 0);

    for (size_t i = 0; i < vec.capacity(); i++) {
        EXPECT_EQ(vec.states()[i], empty);
    }
}

TEST(TestMathVectorLib, DotProductOperator) {
    // Тест 1: Умножение векторов одинакового размера
    MathVector<int> vec1(3);
    MathVector<int> vec2(3);
    
    vec1[0] = 1; vec1[1] = 2; vec1[2] = 3;
    vec2[0] = 4; vec2[1] = 5; vec2[2] = 6;
    
    int result = vec1 * vec2;
    EXPECT_EQ(result, 32); // 1*4 + 2*5 + 3*6 = 4 + 10 + 18 = 32
}

TEST(TestMathVectorLib, DotProductWithZero) {
    // Тест 3: Умножение с нулевыми элементами
    MathVector<int> vec1(3);
    MathVector<int> vec2(3);
    
    vec1[0] = 1; vec1[1] = 0; vec1[2] = 3;
    vec2[0] = 0; vec2[1] = 5; vec2[2] = 0;
    
    int result = vec1 * vec2;
    EXPECT_EQ(result, 0); // 1*0 + 0*5 + 3*0 = 0
}

TEST(TestMathVectorLib, DotProductEmptyVectors) {
    // Тест 4: Умножение пустых векторов
    MathVector<int> vec1(0);
    MathVector<int> vec2(0);
    
    int result = vec1 * vec2;
    EXPECT_EQ(result, 0); // Сумма нуля элементов = 0
}

TEST(TestMathVectorLib, DotProductCommutative) {
    // Тест 5: Проверка коммутативности
    MathVector<int> vec1(3);
    MathVector<int> vec2(3);
    
    vec1[0] = 2; vec1[1] = 3; vec1[2] = 4;
    vec2[0] = 5; vec2[1] = 6; vec2[2] = 7;
    
    int result1 = vec1 * vec2;
    int result2 = vec2 * vec1;
    EXPECT_EQ(result1, result2); // Должны быть равны
}

TEST(TestMathVectorLib, AccessOperators) {
    // Тест 6: Проверка работы операторов доступа
    MathVector<int> vec(3);
    vec[0] = 10;
    vec[1] = 20;
    vec[2] = 30;
    
    EXPECT_EQ(vec[0], 10);
    EXPECT_EQ(vec[1], 20);
    EXPECT_EQ(vec[2], 30);
}

TEST(TestMathVectorLib, SizeMethod) {
    // Тест 7: Проверка метода size()
    MathVector<int> vec(5);
    EXPECT_EQ(vec.size(), 5);
    
    MathVector<int> vec_empty(0);
    EXPECT_EQ(vec_empty.size(), 0);
}
