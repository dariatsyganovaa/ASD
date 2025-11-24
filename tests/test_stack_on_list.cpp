#include <gtest/gtest.h>
#include "../lib_stack_on_list/stack_on_list.h"

TEST(TestStackOnListLib, copy_constructor) {
    StackOnList<int> stack1;
    stack1.push(1); stack1.push(2); stack1.push(3);

    StackOnList<int> stack2(stack1);

    EXPECT_EQ(stack1.top(), stack2.top());
}

TEST(TestStackOnListLib, push_elem) {
    StackOnList<int> stack;
    stack.push(1); stack.push(2); stack.push(3);

    EXPECT_EQ(stack.top(), 3);
    EXPECT_FALSE(stack.is_empty());
}

TEST(TestStackOnListLib, pop_elem) {
    StackOnList<int> stack;
    stack.push(1); stack.push(2); stack.push(3);
    stack.push(4); stack.push(5); stack.push(6);

    stack.pop(); stack.pop(); stack.pop();

    EXPECT_EQ(stack.top(), 3);
    EXPECT_FALSE(stack.is_empty());
}

TEST(TestStackOnListLib, try_pop_elem_from_an_empty_stack) {
    StackOnList<int> stack;

    ASSERT_ANY_THROW(stack.pop());
}

TEST(TestStackOnListLib, top_elem) {
    StackOnList<int> stack;
    stack.push(1); stack.push(2); stack.push(3);
    stack.push(4); stack.push(5); stack.push(6);

    EXPECT_EQ(stack.top(), 6);
    stack.pop();
    EXPECT_EQ(stack.top(), 5);
    stack.pop();
    EXPECT_EQ(stack.top(), 4);
}

TEST(TestStackOnListLib, try_top_elem_from_an_empty_stack) {
    StackOnList<int> stack;

    ASSERT_ANY_THROW(stack.top());
}

TEST(TestStackOnListLib, the_stack_is_empty) {
    StackOnList<int> stack;

    EXPECT_TRUE(stack.is_empty());
}

TEST(TestStackOnListLib, the_stack_is_empty_after_pop) {
    StackOnList<int> stack;
    stack.push(1); stack.push(2); stack.push(3);
    stack.pop(); stack.pop(); stack.pop();

    EXPECT_TRUE(stack.is_empty());
}

TEST(TestStackOnListLib, the_stack_is_not_empty) {
    StackOnList<int> stack;
    stack.push(1); stack.push(2); stack.push(3);
    stack.push(4); stack.push(5); stack.push(6);
    stack.push(7); stack.push(8); stack.push(9);
    stack.push(10); stack.push(11); stack.push(12);
    stack.push(13); stack.push(14); stack.push(15);

    EXPECT_FALSE(stack.is_empty());
}

TEST(TestStackOnListLib, clear_the_stack) {
    StackOnList<int> stack;
    stack.push(1); stack.push(2); stack.push(3);
    stack.push(4); stack.push(5); stack.push(6);
    stack.push(7); stack.push(8); stack.push(9);
    stack.push(10); stack.push(11); stack.push(12);
    stack.push(13); stack.push(14);

    stack.clear();

    EXPECT_TRUE(stack.is_empty());
    ASSERT_NO_THROW(stack.push(1));
}