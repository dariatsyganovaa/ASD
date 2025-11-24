#include <gtest/gtest.h>
#include "../lib_queue_on_list/queue_on_list.h"

TEST(TestQueueOnListLib, size_constructor) {
    QueueOnList<int> queue;

    EXPECT_TRUE(queue.is_empty());
}

TEST(TestQueueOnListLib, copy_constructor) {
    QueueOnList<int> queue1;
    queue1.push(1); queue1.push(2); queue1.push(3);

    QueueOnList<int> queue2(queue1);

    EXPECT_EQ(queue1.head(), queue2.head());
    EXPECT_EQ(queue1.tail(), queue2.tail());

    queue1.pop();
    queue2.pop();

    EXPECT_EQ(queue1.head(), 2);
    EXPECT_EQ(queue2.head(), 2);
}

TEST(TestQueueOnListLib, push_elem) {
    QueueOnList<int> queue;
    queue.push(1); queue.push(2); queue.push(3);

    EXPECT_EQ(queue.head(), 1);
    EXPECT_EQ(queue.tail(), 3);
    EXPECT_FALSE(queue.is_empty());
}

TEST(TestQueueOnListLib, pop_elem) {
    QueueOnList<int> queue;
    queue.push(1); queue.push(2); queue.push(3);
    queue.push(4); queue.push(5); queue.push(6);

    queue.pop(); queue.pop(); queue.pop();

    EXPECT_EQ(queue.head(), 4);
    EXPECT_EQ(queue.tail(), 6);
    EXPECT_FALSE(queue.is_empty());
}

TEST(TestQueueOnListLib, try_pop_elem_from_an_empty_queue) {
    QueueOnList<int> queue;

    ASSERT_ANY_THROW(queue.pop());
    EXPECT_TRUE(queue.is_empty());
}

TEST(TestQueueOnListLib, tail_elem) {
    QueueOnList<int> queue;
    queue.push(1); queue.push(2); queue.push(3);
    queue.push(4); queue.push(5); queue.push(6);

    queue.pop();
    EXPECT_EQ(queue.tail(), 6);
}

TEST(TestQueueOnListLib, try_tail_elem_from_an_empty_queue) {
    QueueOnList<int> queue;

    ASSERT_ANY_THROW(queue.tail());
    EXPECT_TRUE(queue.is_empty());
}

TEST(TestQueueOnListLib, head_elem) {
    QueueOnList<int> queue;
    queue.push(1); queue.push(2); queue.push(3);
    queue.push(4); queue.push(5); queue.push(6);

    EXPECT_EQ(queue.head(), 1);
    queue.pop();
    EXPECT_EQ(queue.head(), 2);
    queue.pop();
    EXPECT_EQ(queue.head(), 3);
}

TEST(TestQueueOnListLib, try_head_elem_from_an_empty_queue) {
    QueueOnList<int> queue;

    ASSERT_ANY_THROW(queue.head());
    EXPECT_TRUE(queue.is_empty());
}

TEST(TestQueueOnListLib, the_queue_is_empty) {
    QueueOnList<int> queue;

    EXPECT_TRUE(queue.is_empty());
}

TEST(TestQueueOnListLib, the_queue_is_not_empty) {
    QueueOnList<int> queue;
    queue.push(1);

    EXPECT_FALSE(queue.is_empty());
}

TEST(TestQueueOnListLib, the_queue_is_empty_after_pop) {
    QueueOnList<int> queue;
    queue.push(1); queue.push(2); queue.push(3);
    queue.pop(); queue.pop(); queue.pop();

    EXPECT_TRUE(queue.is_empty());
}

TEST(TestQueueOnListLib, clear_the_queue) {
    QueueOnList<int> queue;
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
