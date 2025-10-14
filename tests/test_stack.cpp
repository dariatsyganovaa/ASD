#include <gtest/gtest.h>
#include "../lib_stack/stack.h"

TEST(TestStackLib, size_constructor) {
    Stack<int> stack(5);

    EXPECT_FALSE(stack.is_full());
}

TEST(TestStackLib, copy_constructor) {
    Stack<int> stack1(3);
    stack1.push(1); stack1.push(2); stack1.push(3);

    Stack<int> stack2(stack1);

    EXPECT_EQ(stack1.top(), stack2.top());
}

TEST(TestStackLib, push_elem) {
    Stack<int> stack(15);
    stack.push(1); stack.push(2); stack.push(3);
    
    EXPECT_EQ(stack.top(), 3);
    EXPECT_FALSE(stack.is_empty());
    EXPECT_FALSE(stack.is_full());
}

TEST(TestStackLib, try_push_elem_onto_an_overflowing_stack) {
    Stack<int> stack(15);
    stack.push(1); stack.push(2); stack.push(3);
    stack.push(4); stack.push(5); stack.push(6);
    stack.push(7); stack.push(8); stack.push(9);
    stack.push(10); stack.push(11); stack.push(12);
    stack.push(13); stack.push(14); stack.push(15);

    ASSERT_ANY_THROW(stack.push(16));
}

TEST(TestStackLib, pop_elem) {
    Stack<int> stack(15);
    stack.push(1); stack.push(2); stack.push(3);
    stack.push(4); stack.push(5); stack.push(6);

    stack.pop(); stack.pop(); stack.pop();

    EXPECT_EQ(stack.top(), 3);
    EXPECT_FALSE(stack.is_empty());
    EXPECT_FALSE(stack.is_full());
}

TEST(TestStackLib, try_pop_elem_from_an_empty_stack) {
    Stack<int> stack(3);

    ASSERT_ANY_THROW(stack.pop());
}

TEST(TestStackLib, top_elem) {
    Stack<int> stack(6);
    stack.push(1); stack.push(2); stack.push(3);
    stack.push(4); stack.push(5); stack.push(6);

    EXPECT_EQ(stack.top(), 6);
    stack.pop();
    EXPECT_EQ(stack.top(), 5);
    stack.pop();
    EXPECT_EQ(stack.top(), 4);
}

TEST(TestStackLib, try_top_elem_from_an_empty_stack) {
    Stack<int> stack(3);

    ASSERT_ANY_THROW(stack.top());
}

TEST(TestStackLib, the_stack_is_empty) {
    Stack<int> stack(15);

    EXPECT_TRUE(stack.is_empty());
}

TEST(TestStackLib, the_stack_is_empty_after_pop) {
    Stack<int> stack(15);
    stack.push(1); stack.push(2); stack.push(3);
    stack.pop(); stack.pop(); stack.pop();

    EXPECT_TRUE(stack.is_empty());
}

TEST(TestStackLib, the_stack_is_not_empty) {
    Stack<int> stack(15);
    stack.push(1); stack.push(2); stack.push(3);
    stack.push(4); stack.push(5); stack.push(6);
    stack.push(7); stack.push(8); stack.push(9);
    stack.push(10); stack.push(11); stack.push(12);
    stack.push(13); stack.push(14); stack.push(15);

    EXPECT_FALSE(stack.is_empty());
}

TEST(TestStackLib, the_stack_is_full) {
    Stack<int> stack(15);
    stack.push(1); stack.push(2); stack.push(3);
    stack.push(4); stack.push(5); stack.push(6);
    stack.push(7); stack.push(8); stack.push(9);
    stack.push(10); stack.push(11); stack.push(12);
    stack.push(13); stack.push(14); stack.push(15);

    EXPECT_TRUE(stack.is_full());
}

TEST(TestStackLib, the_stack_is_not_full) {
    Stack<int> stack(15);
    stack.push(1); stack.push(2); stack.push(3);
    stack.push(4); stack.push(5); stack.push(6);
    stack.push(7); stack.push(8); stack.push(9);
    stack.push(10); stack.push(11); stack.push(12);
    stack.push(13); stack.push(14); 

    EXPECT_FALSE(stack.is_full());
}

TEST(TestStackLib, clear_the_stack) {
    Stack<int> stack(14);
    stack.push(1); stack.push(2); stack.push(3);
    stack.push(4); stack.push(5); stack.push(6);
    stack.push(7); stack.push(8); stack.push(9);
    stack.push(10); stack.push(11); stack.push(12);
    stack.push(13); stack.push(14);

    stack.clear();

    EXPECT_TRUE(stack.is_empty());
    ASSERT_NO_THROW(stack.push(1));
}