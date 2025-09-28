#include <gtest/gtest.h>
#include "../lib_tvector/tvector.h"

TEST(TestTVectorLib, DefaultConstructor) {
    // Arrange
    // Act & Assert
    ASSERT_NO_THROW(TVector<int> vec);
}

TEST(TestTVectorLib, SizeConstructor) {
    // Arrange
    // Act & Assert
    ASSERT_NO_THROW(TVector<int> vec(7));
}

TEST(TestTVectorLib, SizeZeroConstructor) {
    // Arrange
    // Act & Assert
    ASSERT_NO_THROW(TVector<int> vec(0));
}

TEST(TestTVectorLib, CopyConstructor) {
    // Arrange
    int arr[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    TVector<int> vec1(arr, 9);

    // Act & Assert
    ASSERT_NO_THROW(TVector<int> vec2(vec1));
}

TEST(TestTVectorLib, MassConstructor) {
    // Arrange
    int arr[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    // Act & Assert
    ASSERT_NO_THROW(TVector<int> vec(arr, 9));
}

TEST(TestTVectorLib, MassNullConstructor) {
    // Arrange
    int* arr = nullptr;

    // Act & Assert
    ASSERT_NO_THROW(TVector<int> vec(arr, 0));
}

// Тесты методов доступа
TEST(TestTVectorLib, FrontElement) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);

    // Act & Assert
    ASSERT_NO_THROW(vec.front());
}

TEST(TestTVectorLib, BackElement) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);

    // Act & Assert
    ASSERT_NO_THROW(vec.back());
}

TEST(TestTVectorLib, AtMethod) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);

    // Act & Assert
    ASSERT_NO_THROW(vec.at(0));
}

TEST(TestTVectorLib, BeginIterator) {
    // Arrange
    TVector<int> vec(6);

    // Act & Assert
    ASSERT_NO_THROW(vec.begin());
}

TEST(TestTVectorLib, EndIterator) {
    // Arrange
    int size = 6;
    TVector<int> vec(size);

    // Act & Assert
    ASSERT_NO_THROW(vec.end());
}

// Тесты добавления элементов
TEST(TestTVectorLib, PushBackElement) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);

    // Act & Assert
    ASSERT_NO_THROW(vec.push_back_elem(111));
}

TEST(TestTVectorLib, PushFrontElement) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);

    // Act & Assert
    ASSERT_NO_THROW(vec.push_front_elem(111));
}

TEST(TestTVectorLib, PushBackElements) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    int mass[4] = { 555, 666, 777, 888 };
    TVector<int> vec(arr, 14);

    // Act & Assert
    ASSERT_NO_THROW(vec.push_back_elems(mass, 4));
}

TEST(TestTVectorLib, PushFrontElements) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    int mass[4] = { 555, 666, 777, 888 };
    TVector<int> vec(arr, 14);

    // Act & Assert
    ASSERT_NO_THROW(vec.push_front_elems(mass, 4));
}

TEST(TestTVectorLib, InsertElement) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);

    // Act & Assert
    ASSERT_NO_THROW(vec.insert_elem(111, 3));
}

TEST(TestTVectorLib, InsertElements) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    int mass[4] = { 555, 666, 777, 888 };
    TVector<int> vec(arr, 14);

    // Act & Assert
    ASSERT_NO_THROW(vec.insert_elems(3, mass, 4));
}

// Тесты удаления элементов
TEST(TestTVectorLib, PopBackElement) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);

    // Act & Assert
    ASSERT_NO_THROW(vec.pop_back_elem());
}

TEST(TestTVectorLib, PopFrontElement) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);

    // Act & Assert
    ASSERT_NO_THROW(vec.pop_front_elem());
}

TEST(TestTVectorLib, PopBackElements) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);

    // Act & Assert
    ASSERT_NO_THROW(vec.pop_back_elems(5));
}

TEST(TestTVectorLib, PopFrontElements) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);

    // Act & Assert
    ASSERT_NO_THROW(vec.pop_front_elems(2));
}

TEST(TestTVectorLib, EraseElement) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);

    // Act & Assert
    ASSERT_NO_THROW(vec.erase_elem(4));
}

TEST(TestTVectorLib, EraseElements) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);

    // Act & Assert
    ASSERT_NO_THROW(vec.erase_elems(4, 4));
}

// Тесты специальных методов
TEST(TestTVectorLib, Emplace) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);

    // Act & Assert
    ASSERT_NO_THROW(vec.emplace(6, 111));
}

TEST(TestTVectorLib, Assign) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec1(arr, 14);
    TVector<int> vec2(40);

    // Act & Assert
    ASSERT_NO_THROW(vec2.assign(vec1));
}

TEST(TestTVectorLib, Clear) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);

    // Act & Assert
    ASSERT_NO_THROW(vec.clear());
}

TEST(TestTVectorLib, ShrinkToFit) {
    // Arrange
    TVector<int> vec(16);
    vec.resize(7);

    // Act & Assert
    ASSERT_NO_THROW(vec.shrink_to_fit());
}

TEST(TestTVectorLib, Reserve) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);

    // Act & Assert
    ASSERT_NO_THROW(vec.reserve(17));
}

TEST(TestTVectorLib, Resize) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);

    // Act & Assert
    ASSERT_NO_THROW(vec.resize(25));
}

TEST(TestTVectorLib, ResizeWithValue) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);

    // Act & Assert
    ASSERT_NO_THROW(vec.resize(25, 111));
}

// Тесты операторов
TEST(TestTVectorLib, AssignmentOperator) {
    // Arrange
    int arr[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec1(20);
    TVector<int> vec2(arr, 16);

    // Act & Assert
    ASSERT_NO_THROW(vec1 = vec2);
}

TEST(TestTVectorLib, IndexingOperator) {
    // Arrange
    int arr[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec(arr, 16);

    // Act & Assert
    ASSERT_NO_THROW(vec[0]);
}

// Тесты алгоритмов поиска
TEST(TestTVectorLib, FindFirstElement) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);

    // Act & Assert
    ASSERT_NO_THROW(find_first_elem(vec, 6));
}

TEST(TestTVectorLib, FindLastElement) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 10, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);

    // Act & Assert
    ASSERT_NO_THROW(find_last_elem(vec, 10));
}

TEST(TestTVectorLib, FindElements) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 10, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);
    int count = 0;

    // Act & Assert
    ASSERT_NO_THROW(find_elems(vec, 10, count));
}

TEST(TestTVectorLib, Randomize) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);

    // Act & Assert
    ASSERT_NO_THROW(randomize(vec));
}

TEST(TestTVectorLib, HoaraSort) {
    // Arrange
    int arr[32] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
                   17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 111, 222, 333, 444 };
    TVector<int> vec(arr, 32);
    randomize(vec);

    // Act & Assert
    ASSERT_NO_THROW(hoara_sort(vec));
}

// Тесты с разными типами данных
TEST(TestTVectorLib, StringVector) {
    // Arrange
    // Act & Assert
    ASSERT_NO_THROW(TVector<std::string> vec);
}

TEST(TestTVectorLib, PushBackStringElements) {
    // Arrange
    TVector<std::string> vec;
    std::string items[3] = { "a", "b", "c" };

    // Act & Assert
    ASSERT_NO_THROW(vec.push_back_elems(items, 3));
}

// Комплексные тесты
TEST(TestTVectorLib, MultipleOperations) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);

    // Act & Assert
    ASSERT_NO_THROW({
        vec.push_back_elem(111);
        vec.push_front_elem(222);
        vec.insert_elem(333, 5);
        vec.pop_back_elem();
        vec.pop_front_elem();
        vec.erase_elem(3);
        });
}

TEST(TestTVectorLib, LargeVectorOperations) {
    // Arrange
    const size_t large_size = 1000;
    TVector<int> vec(large_size);

    // Act & Assert
    ASSERT_NO_THROW({
        for (size_t i = 0; i < large_size; i++) {
            vec.emplace(i, i * 2);
        }
        vec.resize(large_size * 2);
        vec.shrink_to_fit();
        });
}