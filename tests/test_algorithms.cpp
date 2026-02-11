#include <gtest/gtest.h>
#include "../lib_algorithms/algorithms.h"

TEST(TestAlgorithmsLib, try_check_breckets_1) {
    std::string str = "()()";

    EXPECT_TRUE(check_breckets(str));
}

TEST(TestAlgorithmsLib, try_check_breckets_2) {
    std::string str = "[(()())({})]";

    EXPECT_TRUE(check_breckets(str));
}

TEST(TestAlgorithmsLib, try_check_breckets_3) {
    std::string str = "(()()";

    EXPECT_FALSE(check_breckets(str));
}

TEST(TestAlgorithmsLib, try_check_breckets_4) {
    std::string str = "())(())";

    EXPECT_FALSE(check_breckets(str));
}

TEST(TestAlgorithmsLib, try_check_breckets_5) {
    std::string str = "((()()(()))";

    EXPECT_FALSE(check_breckets(str));
}

TEST(TestAlgorithmsLib, try_read_expression_1) {
    EXPECT_NO_THROW(read_expression("3 * (15 + (x + y) * (2*x - 7*y^2))"));
    EXPECT_ANY_THROW(read_expression("3 * (15 + (x y) * (2x - 7*y^2))"));
    EXPECT_ANY_THROW(read_expression("3 * (15 + (x + y) * (2*x - 7*y^))"));
    EXPECT_ANY_THROW(read_expression("3 * (15 + (x + y) * (2*x - 7*y^2)"));
    EXPECT_ANY_THROW(read_expression("3 * (15 + (x + y) * (2*x - 7*y^2)))"));
}

TEST(TestAlgorithmsLib, rabbit_turtle_has_cycle) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);

    Node<int>* head = list.head();
    Node<int>* tail = head;
    while (tail->next != nullptr) {
        tail = tail->next;
    }

    Node<int>* cycle = head->next->next;
    tail->next = cycle;

    EXPECT_TRUE(is_looped_rabbit_turtle(&list));

    tail->next = nullptr;
}

TEST(TestAlgorithmsLib, reversal_check_has_cycle) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    Node<int>* head = list.head();
    Node<int>* tail = head;
    while (tail->next != nullptr) {
        tail = tail->next;
    }

    tail->next = head;

    EXPECT_TRUE(is_looped(&list));

    tail->next = nullptr;
}

TEST(TestAlgorithmsLib, find_loop_detects_entry_point) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);

    Node<int>* head = list.head();
    Node<int>* tail = head;
    while (tail->next != nullptr) {
        tail = tail->next;
    }
    Node<int>* expected_entry = head->next->next;

    tail->next = expected_entry;

    Node<int>* result = find_loop(&list);
    EXPECT_EQ(result, expected_entry);
    EXPECT_EQ(result->data, 3);

    tail->next = nullptr;
}

TEST(TestAlgorithmsLib, find_loop_returns_null_if_no_cycle) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    Node<int>* result = find_loop(&list);
    EXPECT_EQ(result, nullptr);
}