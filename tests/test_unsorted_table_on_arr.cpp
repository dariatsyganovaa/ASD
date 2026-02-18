#include <gtest/gtest.h>
#include <string>
#include "../lib_unsorted_table_on_arr/unsortedtable.h" 

TEST(TestUnsortedTableM, init) {
    UnsortedTableM<std::string, int> table;
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(table.size(), size_t(0));
}

TEST(TestUnsortedTableM, insert_into_empty) {
    UnsortedTableM<std::string, int> table;
    EXPECT_TRUE(table.is_empty());

    table.insert("first", 10);

    EXPECT_FALSE(table.is_empty());
    EXPECT_EQ(table.size(), size_t(1));
}

TEST(TestUnsortedTableM, insert_and_found_elem) {
    UnsortedTableM<std::string, int> table;
    table.insert("first", 10);
    table.insert("second", 20);
    table.insert("third", 30);

    EXPECT_EQ(table.size(), size_t(3));
    EXPECT_EQ(table.found("first"), 10);
    EXPECT_EQ(table.found("second"), 20);
    EXPECT_EQ(table.found("third"), 30);
}

TEST(TestUnsortedTableM, try_insert_duplicate) {
    UnsortedTableM<std::string, int> table;
    table.insert("first", 10);

    ASSERT_THROW(table.insert("first", 20), std::logic_error);

    EXPECT_EQ(table.size(), size_t(1));
    EXPECT_FALSE(table.is_empty());
}

TEST(TestUnsortedTableM, erase_elem) {
    UnsortedTableM<std::string, int> table;
    table.insert("first", 10);
    table.insert("second", 20);
    table.erase("first");

    EXPECT_EQ(table.size(), size_t(1));
    EXPECT_EQ(table.found("second"), 20);
    EXPECT_THROW(table.found("first"), std::logic_error);
}

TEST(TestUnsortedTableM, erase_last_elem) {
    UnsortedTableM<std::string, int> table;
    table.insert("first", 10);
    table.erase("first");

    EXPECT_EQ(table.size(), size_t(0));
    EXPECT_TRUE(table.is_empty());
}

TEST(TestUnsortedTableM, exceptions) {
    UnsortedTableM<std::string, int> table;
    table.insert("first", 10);

    EXPECT_THROW(table.insert("first", 20), std::logic_error);
    EXPECT_THROW(table.erase("second"), std::logic_error);
    EXPECT_THROW(table.found("second"), std::logic_error);
}

TEST(TestUnsortedTableM, clear_test) {
    UnsortedTableM<std::string, int> table;
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

TEST(TestUnsortedTableM, reference_modification) {
    UnsortedTableM<std::string, int> table;
    table.insert("first", 10);
    table.found("first") = 20;

    EXPECT_EQ(table.found("first"), 20);
}

TEST(TestUnsortedTableM, mixed_test) {
    UnsortedTableM<std::string, int> table;

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