#include <gtest/gtest.h>
#include "../lib_heap/heap.h"
#include <string>

TEST(TestMinHeap, empty_heap_creation) {
    Heap<int> heap;
    EXPECT_TRUE(heap.is_empty());
    EXPECT_EQ(heap.size(), 0);
}

TEST(TestMinHeap, insert_elem) {
    Heap<int> heap;
    heap.insert(42);

    EXPECT_FALSE(heap.is_empty());
    EXPECT_EQ(heap.size(), 1);
    EXPECT_EQ(heap.get_min(), 42);
}

TEST(TestMinHeap, insert_mult_elems) {
    Heap<int> heap;
    heap.insert(50);
    heap.insert(30);
    heap.insert(20);
    heap.insert(15);
    heap.insert(10);

    EXPECT_EQ(heap.size(), 5);
    EXPECT_EQ(heap.get_min(), 10); 
}

TEST(TestMinHeap, extract_min_from_elem) {
    Heap<int> heap;
    heap.insert(42);

    EXPECT_EQ(heap.extract_min(), 42);
    EXPECT_TRUE(heap.is_empty());
}

TEST(TestMinHeap, extract_min_in_order) {
    Heap<int> heap;
    heap.insert(50);
    heap.insert(30);
    heap.insert(20);
    heap.insert(15);
    heap.insert(10);

    EXPECT_EQ(heap.extract_min(), 10);
    EXPECT_EQ(heap.extract_min(), 15);
    EXPECT_EQ(heap.extract_min(), 20);
    EXPECT_EQ(heap.extract_min(), 30);
    EXPECT_EQ(heap.extract_min(), 50);
    EXPECT_TRUE(heap.is_empty());
}

TEST(TestMinHeap, extract_min_from_empty_heap) {
    Heap<int> heap;
    EXPECT_THROW(heap.extract_min(), std::runtime_error);
}

TEST(TestMinHeap, get_min_from_empty_heap) {
    Heap<int> heap;
    EXPECT_THROW(heap.get_min(), std::runtime_error);
}

TEST(TestMinHeap, build_heap_from_arr) {
    int mass[] = { 4, 10, 3, 5, 1 };
    TVector<int> arr(mass, 5);
    Heap<int> heap(arr);

    EXPECT_EQ(heap.size(), 5);
    EXPECT_EQ(heap.get_min(), 1);
}

TEST(TestMinHeap, build_heap_and_extract_all) {
    int mass[] = { 9, 5, 6, 2, 3 }; 
    TVector<int> arr(mass, 5); 
    Heap<int> heap(arr);

    TVector<int> result;
    while (!heap.is_empty()) {
        result.push_back_elem(heap.extract_min());
    }

    int mass2[] = { 2, 3, 5, 6, 9 };
    TVector<int> expected(mass2, 5);
    EXPECT_EQ(result, expected);
}

TEST(TestMinHeap, build_heap_from_empty_arr) {
    TVector<int> arr;
    Heap<int> heap(arr);

    EXPECT_TRUE(heap.is_empty());
    EXPECT_EQ(heap.size(), 0);
}

TEST(TestMinHeap, heap_property_after_insert) {
    Heap<int> heap;
    heap.insert(50);
    heap.insert(30);
    heap.insert(70);
    heap.insert(10);
    heap.insert(40);

    EXPECT_EQ(heap.get_min(), 10);

    heap.extract_min();
    EXPECT_EQ(heap.get_min(), 30);

    heap.extract_min();
    EXPECT_EQ(heap.get_min(), 40);
}

TEST(TestMinHeap, heap_property_with_duplicates) {
    Heap<int> heap;
    heap.insert(5);
    heap.insert(5);
    heap.insert(5);
    heap.insert(3);
    heap.insert(7);

    EXPECT_EQ(heap.extract_min(), 3);
    EXPECT_EQ(heap.extract_min(), 5);
    EXPECT_EQ(heap.extract_min(), 5);
    EXPECT_EQ(heap.extract_min(), 5);
    EXPECT_EQ(heap.extract_min(), 7);
}

TEST(TestMinHeap, insert_after_extract_all) {
    Heap<int> heap;
    heap.insert(10);
    heap.insert(20);

    heap.extract_min();
    heap.extract_min();

    EXPECT_TRUE(heap.is_empty());

    heap.insert(30);
    EXPECT_EQ(heap.size(), 1);
    EXPECT_EQ(heap.get_min(), 30);
}

TEST(TestMinHeap, large_number_of_elems) {
    Heap<int> heap;

    for (int i = 1000; i >= 1; i--) {
        heap.insert(i);
    }

    EXPECT_EQ(heap.size(), 1000);
    EXPECT_EQ(heap.get_min(), 1);

    for (int i = 1; i <= 1000; i++) {
        EXPECT_EQ(heap.extract_min(), i);
    }
}

TEST(TestMinHeap, negative_numbers) {
    Heap<int> heap;
    heap.insert(-10);
    heap.insert(5);
    heap.insert(-20);
    heap.insert(0);
    heap.insert(-5);

    EXPECT_EQ(heap.extract_min(), -20);
    EXPECT_EQ(heap.extract_min(), -10);
    EXPECT_EQ(heap.extract_min(), -5);
    EXPECT_EQ(heap.extract_min(), 0);
    EXPECT_EQ(heap.extract_min(), 5);
}

TEST(TestMinHeap, double_type) {
    Heap<double> heap;
    heap.insert(3.14);
    heap.insert(2.71);
    heap.insert(1.41);
    heap.insert(9.99);

    EXPECT_DOUBLE_EQ(heap.get_min(), 1.41);
    EXPECT_DOUBLE_EQ(heap.extract_min(), 1.41);
    EXPECT_DOUBLE_EQ(heap.extract_min(), 2.71);
}

TEST(TestMinHeap, string_type) {
    Heap<std::string> heap;
    heap.insert("zebra");
    heap.insert("apple");
    heap.insert("banana");
    heap.insert("cherry");

    EXPECT_EQ(heap.get_min(), "apple");
    EXPECT_EQ(heap.extract_min(), "apple");
    EXPECT_EQ(heap.extract_min(), "banana");
    EXPECT_EQ(heap.extract_min(), "cherry");
    EXPECT_EQ(heap.extract_min(), "zebra");
}

TEST(TestMinHeap, all_elems_same) {
    Heap<int> heap;
    for (int i = 0; i < 5; i++) {
        heap.insert(42);
    }

    EXPECT_EQ(heap.size(), 5);
    while (!heap.is_empty()) {
        EXPECT_EQ(heap.extract_min(), 42);
    }
}

TEST(TestMinHeap, already_sorted_arr) {
    int mass[] = { 1, 2, 3, 4, 5 };
    TVector<int> arr(mass, 5);
    Heap<int> heap(arr);

    for (int i = 1; i <= 5; i++) {
        EXPECT_EQ(heap.extract_min(), i);
    }
}

TEST(TestMinHeap, reverse_sorted_arr) {
    int mass[] = { 5, 4, 3, 2, 1 };
    TVector<int> arr(mass, 5);
    Heap<int> heap(arr);

    for (int i = 1; i <= 5; i++) {
        EXPECT_EQ(heap.extract_min(), i);
    }
}

TEST(TestMinHeap, verify_heap_structure) {
    int mass[] = { 4, 10, 3, 5, 1 };
    TVector<int> arr(mass, 5);
    Heap<int> heap(arr);

    const auto& internal_heap = heap.get_heap();

    for (size_t i = 0; i < internal_heap.size() / 2; i++) {
        size_t left = 2 * i + 1;
        size_t right = 2 * i + 2;

        if (left < internal_heap.size()) {
            EXPECT_LE(internal_heap[i], internal_heap[left]);
        }
        if (right < internal_heap.size()) {
            EXPECT_LE(internal_heap[i], internal_heap[right]);
        }
    }
}
