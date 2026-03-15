#include <gtest/gtest.h>
#include "../lib_tree/tree.h" 

TEST(TestTreeLib, can_create) {
    ASSERT_NO_THROW((Tree<std::string, int>()));
}

TEST(TestTreeLib, check_default_create) {
    Tree<std::string, int> t;
    EXPECT_EQ(nullptr, t.root());
    EXPECT_TRUE(t.is_empty());
    EXPECT_FALSE(!t.is_empty());
}

TEST(TestTreeLib, is_empty_after_insert_returns_false) {
    Tree<std::string, int> t;
    t.insert("one", 1);
    EXPECT_TRUE(!t.is_empty());
    EXPECT_FALSE(t.is_empty());
}

TEST(TestTreeLib, check_insert_one_elem) {
    Tree<std::string, int> t;
    t.insert("one", 1);
    EXPECT_EQ(1, t.root()->data.second);
    EXPECT_FALSE(t.is_empty());
}

TEST(TestTreeLib, check_insert_multiple_elems) {
    Tree<std::string, int> t;
    t.insert("five", 5); t.insert("one", 1); t.insert("three", 3);
    EXPECT_EQ(5, t.root()->data.second);
    EXPECT_EQ(1, t.root()->left->data.second);
    EXPECT_EQ(3, t.root()->right->data.second);
    EXPECT_FALSE(t.is_empty());
}

TEST(TestTreeLib, check_insert_multiple_elems2) {
    Tree<std::string, int> t;
    t.insert("five", 5); t.insert("one", 1); t.insert("three", 3); t.insert("seven", 7);
    EXPECT_EQ(5, t.root()->data.second);
    EXPECT_EQ(1, t.root()->left->data.second);
    EXPECT_EQ(3, t.root()->right->data.second);
    EXPECT_EQ(7, t.root()->left->left->data.second);
    EXPECT_FALSE(t.is_empty());
}

TEST(TestTreeLib, find_existing_elem) {
    Tree<std::string, int> t;
    t.insert("five", 5); t.insert("one", 1); t.insert("three", 3); t.insert("seven", 7);
    ASSERT_NE(nullptr, t.find("seven"));
    EXPECT_EQ(7, *t.find("seven"));
}

TEST(TestTreeLib, find_root_elem) {
    Tree<std::string, int> t;
    t.insert("five", 5); t.insert("one", 1); t.insert("three", 3); t.insert("seven", 7);
    ASSERT_NE(nullptr, t.find("five"));
    EXPECT_EQ(5, *t.find("five"));
}

TEST(TestTreeLib, try_find_elem_in_empty_tree) {
    Tree<std::string, int> t;
    EXPECT_EQ(nullptr, t.find("one"));
    EXPECT_TRUE(t.is_empty());
}

TEST(TestTreeLib, try_find_not_existing_elem) {
    Tree<std::string, int> t;
    t.insert("five", 5); t.insert("one", 1); t.insert("three", 3);
    EXPECT_EQ(nullptr, t.find("seven"));
}

TEST(TestTreeLib, check_erase_elem) {
    Tree<std::string, int> t;
    t.insert("five", 5); t.insert("one", 1); t.insert("three", 3);
    t.insert("seven", 7); t.insert("two", 2); t.insert("four", 4);
    t.erase("seven");
    EXPECT_EQ(nullptr, t.find("seven"));
    EXPECT_NE(nullptr, t.find("four"));
    EXPECT_EQ(4, t.root()->left->left->data.second);
}

TEST(TestTreeLib, erase_root_with_children) {
    Tree<std::string, int> t;
    t.insert("five", 5); t.insert("one", 1); t.insert("three", 3); 
    t.insert("seven", 7); t.insert("two", 2); t.insert("four", 4);
    t.erase("seven");
    t.erase("five");
    EXPECT_EQ(nullptr, t.find("five"));
    EXPECT_EQ(2, t.root()->data.second);
}

TEST(TestTreeLib, erase_root) {
    Tree<std::string, int> t;
    t.insert("seven", 7);
    t.erase("seven");
    EXPECT_EQ(nullptr, t.find("seven"));
    EXPECT_TRUE(t.is_empty());
}

TEST(TestTreeLib, try_erase_elem_in_empty_tree) {
    Tree<std::string, int> t;
    EXPECT_THROW(t.erase("one"), std::logic_error);
    EXPECT_TRUE(t.is_empty());
}

TEST(TestTreeLib, try_erase_not_existing_elem) {
    Tree<std::string, int> t;
    t.insert("five", 5); t.insert("one", 1); t.insert("three", 3);
    EXPECT_THROW(t.erase("seven"), std::logic_error);
}

TEST(TestTreeLib, check_insert_after_erase) {
    Tree<std::string, int> t;
    t.insert("one", 1); t.erase("one");
    EXPECT_TRUE(t.is_empty());
    t.insert("two", 2);
    EXPECT_EQ(2, t.root()->data.second);
    EXPECT_FALSE(t.is_empty());
}

TEST(TestTreeLib, check_clear_empty_tree) {
    Tree<std::string, int> t;
    EXPECT_NO_THROW(t.clear());
    EXPECT_TRUE(t.is_empty());
}

TEST(TestTreeLib, clear_not_empty_tree) {
    Tree<std::string, int> t;
    t.insert("five", 5); t.insert("one", 1); t.insert("three", 3);
    t.clear();
    EXPECT_TRUE(t.is_empty());
    EXPECT_EQ(nullptr, t.root());
}

TEST(TestTreeLib, try_find_after_clear_tree) {
    Tree<std::string, int> t;
    t.insert("five", 5); t.insert("one", 1); t.insert("three", 3);
    t.clear();
    EXPECT_EQ(nullptr, t.find("five"));
    EXPECT_EQ(nullptr, t.find("one"));
    EXPECT_EQ(nullptr, t.find("three"));
}

TEST(TestTreeLib, clear_then_insert_works) {
    Tree<std::string, int> t;
    t.insert("five", 5); t.insert("one", 1);
    t.clear();
    t.insert("three", 3);
    EXPECT_TRUE(!t.is_empty());
    EXPECT_EQ(3, t.root()->data.second);
}

TEST(TestTreeLib, print_tree) {
    Tree<std::string, int> t;
    t.insert("five", 5); t.insert("one", 1); t.insert("three", 3);
    t.insert("seven", 7); t.insert("two", 2); t.insert("four", 4);

    t.print_W();
    std::cout << "\n";
    t.erase("seven");

    t.print_W();
    std::cout << "\n";
    t.erase("five");

    t.print_W();
    std::cout << "\n";
}

TEST(TestTreeLib, print_lcr_tree) {
    Tree<std::string, int> t;
    t.insert("five", 5); t.insert("one", 1); t.insert("three", 3);
    t.insert("seven", 7); t.insert("two", 2); t.insert("four", 4);

    t.print_DLCR();
    std::cout << "\n";
    t.erase("seven");

    t.print_DLCR();
    std::cout << "\n";
    t.erase("five");

    t.print_DLCR();
    std::cout << "\n";
}

TEST(TestTreeLib, print_lrc_tree) {
    Tree<std::string, int> t;
    t.insert("one", 1); t.insert("two", 2); t.insert("three", 3);
    t.insert("four", 4); t.insert("five", 5); t.insert("six", 6);
    t.insert("seven", 7); t.insert("eight", 8); t.insert("nine", 9);
    t.insert("ten", 10); t.insert("eleven", 11);

    t.print_DLRC();
    std::cout << "\n";
}

TEST(TestTreeLib, print_lrc_tree2) {
    Tree<std::string, int> t;
    t.insert("five", 5); t.insert("one", 1); t.insert("three", 3);
    t.insert("seven", 7); t.insert("two", 2); t.insert("four", 4);

    t.print_DLRC();
    std::cout << "\n";
    t.erase("seven");

    t.print_DLRC();
    std::cout << "\n";
    t.erase("five");

    t.print_DLRC();
    std::cout << "\n";
}

TEST(TestTreeLib, print_clr_tree) {
    Tree<std::string, int> t;
    t.insert("five", 5); t.insert("one", 1); t.insert("three", 3);
    t.insert("seven", 7); t.insert("two", 2); t.insert("four", 4);

    t.print_DCLR();
    std::cout << "\n";
    t.erase("seven");

    t.print_DCLR();
    std::cout << "\n";
    t.erase("five");

    t.print_DCLR();
    std::cout << "\n";
}