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

    for (size_t i = index; i < size; i++) {
        if (i < size - 1) {
            EXPECT_EQ(vec[i], arr[i + 1]);
        }
        if (i == index) {
            EXPECT_EQ(vec.states()[i], deleted);
        }
        else {
            EXPECT_EQ(vec.states()[i], busy);
        }
    }
}

TEST(TestTVectorLib, erase_elems) {
    const int size = 10;
    int index = 2;
    int count_of_elems = 4;

    int arr[size];
    for (size_t i = 0; i < size; i++) {
        arr[i] = i + 1;
    }

    TVector<int> vec(arr, size);
    vec.erase_elems(index, count_of_elems);

    EXPECT_EQ(vec.size(), size - count_of_elems);

    for (size_t i = 0; i < index; i++) {
        EXPECT_EQ(vec[i], arr[i]);
        EXPECT_EQ(vec.states()[i], busy);
    }

    //EXPECT_EQ(vec.states()[index], deleted);

    for (size_t i = index; i < size - count_of_elems; i++) {
        EXPECT_EQ(vec[i], arr[i + count_of_elems]);
        EXPECT_EQ(vec.states()[i], busy);
    }
}

TEST(TestTVectorLib, erase_elem_in_empty_vec) {
    TVector<int> vec1;
    ASSERT_ANY_THROW(vec1.erase_elem(2));
}

TEST(TestTVectorLib, erase_elems_in_empty_vec) {
    TVector<int> vec1;
    ASSERT_ANY_THROW(vec1.erase_elems(4, 2));
}

TEST(TestTVectorLib, erase_elem_pos_out_of_range) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec1(arr, 14);
    ASSERT_ANY_THROW(vec1.erase_elem(16));
}

TEST(TestTVectorLib, erase_elems_pos_out_of_range) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec1(arr, 14);
    ASSERT_ANY_THROW(vec1.erase_elems(-1, 10));
}

TEST(TestTVectorLib, emplace) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec1(arr, 14);
    vec1.emplace(6, 111);
    int expected_res[14] = { 1, 2, 3, 4, 5, 6, 111, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec2(expected_res, 14);

    EXPECT_EQ(vec1, vec2);
}

TEST(TestTVectorLib, emplace_in_empty_vec) {
    TVector<int> vec1;
    ASSERT_ANY_THROW(vec1.emplace(1, 111));
}

TEST(TestTVectorLib, emplace_pos_out_of_range) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec1(arr, 14);
    ASSERT_ANY_THROW(vec1.emplace(15, 111));
}

TEST(TestTVectorLib, emplace_after_pop_front_elem) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec1(arr, 14);
    vec1.pop_front_elem();
    vec1.emplace(1, 111);

    int expected_result[13] = { 2, 111, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };

    EXPECT_EQ(vec1.size(), 13);
    for (size_t i = 0; i < 13; i++) {
        EXPECT_EQ(vec1[i], expected_result[i]);
    }
}

TEST(TestTVectorLib, assign) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec1(arr, 14);
    TVector<int> vec2(40);
    vec2.assign(vec1);

    for (size_t i = 0; i < 14; i++) {
        EXPECT_EQ(vec2[i], arr[i]);
    }
}

TEST(TestTVectorLib, assign_in_empty_vec) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec1(arr, 14);
    TVector<int> vec2;
    vec2.assign(vec1);

    for (size_t i = 0; i < 14; i++) {
        EXPECT_EQ(vec2[i], arr[i]);
    }
}

TEST(TestTVectorLib, assign_with_null_size) {
    TVector<int> vec1;
    TVector<int> vec2(20);
    vec2.assign(vec1);

    EXPECT_EQ(vec2.size(), 0);
}

TEST(TestTVectorLib, assign_to_large_vec) {
    const size_t large_size = 1000000;
    int* large_arr = new int[large_size];
    for (size_t i = 0; i < large_size; i++) {
        large_arr[i] = i + 1;
    }

    TVector<int> vec1(large_arr, large_size);
    TVector<int> vec2;
    vec2.assign(vec1);

    EXPECT_EQ(vec2.size(), large_size);

    for (size_t i = 0; i < large_size; i += 100000) {
        EXPECT_EQ(vec2[i], large_arr[i]);
    }

    delete[] large_arr;
}

TEST(TestTVectorLib, repeat_assign) {
    int arr1[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int arr2[4] = { 11, 12, 13, 14 };

    TVector<int> vec11(arr1, 10);
    TVector<int> vec12(arr2, 4);
    TVector<int> vec2(5);

    vec2.assign(vec11);
    vec2.assign(vec12);

    EXPECT_EQ(vec2.size(), 4);

    for (size_t i = 0; i < 4; i++) {
        EXPECT_EQ(vec2[i], arr2[i]);
    }
}

TEST(TestTVectorLib, at) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec1(arr, 14);
    EXPECT_EQ(vec1.at(0), 1);
}

TEST(TestTVectorLib, at_index_out_of_range) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec1(arr, 14);
    ASSERT_ANY_THROW(vec1.at(15));
}

TEST(TestTVectorLib, at_with_an_invalid_elem) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec1(arr, 14);
    vec1.erase_elems(5, 10);
    ASSERT_ANY_THROW(vec1.at(9));
}

TEST(TestTVectorLib, at_in_empty_vec) {
    TVector<int> vec1;
    ASSERT_ANY_THROW(vec1.at(0));
}

TEST(TestTVectorLib, clear) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec1(arr, 14);
    vec1.pop_front_elems(2);
    vec1.clear();
    EXPECT_EQ(vec1.size(), 0);
}

TEST(TestTVectorLib, shrink_to_fit) {
    TVector<int> vec1(16);
    vec1.resize(7);
    vec1.shrink_to_fit();
    EXPECT_EQ(vec1.capacity(), 7);
}

TEST(TestTVectorLib, shrink_to_fit_with_null_size) {
    TVector<int> vec1;
    vec1.shrink_to_fit();
    EXPECT_EQ(vec1.size(), 0);
}

TEST(TestTVectorLib, reserve) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec1(arr, 14);
    vec1.reserve(17);
    EXPECT_EQ(vec1.capacity(), 17);
}

TEST(TestTVectorLib, reserve_return) {
    TVector<int> vec1(40);
    vec1.reserve(16);
    EXPECT_EQ(vec1.capacity(), 45);
}

TEST(TestTVectorLib, reserve_in_empty_vec) {
    TVector<int> vec1;
    vec1.reserve(20);
    EXPECT_EQ(vec1.capacity(), 20);
    EXPECT_NE(vec1.data(), nullptr);
    EXPECT_EQ(vec1.size(), 0);

    for (size_t i = 0; i < 20; i++) {
        EXPECT_EQ(vec1.states()[i], empty);
    }
}

TEST(TestTVectorLib, resize_increasing_the_size) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec1(arr, 14);
    vec1.resize(25);

    EXPECT_EQ(vec1.size(), 25);

    for (size_t i = 0; i < 4; i++) {
        EXPECT_EQ(vec1[i], arr[i]);
    }
}

TEST(TestTVectorLib, resize_reducing_the_size) {
    int arr[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec1(arr, 16);
    vec1.resize(5);
    EXPECT_EQ(vec1.size(), 5);
}

TEST(TestTVectorLib, resize_increasing_the_size_with_value) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec1(arr, 14);
    vec1.resize(25, 111);
    EXPECT_EQ(vec1.size(), 25);
}

TEST(TestTVectorLib, resize_in_empty_vec) {
    TVector<int> vec1;
    vec1.resize(5);
    EXPECT_EQ(vec1.size(), 5);
}

TEST(TestTVectorLib, resize_in_empty_vec_with_value) {
    TVector<int> vec1;
    vec1.resize(5, 111);
    EXPECT_EQ(vec1.size(), 5);
    for (size_t i = 0; i < 5; i++) {
        EXPECT_EQ(vec1.data()[i], 111);
    }
}

TEST(TestTVectorLib, the_assignment_operator) {
    int arr[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec1(20);
    TVector<int> vec2(arr, 16);
    vec1 = vec2;

    EXPECT_EQ(vec1.size(), 16);
    for (size_t i = 0; i < 16; i++) {
        EXPECT_EQ(vec1.data()[i], arr[i]);
    }
    for (size_t i = 0; i < 16; i++) {
        EXPECT_EQ(vec1.states()[i], busy);
    }
}

TEST(TestTVectorLib, the_assignment_operator_for_empty_vec) {
    int arr[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec1(arr, 16);
    TVector<int> vec2;
    vec1 = vec2;
    EXPECT_EQ(vec1.size(), 0);
}

TEST(TestTVectorLib, comparison_operator) {
    int arr[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec1(arr, 16);
    TVector<int> vec2(vec1);
    EXPECT_TRUE(vec1 == vec2);
    EXPECT_FALSE(vec1 != vec2);
}

TEST(TestTVectorLib, comparison_operator_for_empty_vec) {
    TVector<int> vec1;
    TVector<int> vec2;
    EXPECT_TRUE(vec1 == vec2);
    EXPECT_FALSE(vec1 != vec2);
}

TEST(TestTVectorLib, comparison_operator_after_push) {
    int arr1[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec1(arr1, 16);
    int arr2[17] = { 111, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec2(arr2, 17);
    vec1.push_front_elem(111);
    EXPECT_TRUE(vec1 == vec2);
    EXPECT_EQ(vec1.size(), 17);
    EXPECT_EQ(vec2.size(), 17);
}

TEST(TestTVectorLib, indexing_operator) {
    int arr1[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec1(arr1, 16);
    int expected_res = 1;
    int actual_res = vec1[0];
    EXPECT_EQ(expected_res, actual_res);
}

TEST(TestTVectorLib, indexing_operator_modification) {
    int arr1[3] = { 1, 2, 3 };
    TVector<int> vec1(arr1, 3);
    vec1[1] = 100;
    EXPECT_EQ(vec1[0], 1);
    EXPECT_EQ(vec1[1], 100);
    EXPECT_EQ(vec1[2], 3);
}

TEST(TestTVectorLib, find_first_elem) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec1(arr, 14);
    int actual_res = find_first_elem(vec1, 6);
    int expected_res = 5;
    EXPECT_EQ(expected_res, actual_res);
}

TEST(TestTVectorLib, not_find_first_elem) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec1(arr, 14);
    int actual_res = find_first_elem(vec1, 111);
    int expected_res = -1;
    EXPECT_EQ(expected_res, actual_res);
}

TEST(TestTVectorLib, find_last_elem) {
    int arr[14] = { 1, 2, 3, 4, 5, 10, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec1(arr, 14);
    int actual_res = find_last_elem(vec1, 10);
    int expected_res = 9;
    EXPECT_EQ(expected_res, actual_res);
}

TEST(TestTVectorLib, not_find_last_elem) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec1(arr, 14);
    int actual_res = find_last_elem(vec1, 111);
    int expected_res = -1;
    EXPECT_EQ(expected_res, actual_res);
}

TEST(TestTVectorLib, find_elems) {
    int arr[14] = { 1, 2, 3, 4, 5, 10, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec1(arr, 14);
    int count = 0;
    int* actual_res = find_elems(vec1, 10, count);
    int expected_res[2] = { 5, 9 };
    for (int i = 0; i < 2; i++) {
        EXPECT_EQ(actual_res[i], expected_res[i]);
    }
}

TEST(TestTVectorLib, not_find_elems) {
    int arr[14] = { 1, 2, 3, 4, 5, 10, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec1(arr, 14);
    int count = 0;
    int* actual_res = find_elems(vec1, 111, count);

    EXPECT_EQ(actual_res, nullptr);
    EXPECT_EQ(count, 0);
}

TEST(TestTVectorLib, find_first_elem_in_empty_vec) {
    TVector<int> vec1;
    ASSERT_ANY_THROW(find_first_elem(vec1, 6));
}

TEST(TestTVectorLib, find_last_elem_in_empty_vec) {
    TVector<int> vec1;
    ASSERT_ANY_THROW(find_last_elem(vec1, 6));
}

TEST(TestTVectorLib, find_elems_in_empty_vec) {
    TVector<int> vec1;
    int count = 0;
    ASSERT_ANY_THROW(find_elems(vec1, 6, count));
}

TEST(TestTVectorLib, randomize) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec1(arr, 14);
    randomize(vec1);

    EXPECT_EQ(vec1.size(), 14);
    EXPECT_EQ(vec1.capacity(), 15);
}

TEST(TestTVectorLib, randomize_in_empty_vec) {
    TVector<int> vec1;
    randomize(vec1);

    EXPECT_EQ(vec1.size(), 0);
    EXPECT_EQ(vec1.capacity(), 0);
}

TEST(TestTVectorLib, randomize_one_elem) {
    TVector<int> vec1(1);
    randomize(vec1);

    EXPECT_EQ(vec1.size(), 1);
    EXPECT_EQ(vec1.capacity(), 15);
}

TEST(TestTVectorLib, pop_front_elem_after_push_front_elem) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    int expected_result[15] = { 2, 1, 1, 1, 1, 1,1, 1, 1, 1, 1, 1, 1, 1, 1 };
    TVector<int> vec1(arr, 14), vec2(expected_result, 15);
    vec1.push_front_elem(4);
    vec1.pop_front_elem();

    EXPECT_EQ(vec1.size(), 14);

    for (size_t i = 0; i < 15; i++) {
        EXPECT_EQ(vec1.states()[i], expected_result[i]);
    }
}

TEST(TestTVectorLib, pop_back_elem_after_push_back_elem) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    int expected_result[15] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 };
    TVector<int> vec1(arr, 14), vec2(expected_result, 15);
    vec1.push_back_elem(4);
    vec1.pop_back_elem();

    EXPECT_EQ(vec1.size(), 14);

    for (size_t i = 0; i < 15; i++) {
        EXPECT_EQ(vec1.states()[i], expected_result[i]);
    }
}

TEST(TestTVectorLib, erase_elem_after_insert_elem) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    int expected_result[15] = { 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    TVector<int> vec1(arr, 14), vec2(expected_result, 15);
    vec1.insert_elem(4, 4);
    vec1.erase_elem(4);

    EXPECT_EQ(vec1.size(), 14);

    for (size_t i = 0; i < 15; i++) {
        EXPECT_EQ(vec1.states()[i], expected_result[i]);
    }
}

TEST(TestTVectorLib, pop_front_elems_after_push_front_elems) {
    int arr1[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    int arr2[2] = { 1, 2 };
    int expected_result[18] = { 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    TVector<int> vec1(arr1, 16), vec2(expected_result, 18);
    vec1.push_front_elems(arr2, 2);
    vec1.pop_front_elems(2);

    EXPECT_EQ(vec1.size(), 16);

    for (size_t i = 0; i < 18; i++) {
        EXPECT_EQ(vec1.states()[i], expected_result[i]);
    }
}

TEST(TestTVectorLib, pop_back_elems_after_push_back_elems) {
    int arr1[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    int arr2[2] = { 1, 2 };
    int expected_result[18] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 };
    TVector<int> vec1(arr1, 16), vec2(expected_result, 18);
    vec1.push_back_elems(arr2, 2);
    vec1.pop_back_elems(2);

    EXPECT_EQ(vec1.size(), 16);

    for (size_t i = 0; i < 18; i++) {
        EXPECT_EQ(vec1.states()[i], expected_result[i]);
    }
}

TEST(TestTVectorLib, erase_elems_after_insert_elems) {
    int arr1[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    int arr2[2] = { 1, 2 };
    int expected_result[18] = { 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    TVector<int> vec1(arr1, 16);
    vec1.insert_elems(3, arr2, 2);
    vec1.erase_elems(3, 2);

    EXPECT_EQ(vec1.size(), 16);

    for (size_t i = 0; i < 18; i++) {
        EXPECT_EQ(vec1.states()[i], expected_result[i]);
    }
}

TEST(TestTVectorLib, pop_front_elem_after_emplace_elem) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    int expected_result[14] = { 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    TVector<int> vec1(arr, 14), vec2(expected_result, 14);
    vec1.emplace(1, 5);
    vec1.pop_front_elem();

    EXPECT_EQ(vec1.size(), 13);

    for (int i = 0; i < 14; i++) {
        EXPECT_EQ(vec1.states()[i], expected_result[i]);
    }
}

TEST(TestTVectorLib, pop_back_elem_after_emplace_elem) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    int expected_result[14] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 };
    TVector<int> vec1(arr, 14), vec2(expected_result, 14);
    vec1.emplace(13, 5);
    vec1.pop_back_elem();

    EXPECT_EQ(vec1.size(), 13);

    for (int i = 0; i < 14; i++) {
        EXPECT_EQ(vec1.states()[i], expected_result[i]);
    }
}

TEST(TestTVectorLib, erase_elem_after_emplace_elem) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    int expected_result[14] = { 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    TVector<int> vec1(arr, 14), vec2(expected_result, 14);
    vec1.emplace(3, 5);
    vec1.erase_elem(3);

    EXPECT_EQ(vec1.size(), 13);

    for (int i = 0; i < 14; i++) {
        EXPECT_EQ(vec1.states()[i], expected_result[i]);
    }
}

TEST(TestTVectorLib, find_elems_after_pop_elem) {
    int arr[20] = { 1, 2, 3, 4, 1, 6, 7, 8, 9, 10, 11, 12, 1, 14, 15, 18, 1, 21, 11, 1 };
    TVector<int> vec1(arr, 20);
    vec1.erase_elems(4, 3);

    int expected_result[4] = { 0, 9, 13, 16 };
    int count = 0;
    int* actual_result = find_elems(vec1, 1, count);

    EXPECT_EQ(count, 4);

    for (int i = 0; i < count; i++) {
        EXPECT_EQ(actual_result[i], expected_result[i]);
    }
}

TEST(TestTVectorLib, emplace_after_erase_elem) {
    int arr[20] = { 1, 2, 3, 4, 1, 6, 7, 8, 9, 10, 11, 12, 1, 14, 15, 18, 1, 21, 11, 1 };
    TVector<int> vec1(arr, 20);
    vec1.erase_elems(4, 2);
    vec1.emplace(3, 111);
    int expected_result[18] = { 1, 2, 3, 111, 7, 8, 9, 10, 11, 12, 1, 14, 15, 18, 1, 21, 11, 1 };
    TVector<int> vec2(expected_result, 18);

    EXPECT_EQ(vec1, vec2);
    EXPECT_EQ(vec1.size(), 18);
}

TEST(TestTVectorLib, push_front_elem_after_pop_front_elem) {
    int arr[20] = { 1, 2, 3, 4, 1, 6, 7, 8, 9, 10, 11, 12, 1, 14, 15, 18, 1, 21, 11, 1 };
    TVector<int> vec1(arr, 20);
    vec1.pop_front_elem();
    vec1.push_front_elem(111);

    EXPECT_EQ(vec1.size(), 20);
    EXPECT_EQ(vec1[0], 111);
}

TEST(TestTVectorLib, find_elems_after_emplace) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec1(arr, 14);
    vec1.emplace(4, 111);
    int count = 0;
    int* actual_res = find_elems(vec1, 5, count);

    EXPECT_EQ(actual_res, nullptr);
    EXPECT_EQ(count, 0);
}

TEST(TestTVectorLib, accessing_an_elem_using_an_iterator) {
    int arr[32] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 111, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    TVector<int> vec1(arr, 32);
    auto it = vec1.begin();
    EXPECT_EQ(*it, 1);
}

TEST(TestTVectorLib, hoara_sort) {
    int arr[32] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 111, 222, 333, 444 };

    TVector<int> vec1(arr, 32);
    randomize(vec1);
    hoara_sort(vec1);

    for (size_t i = 1; i < 32; i++) {
        if (vec1.states()[i] == busy && vec1.states()[i - 1] == busy) {
            EXPECT_GE(vec1[i], vec1[i - 1]);
        }
    }
}

TEST(TestTVectorLib, hoara_sort_after_erase_elem) {
    int arr[32] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 111, 222, 333, 444 };

    TVector<int> vec1(arr, 32);
    vec1.erase_elem(5); 
    
    EXPECT_EQ(vec1.size(), 31);
    randomize(vec1);
    hoara_sort(vec1);

    for (size_t i = 1; i < 31; i++) {
        if (vec1.states()[i] == busy && vec1.states()[i - 1] == busy) {
            EXPECT_GE(vec1[i], vec1[i - 1]);
        }
    }
}

TEST(TestTVectorLib, push_back_after_erase_elems) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    int expected_result[13] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 111 };
    TVector<int> vec1(arr, 14), vec2(expected_result, 13);
    vec1.erase_elems(13, 2);
    vec1.push_back_elem(111);
    for (int i = 0; i < 13; i++) {
        EXPECT_EQ(vec1[i], vec2[i]);
    }
}
