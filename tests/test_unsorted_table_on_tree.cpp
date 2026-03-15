#include <gtest/gtest.h>
#include <string>
#include "../lib_unsorted_table_on_tree/unsortedtableontree.h" 

TEST(TestUnsortedTableOnTree, init) {
    UnsortedTableOnTree<std::string, int> table;
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(table.size(), size_t(0));
}

TEST(TestUnsortedTableOnTree, insert_into_empty) {
    UnsortedTableOnTree<std::string, int> table;
    EXPECT_TRUE(table.is_empty());
    table.insert("first", 10);
    EXPECT_FALSE(table.is_empty());
    EXPECT_EQ(table.size(), size_t(1));
}

TEST(TestUnsortedTableOnTree, insert_and_found_elem) {
    UnsortedTableOnTree<std::string, int> table;
    table.insert("first", 10);
    table.insert("second", 20);
    table.insert("third", 30);
    EXPECT_EQ(table.size(), size_t(3));
    EXPECT_EQ(table.found("first"), 10);
    EXPECT_EQ(table.found("second"), 20);
    EXPECT_EQ(table.found("third"), 30);
}

TEST(TestUnsortedTableOnTree, try_insert_duplicate) {
    UnsortedTableOnTree<std::string, int> table;
    table.insert("first", 10);
    ASSERT_THROW(table.insert("first", 20), std::logic_error);
    EXPECT_EQ(table.size(), size_t(1));
    EXPECT_FALSE(table.is_empty());
}

TEST(TestUnsortedTableOnTree, erase_elem) {
    UnsortedTableOnTree<std::string, int> table;
    table.insert("first", 10);
    table.insert("second", 20);
    table.erase("first");
    EXPECT_EQ(table.size(), size_t(1));
    EXPECT_EQ(table.found("second"), 20);
    EXPECT_THROW(table.found("first"), std::logic_error);
}

TEST(TestUnsortedTableOnTree, erase_last_elem) {
    UnsortedTableOnTree<std::string, int> table;
    table.insert("first", 10);
    table.erase("first");
    EXPECT_EQ(table.size(), size_t(0));
    EXPECT_TRUE(table.is_empty());
}

TEST(TestUnsortedTableOnTree, exceptions) {
    UnsortedTableOnTree<std::string, int> table;
    table.insert("first", 10);
    EXPECT_THROW(table.insert("first", 20), std::logic_error);
    EXPECT_THROW(table.erase("second"), std::logic_error);
    EXPECT_THROW(table.found("second"), std::logic_error);
}

TEST(TestUnsortedTableOnTree, clear_test) {
    UnsortedTableOnTree<std::string, int> table;
    table.insert("first", 10);
    table.insert("second", 20);
    table.erase("first");
    table.erase("second");
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(table.size(), size_t(0));
    ASSERT_NO_THROW(table.insert("new", 100));
    EXPECT_EQ(table.found("new"), 100);
    EXPECT_EQ(table.size(), size_t(1));
}

TEST(TestUnsortedTableOnTree, reference_modification) {
    UnsortedTableOnTree<std::string, int> table;
    table.insert("first", 10);
    table.found("first") = 20;
    EXPECT_EQ(table.found("first"), 20);
}

TEST(TestUnsortedTableOnTree, mixed_test) {
    UnsortedTableOnTree<std::string, int> table;
    table.insert("first", 10);
    table.insert("second", 20);
    table.insert("third", 30);
    EXPECT_EQ(table.size(), size_t(3));
    EXPECT_EQ(table.found("first"), 10);
    EXPECT_EQ(table.found("second"), 20);
    EXPECT_EQ(table.found("third"), 30);
    //std::cout << table;
    table.erase("second");
    EXPECT_EQ(table.size(), size_t(2));
    EXPECT_THROW(table.found("second"), std::logic_error);
    EXPECT_EQ(table.found("first"), 10);
    EXPECT_EQ(table.found("third"), 30);
    //std::cout << table;
    table.insert("fourth", 40);
    EXPECT_EQ(table.size(), size_t(3));
    EXPECT_EQ(table.found("fourth"), 40);
    EXPECT_EQ(table.found("third"), 30);
    //std::cout << table;
}