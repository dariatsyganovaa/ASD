#include <gtest/gtest.h>
#include <string>
#include "../lib_unsorted_table_on_list/unsortedtableonlist.h" 

TEST(TestUnsortedTableOnList, init) {
    UnsortedTableOnList<std::string, int> table;
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(table.size(), size_t(0));
}

TEST(TestUnsortedTableOnList, insert_and_found_elem) {
    UnsortedTableOnList<std::string, int> table;
    table.insert("first", 10);
    table.insert("second", 20);
    table.insert("third", 30);

    EXPECT_EQ(table.size(), size_t(3));
    EXPECT_EQ(table.found("first"), 10);
    EXPECT_EQ(table.found("second"), 20);
    EXPECT_EQ(table.found("third"), 30);
}

TEST(TestUnsortedTableOnList, erase_elem) {
    UnsortedTableOnList<std::string, int> table;
    table.insert("first", 10);
    table.insert("second", 20);
    table.erase("first");

    EXPECT_EQ(table.size(), size_t(1));
    EXPECT_EQ(table.found("second"), 20);
    EXPECT_THROW(table.found("first"), std::logic_error);
}

TEST(TestUnsortedTableOnList, exceptions) {
    UnsortedTableOnList<std::string, int> table;
    table.insert("first", 10);

    EXPECT_THROW(table.insert("first", 20), std::logic_error);
    EXPECT_THROW(table.erase("second"), std::logic_error);
    EXPECT_THROW(table.found("second"), std::logic_error);
}

TEST(TestUnsortedTableOnList, clear_test) {
    UnsortedTableOnList<std::string, int> table;
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

TEST(TestUnsortedTableOnList, reference_modification) {
    UnsortedTableOnList<std::string, int> table;
    table.insert("first", 10);
    table.found("first") = 20;

    EXPECT_EQ(table.found("first"), 20);
}

TEST(TestUnsortedTableOnList, mixed_test) {
    UnsortedTableOnList<std::string, int> table;

    table.insert("first", 10);
    table.insert("second", 20);
    table.insert("third", 30);

    EXPECT_EQ(table.size(), size_t(3));
    EXPECT_EQ(table.found("first"), 10);
    EXPECT_EQ(table.found("second"), 20);
    EXPECT_EQ(table.found("third"), 30);
    //table.print(std::cout);

    table.erase("second");

    EXPECT_EQ(table.size(), size_t(2));
    EXPECT_THROW(table.found("second"), std::logic_error); 
    EXPECT_EQ(table.found("first"), 10); 
    EXPECT_EQ(table.found("third"), 30);
    //table.print(std::cout);

    table.insert("fourth", 40);

    EXPECT_EQ(table.size(), size_t(3));
    EXPECT_EQ(table.found("fourth"), 40);
    EXPECT_EQ(table.found("third"), 30);
    //table.print(std::cout);
}