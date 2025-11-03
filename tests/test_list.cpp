#include <gtest/gtest.h>
#include "../lib_list/list.h"

TEST(TestListLib, is_empty_initially) {
    List<int> list;

    ASSERT_TRUE(list.is_empty());
    ASSERT_EQ(list.size(), 0);
    ASSERT_EQ(list.head(), nullptr);
    ASSERT_EQ(list.tail(), nullptr);
}

TEST(TestListLib, push_front_elem) {
    List<int> list;

    list.push_front(10);

    ASSERT_FALSE(list.is_empty());
    ASSERT_EQ(list.size(), 1);
    ASSERT_NE(list.head(), nullptr);
    ASSERT_EQ(list.head(), list.tail());
    ASSERT_EQ(list.head()->data, 10);
}

TEST(TestListLib, push_back_elem) {
    List<int> list;

    list.push_back(20);

    ASSERT_FALSE(list.is_empty());
    ASSERT_EQ(list.size(), 1);
    ASSERT_NE(list.head(), nullptr);
    ASSERT_EQ(list.head(), list.tail());
    ASSERT_EQ(list.head()->data, 20);
}

TEST(TestListLib, push_front_multiple_elems) {
    List<int> list;
    list.push_front(3);
    list.push_front(2);
    list.push_front(1);

    ASSERT_EQ(list.size(), 3);

    ASSERT_EQ(list.head()->data, 1);
    ASSERT_EQ(list.head()->next->data, 2);
    ASSERT_EQ(list.head()->next->next->data, 3);
    ASSERT_EQ(list.head()->next->next, list.tail());
    ASSERT_EQ(list.tail()->next, nullptr);
}

TEST(TestListLib, insert_at_middle) {
    List<int> list;
    list.push_back(10);
    list.push_back(30);
    list.insert(1, 20); 

    ASSERT_EQ(list.size(), 3);
    ASSERT_EQ(list.head()->data, 10);
    ASSERT_EQ(list.head()->next->data, 20);
    ASSERT_EQ(list.tail()->data, 30);
}

TEST(TestListLib, insert_at_end) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.insert(2, 30);

    ASSERT_EQ(list.size(), 3);
    ASSERT_EQ(list.tail()->data, 30);
    ASSERT_EQ(list.head()->next->next, list.tail());
}

TEST(TestListLib, insert_out_of_bounds) {
    List<int> list;
    list.push_back(10);

    ASSERT_THROW(list.insert(5, 50), std::out_of_range);
    ASSERT_THROW(list.insert(2, 50), std::out_of_range);
}

TEST(TestListLib, pop_front_single_elem) {
    List<int> list;
    list.push_front(10);
    list.pop_front();
    ASSERT_TRUE(list.is_empty());
    ASSERT_EQ(list.size(), 0);
    ASSERT_EQ(list.head(), nullptr);
    ASSERT_EQ(list.tail(), nullptr);
}

TEST(TestListLib, pop_back_multiple_elems) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3); 
    list.pop_back();

    ASSERT_EQ(list.size(), 2);
    ASSERT_EQ(list.head()->data, 1);
    ASSERT_EQ(list.tail()->data, 2); 
    ASSERT_EQ(list.tail()->next, nullptr);
}

TEST(TestListLib, erase_from_middle) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.erase(1); 

    ASSERT_EQ(list.size(), 2);
    ASSERT_EQ(list.head()->data, 1);
    ASSERT_EQ(list.head()->next->data, 3); 
    ASSERT_EQ(list.tail()->data, 3);
}

TEST(TestListLib, erase_from_end) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3); 
    list.erase(2); 

    ASSERT_EQ(list.size(), 2);
    ASSERT_EQ(list.head()->data, 1);
    ASSERT_EQ(list.tail()->data, 2);
    ASSERT_EQ(list.tail()->next, nullptr);
}

TEST(TestListLib, erase_out_of_bounds) {
    List<int> list;
    list.push_back(10);
    ASSERT_THROW(list.erase(1), std::out_of_range);
}

TEST(TestListLib, pop_from_empty) {
    List<int> list;
    ASSERT_THROW(list.pop_front(), std::out_of_range);
    ASSERT_THROW(list.pop_back(), std::out_of_range);
}

TEST(TestListLib, deep_copy_constructor) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);

    List<int> listCopy = list;

    ASSERT_EQ(listCopy.size(), 2);
    ASSERT_EQ(listCopy.head()->data, 10);
    ASSERT_EQ(listCopy.tail()->data, 20);

    listCopy.pop_back();
    list.push_front(5);

    ASSERT_EQ(listCopy.size(), 1);
    ASSERT_EQ(listCopy.head()->data, 10);

    ASSERT_EQ(list.size(), 3);
    ASSERT_EQ(list.head()->data, 5);
    ASSERT_EQ(list.head()->next->data, 10);

    ASSERT_NE(list.head(), listCopy.head());
}

TEST(TestListLib, read_iterator) {
    List<int> list;
    
    for (int i = 0; i < 10; i++)
        list.push_back(i * 3 + 1);

    int i = 0;
    List<int>::Iterator it;

    for (it = list.begin(); it != list.end(); it++){
        //std::cout << *it << " ";
        EXPECT_EQ(*it, i * 3 + 1);
        *it = i++;
    }
}

TEST(TestListLib, write_iterator) {
    List<int> list;
    
    for (int i = 0; i < 3; i++)
        list.push_back(i * 3 + 1);

    List<int>::Iterator it;

    for (it = list.begin(); it != list.end(); it++) {
        *it = 111;
        EXPECT_EQ(*it, 111);
    }
}

TEST(TestListLib, iterator_in_empty_list) {
    List<int> list;
    List<int>::Iterator it;

    for (it = list.begin(); it != list.end(); it++) {
        EXPECT_NO_THROW(*it);
    }

    EXPECT_TRUE(list.begin() == list.end());
}