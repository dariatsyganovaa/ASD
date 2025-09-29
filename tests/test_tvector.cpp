#include <gtest/gtest.h>
#include "../lib_tvector/tvector.h"

TEST(TestTVectorLib, default_constructor) {
    TVector<int> vec;
    EXPECT_TRUE((vec.size() == (size_t)0) && (vec.is_empty() == true));
}

TEST(TestTVectorLib, size_constructor) {
    TVector<int> vec(7);
    EXPECT_EQ(vec.size(), 7);
    EXPECT_EQ(vec.capacity(), 15);

    for (size_t i = 0; i < vec.capacity(); i++) {
        EXPECT_EQ(vec.states()[i], empty);
    }
}

TEST(TestTVectorLib, size_null_constructor) {
    TVector<int> vec;
    EXPECT_TRUE((vec.size() == (size_t)0) && (vec.is_empty() == true));
}

TEST(TestTVectorLib, copy_constructor) {
    int arr[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    TVector<int> vec1(arr, 9);
    TVector<int> vec2(vec1);

    EXPECT_EQ(vec2.size(), 9);
    EXPECT_EQ(vec2.capacity(), 15);

    for (size_t i = 0; i < vec2.size(); i++) {
        EXPECT_EQ(vec1.data()[i], vec2.data()[i]);
    }
}

TEST(TestTVectorLib, copy_null_constructor) {
    TVector<int> vec1(0);
    TVector<int> vec2(vec1);

    EXPECT_EQ(vec2.size(), 0);
    EXPECT_EQ(vec2.capacity(), 0);
    EXPECT_TRUE(vec2.is_empty() == true);
}

TEST(TestTVectorLib, mass_constructor) {
    int arr[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    TVector<int> vec(arr, 9);

    EXPECT_EQ(vec.size(), 9);
    EXPECT_EQ(vec.capacity(), 15);

    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_EQ(vec.data()[i], arr[i]);
        EXPECT_EQ(vec.states()[i], busy);
    }
}

TEST(TestTVectorLib, mass_null_constructor) {
    int* arr = nullptr;
    TVector<int> vec(arr, 0);

    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.capacity(), 0);
    EXPECT_TRUE(vec.is_empty() == true);
}

TEST(TestTVectorLib, destructor) {
    TVector<int> vec2;
    vec2.push_back_elem(222);
}

TEST(TestTVectorLib, front_elem) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);
    int expected_res = 1;
    int actual_res = vec.front();

    EXPECT_EQ(expected_res, actual_res);
}

TEST(TestTVectorLib, back_elem) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);
    int expected_res = 14;
    int actual_res = vec.back();

    EXPECT_EQ(expected_res, actual_res);
}

TEST(TestTVectorLib, begin_vector_with_size) { 
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);
    EXPECT_EQ(&vec[0], vec.begin());
}

TEST(TestTVectorLib, begin_empty_vector) {
    TVector<int> empty_vec;
    EXPECT_EQ(empty_vec.end(), empty_vec.begin());
}

TEST(TestTVectorLib, end_vector_with_size) {
    const int size = 14;
    int arr[size] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, size);
    EXPECT_EQ(&vec[size - 1] + 1, vec.end());
}

TEST(TestTVectorLib, end_empty_vector) {
    TVector<int> empty_vec;
    EXPECT_EQ(empty_vec.end(), empty_vec.begin()); 
}

TEST(TestTVectorLib, push_front_elem) { 
    const int size = 6;
    int arr[size];
    for (size_t i = 0; i < size; i++) {
        arr[i] = i + 1;
    }

    TVector<int> vec(arr, size);
    size_t old_capacity = vec.capacity();
    vec.push_front_elem(111);

    EXPECT_EQ(vec.size(), size + 1);
    EXPECT_EQ(vec[0], 111);

    EXPECT_GE(vec.capacity(), old_capacity);

    for (size_t i = 0; i < size; i++) {
        EXPECT_EQ(vec[i+1], arr[i]);
    }
}

TEST(TestTVectorLib, push_front_elems) {
    const int size = 6;
    int arr[size];
    for (size_t i = 0; i < size; i++) {
        arr[i] = i + 1;
    }

    const int count_of_elems = 3;
    int mass[count_of_elems];
    for (size_t i = 0; i < count_of_elems; i++) {
        mass[i] = (i + 1) * 111;
    }

    TVector<int> vec(arr, size);
    size_t old_capacity = vec.capacity();
    vec.push_front_elems(mass, count_of_elems);

    EXPECT_EQ(vec.size(), size + count_of_elems);
    EXPECT_GE(vec.capacity(), old_capacity);

    for (size_t i = 0; i < count_of_elems; i++) {
        EXPECT_EQ(vec[i], mass[i]);
    }

    for (size_t i = 0; i < size; i++) {
        EXPECT_EQ(vec[i + count_of_elems], arr[i]);
    }
}

TEST(TestTVectorLib, push_back_elem) {
    const int size = 6;
    int arr[size];
    for (size_t i = 0; i < size; i++) {
        arr[i] = i + 1;
    }

    TVector<int> vec(arr, size);
    size_t old_capacity = vec.capacity();
    vec.push_back_elem(111);

    EXPECT_EQ(vec.size(), size + 1);
    EXPECT_GE(vec.capacity(), old_capacity);

    for (size_t i = 0; i < size; i++) {
        EXPECT_EQ(vec[i], arr[i]);
    }

    EXPECT_EQ(vec[size], 111);
}

TEST(TestTVectorLib, push_back_elems) {
    const int size = 6;
    int arr[size];
    for (size_t i = 0; i < size; i++) {
        arr[i] = i + 1;
    }

    const int count_of_elems = 3;
    int mass[count_of_elems];
    for (size_t i = 0; i < count_of_elems; i++) {
        mass[i] = (i + 1) * 111;
    }

    TVector<int> vec(arr, size);
    size_t old_capacity = vec.capacity();
    vec.push_back_elems(mass, count_of_elems);

    EXPECT_EQ(vec.size(), size + count_of_elems);
    EXPECT_GE(vec.capacity(), old_capacity);

    for (size_t i = 0; i < size; i++) {
        EXPECT_EQ(vec[i], arr[i]);
    }

    for (size_t i = 0; i < count_of_elems; i++) {
        EXPECT_EQ(vec[size + i], mass[i]);
    }
}
 
TEST(TestTVectorLib, insert_elem) { 
    const int size = 5;
    int index = 2;

    int arr[size];
    for (size_t i = 0; i < size; i++) {
        arr[i] = i + 1;
    }
    
    TVector<int> vec(arr, size);
    size_t old_capacity = vec.capacity();
    vec.insert_elem(111, index);

    EXPECT_EQ(vec.size(), size + 1);
    EXPECT_GE(vec.capacity(), old_capacity);

    for (size_t i = 0; i < index; i++) {
        EXPECT_EQ(vec[i], arr[i]);
    }

    EXPECT_EQ(vec[index], 111);

    for (size_t i = index; i < size; i++) {
        EXPECT_EQ(vec[i + 1], arr[i]);
    }
}

TEST(TestTVectorLib, insert_elems) {
    const int size = 5;
    int index = 2;
    const int count_of_elems = 3;

    int arr[size];
    for (size_t i = 0; i < size; i++) {
        arr[i] = i + 1;
    }

    int mass[count_of_elems];
    for (size_t i = 0; i < count_of_elems; i++) {
        mass[i] = (i + 1) * 111;
    }

    TVector<int> vec(arr, size);
    size_t old_capacity = vec.capacity();
    vec.insert_elems(index, mass, count_of_elems);

    EXPECT_EQ(vec.size(), size + count_of_elems);
    EXPECT_GE(vec.capacity(), old_capacity);

    for (size_t i = 0; i < index; i++) {
        EXPECT_EQ(vec[i], arr[i]);
    }

    for (size_t i = 0; i < count_of_elems; i++) {
        EXPECT_EQ(vec[index + i], mass[i]);
    }

    for (size_t i = index; i < size; i++) {
        EXPECT_EQ(vec[i + count_of_elems], arr[i]);
    }
}

TEST(TestTVectorLib, push_front_elem_in_empty_vec) {
    int expected_result[1] = { 111 };
    TVector<int> vec1, vec2(expected_result, 1);
    vec1.push_front_elem(111);

    EXPECT_EQ(vec1.size(), 1);
    EXPECT_EQ(vec1, vec2);
}

TEST(TestTVectorLib, push_front_elems_in_empty_vec) {
    int expected_result[4] = { 555, 666, 777, 888 };
    int mass[4] = { 555, 666, 777, 888 };
    TVector<int> vec1, vec2(expected_result, 4);
    vec1.push_front_elems(mass, 4);

    EXPECT_EQ(vec1.size(), 4);
    EXPECT_EQ(vec1, vec2);
}

TEST(TestTVectorLib, push_back_elem_in_empty_vec) {
    int expected_result[1] = { 111 };
    TVector<int> vec1, vec2(expected_result, 1);
    vec1.push_back_elem(111);

    EXPECT_EQ(vec1.size(), 1);
    EXPECT_EQ(vec1, vec2);
}

TEST(TestTVectorLib, push_back_elems_in_empty_vec) {
    int expected_result[4] = { 555, 666, 777, 888 };
    int mass[4] = { 555, 666, 777, 888 };
    TVector<int> vec1, vec2(expected_result, 4);
    vec1.push_back_elems(mass, 4);

    EXPECT_EQ(vec1.size(), 4);
    EXPECT_EQ(vec1, vec2);
}

TEST(TestTVectorLib, insert_elem_in_empty_vec) {
    TVector<int> vec1;
    ASSERT_ANY_THROW(vec1.insert_elem(555, 1));
}

TEST(TestTVectorLib, insert_elems_in_empty_vec) {
    TVector<int> vec1;
    int mass[4] = { 555, 666, 777, 888 };
    ASSERT_ANY_THROW(vec1.insert_elems(1, mass, 4));
}

TEST(TestTVectorLib, insert_elem_pos_out_of_range) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec1(arr, 14);
    ASSERT_ANY_THROW(vec1.insert_elem(555, 16));
}

TEST(TestTVectorLib, insert_elems_pos_out_of_range) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec1(arr, 14);
    int mass[4] = { 555, 666, 777, 888 };
    ASSERT_ANY_THROW(vec1.insert_elems(18, mass, 4));
}

TEST(TestTVectorLib, pop_front_elem) {
    const int size = 15;
    int arr[size];
    for (size_t i = 0; i < size; i++) {
        arr[i] = i + 1;
    }

    TVector<int> vec(arr, size);
    vec.pop_front_elem();

    EXPECT_EQ(vec.size(), size - 1);
    EXPECT_EQ(vec.states()[0], deleted);

    for (size_t i = 1; i < size - 1; i++) {
        EXPECT_EQ(vec.states()[i], busy);
    }

    for (size_t i = 0; i < size - 1; i++) {
        EXPECT_EQ(vec[i], arr[i + 1]);
    }
}

TEST(TestTVectorLib, pop_front_elems) {
    const int size = 15;
    int arr[size];
    for (size_t i = 0; i < size; i++) {
        arr[i] = i + 1;
    }

    int count_of_elems = 3;

    TVector<int> vec(arr, size);
    vec.pop_front_elems(count_of_elems);

    EXPECT_EQ(vec.size(), size - count_of_elems);

    for (size_t i = 0; i < count_of_elems; i++) {
        EXPECT_EQ(vec.states()[i], deleted);
    }

    for (size_t i = count_of_elems; i < size - count_of_elems; i++) {
        EXPECT_EQ(vec.states()[i], busy);
    }

    for (size_t i = 0; i < size - count_of_elems; i++) {
        EXPECT_EQ(vec[i], arr[i + count_of_elems]);
    }
}

TEST(TestTVectorLib, pop_front_elem_in_empty_vec) {
    TVector<int> vec1;
    ASSERT_ANY_THROW(vec1.pop_front_elem());
}

TEST(TestTVectorLib, pop_front_elems_in_empty_vec) {
    TVector<int> vec1;
    ASSERT_ANY_THROW(vec1.pop_front_elems(2));
}

TEST(TestTVectorLib, pop_front_elems_count_out_of_range) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec1(arr, 14);
    ASSERT_ANY_THROW(vec1.pop_front_elems(16));
}

TEST(TestTVectorLib, pop_back_elem) {
    const int size = 14;
    int arr[size];
    for (size_t i = 0; i < size; i++) {
        arr[i] = i + 1;
    }

    TVector<int> vec(arr, size);
    vec.pop_back_elem();

    EXPECT_EQ(vec.size(), size - 1);

    for (size_t i = 0; i < size - 1; i++) {
        EXPECT_EQ(vec[i], arr[i]);
    }

    for (size_t i = 0; i < size - 1; i++) {
        EXPECT_EQ(vec.states()[i], busy);
    }

    EXPECT_EQ(vec.states()[size - 1], empty);
}

TEST(TestTVectorLib, pop_back_elems) {
    const int size = 14;
    int arr[size];
    for (size_t i = 0; i < size; i++) {
        arr[i] = i + 1;
    }

    int count_of_elems = 3;

    TVector<int> vec(arr, size);
    vec.pop_back_elems(count_of_elems);

    EXPECT_EQ(vec.size(), size - count_of_elems);

    for (size_t i = 0; i < size - count_of_elems; i++) {
        EXPECT_EQ(vec[i], arr[i]);
    }

    for (size_t i = 0; i < size - count_of_elems; i++) {
        EXPECT_EQ(vec.states()[i], busy);
    }

    for (size_t i = size - count_of_elems; i < size; i++) {
        EXPECT_EQ(vec.states()[i], empty);
    }
}

TEST(TestTVectorLib, pop_back_elem_in_empty_vec) {
    TVector<int> vec1;
    ASSERT_ANY_THROW(vec1.pop_back_elem());
}

TEST(TestTVectorLib, pop_back_elems_in_empty_vec) {
    TVector<int> vec1;
    ASSERT_ANY_THROW(vec1.pop_back_elems(2));
}

TEST(TestTVectorLib, pop_back_elems_count_out_of_range) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec1(arr, 14);
    ASSERT_ANY_THROW(vec1.pop_back_elems(16));
}

TEST(TestTVectorLib, erase_elem) {
    const int size = 5;
    int index = 2;

    int arr[size];
    for (size_t i = 0; i < size; i++) {
        arr[i] = i + 1;
    }

    TVector<int> vec(arr, size);
    vec.erase_elem(index);

    EXPECT_EQ(vec.size(), size - 1);

    for (size_t i = 0; i < index; i++) {
        EXPECT_EQ(vec[i], arr[i]);
        EXPECT_EQ(vec.states()[i], busy);
    }

    EXPECT_EQ(vec.states()[index], deleted);

    for (size_t i = index + 1; i < size; i++) {
        EXPECT_EQ(vec[i - 1], arr[i]);//index?
        EXPECT_EQ(vec.states()[i], busy);
    }
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

//TEST(TestTVectorLib, PushBackStringElements) {
//    // Arrange
//    TVector<std::string> vec;
//    std::string items[3] = { "a", "b", "c" };
//
//    // Act & Assert
//    ASSERT_NO_THROW(vec.push_back_elems(items, 3));
//}

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