#include <gtest/gtest.h>
#include <string>
#include "../lib_sorted_table_on_bstree/sortedtableonbstree.h" 

TEST(TestSortedTableOnBSTree, init) {
    SortedTableOnBSTree<std::string, int> table;
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(table.size(), size_t(0));
}

TEST(TestSortedTableOnBSTree, insert_into_empty) {
    SortedTableOnBSTree<std::string, int> table;
    EXPECT_TRUE(table.is_empty());

    table.insert("b", 1); 

    EXPECT_FALSE(table.is_empty());
    EXPECT_EQ(table.size(), size_t(1));
}

TEST(TestSortedTableOnBSTree, insert_and_found_elem) {
    SortedTableOnBSTree<std::string, int> table;
    table.insert("b", 1);
    table.insert("a", 3);
    table.insert("d", 2);

    std::stringstream ss;
    table.print(ss);
    std::string s = ss.str();

    EXPECT_TRUE(s.find("a") < s.find("b"));
    EXPECT_TRUE(s.find("b") < s.find("d"));
    EXPECT_EQ(table.size(), size_t(3));
}

TEST(TestSortedTableOnBSTree, try_insert_duplicate) {
    SortedTableOnBSTree<std::string, int> table;
    table.insert("b", 1);
    ASSERT_THROW(table.insert("b", 1), std::logic_error);
    EXPECT_EQ(table.size(), size_t(1));
    EXPECT_FALSE(table.is_empty());
}

TEST(TestSortedTableOnBSTree, erase_elem) {
    SortedTableOnBSTree<std::string, int> table;
    table.insert("first", 10);
    table.insert("second", 20);
    table.insert("zero", 0);
    table.erase("first");

    std::stringstream ss;
    table.print(ss);
    std::string s = ss.str();
    EXPECT_TRUE(s.find("second") < s.find("zero"));

    EXPECT_EQ(table.size(), size_t(2));
    EXPECT_THROW(table.found("first"), std::logic_error);
}

TEST(TestSortedTableOnBSTree, erase_last_elem) {
    SortedTableOnBSTree<std::string, int> table;
    table.insert("first", 10);
    table.erase("first");
    EXPECT_EQ(table.size(), size_t(0));
    EXPECT_TRUE(table.is_empty());
}

TEST(TestSortedTableOnBSTree, exceptions) {
    SortedTableOnBSTree<std::string, int> table;
    table.insert("first", 10);
    EXPECT_THROW(table.insert("first", 20), std::logic_error);
    EXPECT_THROW(table.erase("second"), std::logic_error);
    EXPECT_THROW(table.found("second"), std::logic_error);
}

TEST(TestSortedTableOnBSTree, clear_test) {
    SortedTableOnBSTree<std::string, int> table;
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

TEST(TestSortedTableOnBSTree, reference_modification) {
    SortedTableOnBSTree<std::string, int> table;
    table.insert("first", 10);
    table.found("first") = 20;
    EXPECT_EQ(table.found("first"), 20);
}

TEST(TestSortedTableOnBSTree, mixed_test) {
    SortedTableOnBSTree<std::string, int> table;
    table.insert("abc", 10);
    table.insert("ab", 20);
    table.insert("abcd", 30);

    std::stringstream ss;
    table.print(ss);
    std::string s = ss.str();
    EXPECT_TRUE(s.find("ab") < s.find("abc"));
    EXPECT_TRUE(s.find("abc") < s.find("abcd"));

    EXPECT_EQ(table.size(), size_t(3));

    table.erase("ab");

    EXPECT_TRUE(s.find("abc") < s.find("abcd"));

    EXPECT_EQ(table.size(), size_t(2));

    EXPECT_THROW(table.found("ab"), std::logic_error);

    table.insert("a", 40);

    EXPECT_TRUE(s.find("a") < s.find("abc"));
    EXPECT_TRUE(s.find("abc") < s.find("abcd"));

    EXPECT_EQ(table.size(), size_t(3));
}
