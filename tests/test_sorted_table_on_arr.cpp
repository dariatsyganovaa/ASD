#include <gtest/gtest.h>
#include <string>
#include "../lib_sorted_table_on_arr/sortedtableonarr.h" 

TEST(TestSortedTableM, init) {
    SortedTableM<std::string, int> table;
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(table.size(), size_t(0));
}

TEST(TestSortedTableM, insert_into_empty) {
    SortedTableM<std::string, int> table;
    EXPECT_TRUE(table.is_empty());

    table.insert("b", 1); 

    EXPECT_FALSE(table.is_empty());
    EXPECT_EQ(table.size(), size_t(1));
}

TEST(TestSortedTableM, insert_and_found_elem) {
    SortedTableM<std::string, int> table;
    table.insert("b", 1);
    table.insert("a", 3);
    table.insert("d", 2);
    std::cout << table;

    EXPECT_EQ(table.size(), size_t(3));
    EXPECT_EQ(table.found("b"), 1);
    EXPECT_EQ(table.found("d"), 2);
    EXPECT_EQ(table.found("a"), 3);
}

TEST(TestSortedTableM, try_insert_duplicate) {
    SortedTableM<std::string, int> table;
    table.insert("b", 1);

    ASSERT_THROW(table.insert("b", 1), std::logic_error);

    EXPECT_EQ(table.size(), size_t(1));
    EXPECT_FALSE(table.is_empty());
}

TEST(TestSortedTableM, erase_elem) {
    SortedTableM<std::string, int> table;
    table.insert("first", 10);
    table.insert("second", 20);
    table.erase("first");

    std::cout << table;
    EXPECT_EQ(table.size(), size_t(1));
    EXPECT_EQ(table.found("second"), 20);
    EXPECT_THROW(table.found("first"), std::logic_error);
}

TEST(TestSortedTableM, erase_last_elem) {
    SortedTableM<std::string, int> table;
    table.insert("first", 10);
    table.erase("first");

    EXPECT_EQ(table.size(), size_t(0));
    EXPECT_TRUE(table.is_empty());
}

TEST(TestSortedTableM, exceptions) {
    SortedTableM<std::string, int> table;
    table.insert("first", 10);

    EXPECT_THROW(table.insert("first", 20), std::logic_error);
    EXPECT_THROW(table.erase("second"), std::logic_error);
    EXPECT_THROW(table.found("second"), std::logic_error);
}

TEST(TestSortedTableM, clear_test) {
    SortedTableM<std::string, int> table;
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

TEST(TestSortedTableM, reference_modification) {
    SortedTableM<std::string, int> table;
    table.insert("first", 10);
    table.found("first") = 20;

    EXPECT_EQ(table.found("first"), 20);
}

TEST(TestSortedTableM, mixed_test) {
    SortedTableM<std::string, int> table;

    table.insert("abc", 10);
    table.insert("ab", 20);
    table.insert("abcd", 30);

    EXPECT_EQ(table.size(), size_t(3));
    EXPECT_EQ(table.found("abc"), 10);
    EXPECT_EQ(table.found("ab"), 20);
    EXPECT_EQ(table.found("abcd"), 30);
    std::cout << table;

    table.erase("ab");

    EXPECT_EQ(table.size(), size_t(2));
    EXPECT_THROW(table.found("ab"), std::logic_error);
    EXPECT_EQ(table.found("abc"), 10);
    EXPECT_EQ(table.found("abcd"), 30);
    std::cout << table;

    table.insert("a", 40);

    EXPECT_EQ(table.size(), size_t(3));
    EXPECT_EQ(table.found("a"), 40);
    EXPECT_EQ(table.found("abcd"), 30);
    std::cout << table;
}
