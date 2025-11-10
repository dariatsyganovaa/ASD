#include <gtest/gtest.h>
#include "../lib_list/list.h"

TEST(TestListLib, init_constructor) {
    List<int> list;

    ASSERT_TRUE(list.is_empty());
    EXPECT_EQ(list.head(), nullptr);
    EXPECT_EQ(list.tail(), nullptr);
}

TEST(TestListLib, copy_constructor) {
    List<int> list1;
    list1.push_back(1); list1.push_back(2); list1.push_back(3);

    List<int> list2(list1);

    EXPECT_TRUE(list1.size() == list2.size());

    int i = 1;
    List<int>::Iterator it;

    for (it = list2.begin(); it != list2.end(); it++) {
        EXPECT_EQ(*it, i);
        i++;
    }
}

TEST(TestListLib, get_head) {
    List<int> list;
    list.push_back(1); list.push_back(2); list.push_back(3);

    EXPECT_EQ(list.head()->data, 1);
}

TEST(TestListLib, get_tail) {
    List<int> list;
    list.push_back(1); list.push_back(2); list.push_back(3);

    EXPECT_EQ(list.tail()->data, 3);
}

TEST(TestListLib, push_front_elem) {
    List<int> list;

    list.push_front(10);

    ASSERT_FALSE(list.is_empty());
    EXPECT_EQ(list.size(), 1);
    EXPECT_NE(list.head(), nullptr);
    EXPECT_EQ(list.head(), list.tail());
    EXPECT_EQ(list.head()->data, 10);
}

TEST(TestListLib, push_back_elem) {
    List<int> list;

    list.push_back(20);

    ASSERT_FALSE(list.is_empty());
    EXPECT_EQ(list.size(), 1);
    EXPECT_NE(list.head(), nullptr);
    EXPECT_EQ(list.head(), list.tail());
    EXPECT_EQ(list.head()->data, 20);
}

TEST(TestListLib, push_front_multiple_elems) {
    List<int> list;
    list.push_front(3);
    list.push_front(2);
    list.push_front(1);

    EXPECT_EQ(list.size(), 3);

    EXPECT_EQ(list.head()->data, 1);
    EXPECT_EQ(list.head()->next->data, 2);
    EXPECT_EQ(list.head()->next->next->data, 3);
    EXPECT_EQ(list.head()->next->next, list.tail());
    EXPECT_EQ(list.tail()->next, nullptr);
}

TEST(TestListLib, insert_at_begin) {
    List<int> list;
    list.push_back(20);
    list.push_back(30);
    list.insert(1, 10);

    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.head()->data, 10);
    EXPECT_EQ(list.head()->next->data, 20);
    EXPECT_EQ(list.tail()->data, 30);
}

TEST(TestListLib, insert_at_middle) {
    List<int> list;
    list.push_back(10);
    list.push_back(30);
    list.insert(2, 20); 

    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.head()->data, 10);
    EXPECT_EQ(list.head()->next->data, 20);
    EXPECT_EQ(list.tail()->data, 30);
}

TEST(TestListLib, insert_at_end) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.insert(3, 30);

    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.tail()->data, 30);
    EXPECT_EQ(list.head()->next->next, list.tail());
}

TEST(TestListLib, insert_out_of_bounds) {
    List<int> list;
    list.push_back(10);

    ASSERT_THROW(list.insert(5, 50), std::out_of_range);
}

TEST(TestListLib, pop_front_single_elem) {
    List<int> list;
    list.push_front(10);
    list.pop_front();
    ASSERT_TRUE(list.is_empty());
    EXPECT_EQ(list.size(), 0);
    EXPECT_EQ(list.head(), nullptr);
    EXPECT_EQ(list.tail(), nullptr);
}

TEST(TestListLib, pop_back_multiple_elems) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3); 
    list.pop_back();

    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.head()->data, 1);
    EXPECT_EQ(list.tail()->data, 2); 
    EXPECT_EQ(list.tail()->next, nullptr);
}

TEST(TestListLib, erase_from_begin) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.erase(1);

    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.head()->data, 2);
    EXPECT_EQ(list.head()->next->data, 3);
    EXPECT_EQ(list.tail()->data, 3);
}

TEST(TestListLib, erase_from_middle) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.erase(2); 

    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.head()->data, 1);
    EXPECT_EQ(list.head()->next->data, 3); 
    EXPECT_EQ(list.tail()->data, 4);
}

TEST(TestListLib, erase_from_end) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3); 
    list.erase(3); 

    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.head()->data, 1);
    EXPECT_EQ(list.tail()->data, 2);
    EXPECT_EQ(list.tail()->next, nullptr);
    EXPECT_EQ(list.head()->next, list.tail());
}

TEST(TestListLib, erase_out_of_bounds) {
    List<int> list;
    list.push_back(10);
    EXPECT_THROW(list.erase(2), std::out_of_range);
}

TEST(TestListLib, pop_from_empty) {
    List<int> list;
    EXPECT_THROW(list.pop_front(), std::out_of_range);
    EXPECT_THROW(list.pop_back(), std::out_of_range);
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