#include <gtest/gtest.h>
#include "../lib_queue/queue.h"

TEST(TestQueueLib, size_constructor) {
    Queue<int> queue(5);

    EXPECT_FALSE(queue.is_full());
    EXPECT_TRUE(queue.is_empty());
}

TEST(TestQueueLib, copy_constructor) {
    Queue<int> queue1(3);
    queue1.push(1); queue1.push(2); queue1.push(3);

    Queue<int> queue2(queue1);

    EXPECT_EQ(queue1.head(), queue2.head());
    EXPECT_EQ(queue1.tail(), queue2.tail());

    queue1.pop();
    queue2.pop();

    EXPECT_EQ(queue1.head(), 2);
    EXPECT_EQ(queue2.head(), 2);
}

TEST(TestQueueLib, push_elem) {
    Queue<int> queue(15);
    queue.push(1); queue.push(2); queue.push(3);

    EXPECT_EQ(queue.head(), 1);
    EXPECT_EQ(queue.tail(), 3);
    EXPECT_FALSE(queue.is_empty());
    EXPECT_FALSE(queue.is_full());
}

TEST(TestQueueLib, try_push_elem_onto_an_overflowing_queue) {
    Queue<int> queue(3);
    queue.push(1); queue.push(2); queue.push(3);

    ASSERT_ANY_THROW(queue.push(4));
}

TEST(TestQueueLib, pop_elem) {
    Queue<int> queue(6);
    queue.push(1); queue.push(2); queue.push(3);
    queue.push(4); queue.push(5); queue.push(6);

    queue.pop(); queue.pop(); queue.pop();

    EXPECT_EQ(queue.head(), 4);
    EXPECT_EQ(queue.tail(), 6);
    EXPECT_FALSE(queue.is_empty());
    EXPECT_FALSE(queue.is_full());
}

TEST(TestQueueLib, tail_elem) {
    Queue<int> queue(6);
    queue.push(1); queue.push(2); queue.push(3);
    queue.push(4); queue.push(5); queue.push(6);

    queue.pop();
    EXPECT_EQ(queue.tail(), 6);
}

TEST(TestQueueLib, try_tail_elem_from_an_empty_queue) {
    Queue<int> queue(3);

    ASSERT_ANY_THROW(queue.tail());
    EXPECT_FALSE(queue.is_full());
    EXPECT_TRUE(queue.is_empty());
}

TEST(TestQueueLib, head_elem) {
    Queue<int> queue(6);
    queue.push(1); queue.push(2); queue.push(3);
    queue.push(4); queue.push(5); queue.push(6);

    EXPECT_EQ(queue.head(), 1);
    queue.pop();
    EXPECT_EQ(queue.head(), 2);
    queue.pop();
    EXPECT_EQ(queue.head(), 3);
}

TEST(TestQueueLib, try_actions_from_an_empty_queue) {
    Queue<int> queue(3);

    ASSERT_ANY_THROW(queue.pop());
    ASSERT_ANY_THROW(queue.head());
    EXPECT_FALSE(queue.is_full());
    EXPECT_TRUE(queue.is_empty());
}

TEST(TestQueueLib, the_queue_is_not_empty) {
    Queue<int> queue(15);
    queue.push(1);

    EXPECT_FALSE(queue.is_empty());
}

TEST(TestQueueLib, the_queue_is_empty_after_pop) {
    Queue<int> queue(15);
    queue.push(1); queue.push(2); queue.push(3);
    queue.pop(); queue.pop(); queue.pop();

    EXPECT_TRUE(queue.is_empty());
}

TEST(TestQueueLib, the_queue_is_full) {
    Queue<int> queue(3);
    queue.push(1); queue.push(2); queue.push(3);

    EXPECT_TRUE(queue.is_full());
}

TEST(TestQueueLib, the_queue_is_not_full) {
    Queue<int> queue(3);
    queue.push(1);

    EXPECT_FALSE(queue.is_full());
}

TEST(TestQueueLib, clear_the_queue) {
    Queue<int> queue(14);
    queue.push(1); queue.push(2); queue.push(3);
    queue.push(4); queue.push(5); queue.push(6);
    queue.push(7); queue.push(8); queue.push(9);
    queue.push(10); queue.push(11); queue.push(12);
    queue.push(13); queue.push(14);

    queue.clear();

    EXPECT_TRUE(queue.is_empty());
    ASSERT_NO_THROW(queue.push(1));

    EXPECT_EQ(queue.head(), 1);
    EXPECT_EQ(queue.tail(), 1);
}

TEST(TestQueueLib, the_queue_is_full_2) {
    Queue<int> queue(6);
    queue.push(1); queue.push(2); queue.push(3);
    queue.push(4); queue.push(5); queue.push(6);

    EXPECT_EQ(queue.head(), 1);
    EXPECT_EQ(queue.tail(), 6);

    queue.pop(); queue.pop(); queue.pop(); queue.pop();

    EXPECT_EQ(queue.head(), 5);
    EXPECT_EQ(queue.tail(), 6);

    queue.push(11); 

    EXPECT_EQ(queue.head(), 5);
    EXPECT_EQ(queue.tail(), 11);
    
    queue.push(22); 

    EXPECT_EQ(queue.tail(), 22);
    
    queue.push(33);
    
    EXPECT_EQ(queue.tail(), 33); 
    
    queue.push(44);

    EXPECT_EQ(queue.tail(), 44);


    EXPECT_TRUE(queue.is_full());
    EXPECT_FALSE(queue.is_empty());
}