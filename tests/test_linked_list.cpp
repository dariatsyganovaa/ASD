#include <gtest/gtest.h>
#include "../lib_linked_list/linked_list.h"

TEST(TestLinkedListLib, init_constructor) {
    LinkedList<int> list;

    EXPECT_TRUE(list.is_empty());
    EXPECT_EQ(list.head(), nullptr);
    EXPECT_EQ(list.tail(), nullptr);
}

TEST(TestLinkedListLib, copy_constructor) {
    LinkedList<int> list1;
    list1.push_back(1); list1.push_back(2); list1.push_back(3);

    LinkedList<int> list2(list1);

    EXPECT_TRUE(list1.size() == list2.size());

    int i = 1;
    LinkedList<int>::Iterator it;

    for (it = list2.begin(); it != list2.end(); it++) {
        EXPECT_EQ(*it, i);
        i++;
    }
}

TEST(TestLinkedListLib, list_is_empty) {
    LinkedList<int> list;

    list.push_back(1); list.push_back(2); list.push_back(3);
    EXPECT_FALSE(list.is_empty());

    list.pop_back(); list.pop_back(); list.pop_back();
    EXPECT_TRUE(list.is_empty());
}

TEST(TestLinkedListLib, push_front_elem) {
    LinkedList<int> list;

    list.push_front(10);

    EXPECT_FALSE(list.is_empty());
    EXPECT_EQ(list.size(), 1);
    EXPECT_NE(list.head(), nullptr);

    EXPECT_EQ(list.head()->next, nullptr);
    EXPECT_EQ(list.head()->prev, nullptr);

    EXPECT_EQ(list.head(), list.tail());
    EXPECT_EQ(list.head()->data, 10);
}

TEST(TestLinkedListLib, push_back_elem) {
    LinkedList<int> list;

    list.push_back(20);

    EXPECT_FALSE(list.is_empty());
    EXPECT_EQ(list.size(), 1);
    EXPECT_NE(list.head(), nullptr);

    EXPECT_EQ(list.head()->next, nullptr);
    EXPECT_EQ(list.head()->prev, nullptr);

    EXPECT_EQ(list.head(), list.tail());
    EXPECT_EQ(list.head()->data, 20);
}

TEST(TestLinkedListLib, push_front_multiple_elems) {
    LinkedList<int> list;
    list.push_front(3);
    list.push_front(2);
    list.push_front(1);

    EXPECT_EQ(list.size(), 3);

    EXPECT_EQ(list.head()->data, 1);
    EXPECT_EQ(list.head()->next->data, 2);
    EXPECT_EQ(list.head()->next->next->data, 3);
    EXPECT_EQ(list.head()->next->next, list.tail());

    EXPECT_EQ(list.head()->prev, nullptr);
    EXPECT_EQ(list.tail()->next, nullptr);
}

TEST(TestLinkedListLib, insert_at_middle_with_node) {
    LinkedList<int> list;

    list.push_front(3);
    list.push_front(1);

    Node<int>* node = list.head();
    list.insert(node, 2);

    int i = 1;
    LinkedList<int>::Iterator it;

    for (it = list.begin(); it != list.end(); it++) {
        EXPECT_EQ(*it, i);
        i++;
    }

    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.head()->data, 1);
    EXPECT_EQ(node->next->data, 2);
    EXPECT_EQ(node->prev, nullptr);
    EXPECT_EQ(list.tail()->data, 3);
}

TEST(TestLinkedListLib, insert_at_begin_with_pos) {
    LinkedList<int> list;
    list.push_back(20);
    list.push_back(30);
    list.insert(1, 10);

    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.head()->data, 10);
    EXPECT_EQ(list.head()->next->data, 20);
    EXPECT_EQ(list.tail()->data, 30);
    EXPECT_EQ(list.head()->prev, nullptr);
}

TEST(TestLinkedListLib, insert_at_middle_with_pos) {
    LinkedList<int> list;
    list.push_back(10);
    list.push_back(30);
    list.insert(2, 20);

    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.head()->data, 10);
    EXPECT_EQ(list.head()->next->data, 20);
    EXPECT_EQ(list.tail()->data, 30);
    EXPECT_EQ(list.head()->prev, nullptr);
}

TEST(TestLinkedListLib, insert_at_end_with_pos) {
    LinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.insert(3, 30);

    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.tail()->data, 30);
    EXPECT_EQ(list.head()->next->next, list.tail());
}

TEST(TestLinkedListLib, try_insert_with_nullptr) {
    LinkedList<int> list;
    Node<int>* node = list.head();

    EXPECT_THROW(list.insert(node, 2), std::invalid_argument);
}

TEST(TestLinkedListLib, insert_out_of_bounds) {
    LinkedList<int> list;
    list.push_back(10);

    EXPECT_THROW(list.insert(5, 50), std::out_of_range);
}

TEST(TestLinkedListLib, pop_front_elem) {
    LinkedList<int> list;

    list.push_front(10);
    list.pop_front();

    EXPECT_TRUE(list.is_empty());
    EXPECT_EQ(list.size(), 0);
    EXPECT_EQ(list.head(), nullptr);
    EXPECT_EQ(list.head(), list.tail());
}

TEST(TestLinkedListLib, pop_back_elem) {
    LinkedList<int> list;

    list.push_back(10);
    list.push_back(20);
    list.pop_back();

    EXPECT_FALSE(list.is_empty());
    EXPECT_EQ(list.size(), 1);
    EXPECT_NE(list.tail(), nullptr);

    EXPECT_EQ(list.head()->next, nullptr);
    EXPECT_EQ(list.head()->prev, nullptr);

    EXPECT_EQ(list.head()->data, 10);
    EXPECT_EQ(list.head(), list.tail());
}

TEST(TestLinkedListLib, pop_back_multiple_elems) {
    LinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.pop_back();

    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.head()->data, 1);
    EXPECT_EQ(list.tail()->prev->data, 2);
    EXPECT_EQ(list.tail()->data, 3);
    EXPECT_EQ(list.tail()->next, nullptr);
}

TEST(TestLinkedListLib, erase_from_middle_with_node) {
    LinkedList<int> list;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    Node<int>* node = list.head()->next;
    list.erase(node);

    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.head()->data, 1);
    EXPECT_EQ(list.head()->next->data, 3);
    EXPECT_EQ(list.tail()->prev, list.head());
    EXPECT_EQ(list.tail()->data, 3);
}

TEST(TestLinkedListLib, erase_from_begin_with_pos) {
    LinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.erase(1);

    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.head()->data, 2);
    EXPECT_EQ(list.head()->next->data, 3);
    EXPECT_EQ(list.tail()->prev, list.head());
    EXPECT_EQ(list.tail()->data, 3);
}

TEST(TestLinkedListLib, erase_from_middle_with_pos) {
    LinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.erase(2);

    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.head()->data, 1);
    EXPECT_EQ(list.head()->next->data, 3);
    EXPECT_EQ(list.tail()->prev, list.head());
    EXPECT_EQ(list.tail()->data, 3);
}

TEST(TestLinkedListLib, erase_from_end_with_pos) {
    LinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.erase(3);

    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.head()->data, 1);
    EXPECT_EQ(list.tail()->data, 2);
    EXPECT_EQ(list.tail()->prev, list.head());
    EXPECT_EQ(list.tail()->next, nullptr);
}

TEST(TestLinkedListLib, erase_out_of_bounds) {
    LinkedList<int> list;
    list.push_back(10);
    ASSERT_THROW(list.erase(2), std::out_of_range);
}

TEST(TestLinkedListLib, pop_from_empty) {
    LinkedList<int> list;
    ASSERT_THROW(list.pop_front(), std::out_of_range);
    ASSERT_THROW(list.pop_back(), std::out_of_range);
}

TEST(TestLinkedListLib, read_iterator) {
    LinkedList<int> list;

    for (int i = 0; i < 10; i++)
        list.push_back(i * 3 + 1);

    int i = 0;
    LinkedList<int>::Iterator it;

    for (it = list.begin(); it != list.end(); it++) {
        //std::cout << *it << " ";
        EXPECT_EQ(*it, i * 3 + 1);
        *it = i++;
    }
}

TEST(TestLinkedListLib, write_iterator) {
    LinkedList<int> list;

    for (int i = 0; i < 3; i++)
        list.push_back(i * 3 + 1);

    LinkedList<int>::Iterator it;

    for (it = list.begin(); it != list.end(); it++) {
        *it = 111;
        EXPECT_EQ(*it, 111);
    }
}

TEST(TestLinkedListLib, iterator_in_empty_list) {
    LinkedList<int> list;
    LinkedList<int>::Iterator it;

    for (it = list.begin(); it != list.end(); it++) {
        EXPECT_NO_THROW(*it);
    }

    EXPECT_TRUE(list.begin() == list.end());
}