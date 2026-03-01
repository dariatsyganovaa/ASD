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

    std::string expect_keys[] = {"a", "b", "d"};
    int expect_values[] = {3, 1, 2};

    for (int i = 0; i < table.size(); i++) {
        EXPECT_EQ(table.get_key(i), expect_keys[i]);
        EXPECT_EQ(table[i], expect_values[i]);
    }

    EXPECT_EQ(table.size(), size_t(3));
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
    table.insert("zero", 0);
    table.erase("first");

    std::string expect_keys[] = { "second", "zero" };
    int expect_values[] = { 20, 0 };

    for (int i = 0; i < table.size(); i++) {
        EXPECT_EQ(table.get_key(i), expect_keys[i]);
        EXPECT_EQ(table[i], expect_values[i]);
    }

    EXPECT_EQ(table.size(), size_t(2));
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

    std::string expect_keys1[] = { "ab", "abc", "abcd" };
    int expect_values1[] = { 20, 10, 30 };

    for (int i = 0; i < table.size(); i++) {
        EXPECT_EQ(table.get_key(i), expect_keys1[i]);
        EXPECT_EQ(table[i], expect_values1[i]);
    }

    EXPECT_EQ(table.size(), size_t(3));

    table.erase("ab");

    std::string expect_keys2[] = { "abc", "abcd" };
    int expect_values2[] = { 10, 30 };

    for (int i = 0; i < table.size(); i++) {
        EXPECT_EQ(table.get_key(i), expect_keys2[i]);
        EXPECT_EQ(table[i], expect_values2[i]);
    }

    EXPECT_EQ(table.size(), size_t(2));
    EXPECT_THROW(table.found("ab"), std::logic_error);

    table.insert("a", 40);

    std::string expect_keys3[] = { "a", "abc", "abcd" };
    int expect_values3[] = { 40, 10, 30 };

    for (int i = 0; i < table.size(); i++) {
        EXPECT_EQ(table.get_key(i), expect_keys3[i]);
        EXPECT_EQ(table[i], expect_values3[i]);
    }

    EXPECT_EQ(table.size(), size_t(3));
}
