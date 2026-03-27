#include <gtest/gtest.h>
#include "../lib_bstree/bstree.h" 

TEST(TestBSTreeLib, can_create) {
    ASSERT_NO_THROW((BSTree<std::string, int>()));
}

TEST(TestBSTreeLib, check_default_create) {
    BSTree<std::string, int> t;
    EXPECT_EQ(nullptr, t.root());
    EXPECT_TRUE(t.is_empty());
    EXPECT_FALSE(!t.is_empty());
}

TEST(TestBSTreeLib, is_empty_after_insert_returns_false) {
    BSTree<int, std::string> t;
    t.insert(1, "one");
    EXPECT_TRUE(!t.is_empty());
    EXPECT_FALSE(t.is_empty());
}

TEST(TestBSTreeLib, check_insert_one_elem) {
    BSTree<int, std::string> t;
    t.insert(1, "one");
    EXPECT_EQ(1, t.root()->data.first);
    EXPECT_FALSE(t.is_empty());
}

TEST(TestBSTreeLib, check_insert_multiple_elems) {
    BSTree<int, std::string> t;
    t.insert(5, "five"); t.insert(1, "one"); t.insert(7, "seven");
    EXPECT_EQ(5, t.root()->data.first);
    EXPECT_EQ(1, t.root()->left->data.first);
    EXPECT_EQ(7, t.root()->right->data.first);
    EXPECT_FALSE(t.is_empty());
}

TEST(TestBSTreeLib, check_insert_multiple_elems2) {
    BSTree<int, std::string> t;
    t.insert(5, "five"); t.insert(1, "one"); t.insert(7, "seven");
    t.insert(20, "twenty");
    EXPECT_EQ(5, t.root()->data.first);
    EXPECT_EQ(1, t.root()->left->data.first);
    EXPECT_EQ(7, t.root()->right->data.first);
    EXPECT_EQ(20, t.root()->right->right->data.first);
    EXPECT_FALSE(t.is_empty());
}

TEST(TestBSTreeLib, find_existing_elem) {
    BSTree<int, std::string> t;
    t.insert(5, "five"); t.insert(1, "one"); t.insert(3, "three");
    t.insert(7, "seven");
    ASSERT_NE(nullptr, t.find(7));
    EXPECT_EQ("seven", *t.find(7));
}

TEST(TestBSTreeLib, find_root_elem) {
    BSTree<int, std::string> t;
    t.insert(5, "five"); t.insert(1, "one"); t.insert(3, "three");
    t.insert(7, "seven");
    ASSERT_NE(nullptr, t.find(5));
    EXPECT_EQ("five", *t.find(5));
}

TEST(TestBSTreeLib, try_find_elem_in_empty_tree) {
    BSTree<int, std::string> t;
    EXPECT_EQ(nullptr, t.find(1));
    EXPECT_TRUE(t.is_empty());
}

TEST(TestBSTreeLib, try_find_not_existing_elem) {
    BSTree<int, std::string> t;
    t.insert(5, "five"); t.insert(1, "one"); t.insert(3, "three");
    EXPECT_EQ(nullptr, t.find(7));
}

TEST(TestBSTreeLib, check_erase_elem) {
    BSTree<int, std::string> t;
    t.insert(6, "six"); t.insert(4, "four"); t.insert(9, "nine"); 
    t.insert(1, "one"); t.insert(5, "five");
    t.insert(7, "seven"); t.insert(12, "twelve"); t.insert(8, "eight");
    t.erase(7);
    EXPECT_EQ(nullptr, t.find(7));
    EXPECT_NE(nullptr, t.find(8));
    EXPECT_EQ(8, t.root()->right->left->data.first);
}

TEST(TestBSTreeLib, erase_node_without_children) {
    BSTree<int, std::string> t;
    t.insert(5, "five"); t.insert(3, "three"); t.insert(1, "one");
    t.insert(4, "four"); t.insert(9, "nine"); t.insert(7, "seven");
    t.erase(4);
    EXPECT_EQ(nullptr, t.find(4));
    EXPECT_EQ(nullptr, t.root()->left->right);
}

TEST(TestBSTreeLib, erase_node_left_child) {
    BSTree<int, std::string> t;
    t.insert(5, "five"); t.insert(3, "three"); t.insert(1, "one");
    t.insert(4, "four"); t.insert(9, "nine"); t.insert(7, "seven"); 
    t.insert(6, "six"); t.insert(8, "eight");
    EXPECT_EQ(9, t.root()->right->data.first);
    t.erase(9);
    EXPECT_EQ(nullptr, t.find(9));
    EXPECT_EQ(7, t.root()->right->data.first);
}

TEST(TestBSTreeLib, erase_node_right_child) {
    BSTree<int, std::string> t;
    t.insert(11, "eleven"); t.insert(5, "five"); t.insert(13, "thirteen");
    t.insert(7, "seven"); t.insert(6, "six"); t.insert(10, "ten");
    t.insert(12, "twelve"); t.insert(15, "fifteen");
    EXPECT_EQ(5, t.root()->left->data.first);
    t.erase(5);
    EXPECT_EQ(nullptr, t.find(5));
    EXPECT_EQ(7, t.root()->left->data.first);
}

TEST(TestBSTreeLib, erase_elem_with_children) {
    BSTree<int, std::string> t;
    t.insert(6, "six"); t.insert(4, "four"); t.insert(9, "nine");
    t.insert(1, "one"); t.insert(5, "five");
    t.insert(7, "seven"); t.insert(12, "twelve"); t.insert(8, "eight");
    t.erase(9);
    EXPECT_EQ(nullptr, t.find(9));
    EXPECT_EQ(8, t.root()->right->data.first);
}

TEST(TestBSTreeLib, erase_root_with_children) {
    BSTree<int, std::string> t;
    t.insert(5, "five"); t.insert(3, "three"); t.insert(1, "one");
    t.insert(4, "four"); t.insert(7, "seven");
    t.insert(6, "six"); t.insert(8, "eight");
    t.erase(5);
    EXPECT_EQ(nullptr, t.find(5));
    EXPECT_EQ(4, t.root()->data.first);
}

TEST(TestBSTreeLib, erase_root) {
    BSTree<int, std::string> t;
    t.insert(7, "seven");
    t.erase(7);
    EXPECT_EQ(nullptr, t.find(7));
    EXPECT_TRUE(t.is_empty());
}

TEST(TestBSTreeLib, try_erase_elem_in_empty_tree) {
    BSTree<int, std::string> t;
    EXPECT_THROW(t.erase(1), std::logic_error);
    EXPECT_TRUE(t.is_empty());
}

TEST(TestBSTreeLib, try_erase_not_existing_elem) {
    BSTree<int, std::string> t;
    t.insert(5, "five"); t.insert(1, "one"); t.insert(3, "three");
    EXPECT_THROW(t.erase(7), std::logic_error);
}

TEST(TestBSTreeLib, try_erase_not_existing_elem2) {
    BSTree<int, std::string> t;
    t.insert(5, "five"); t.insert(3, "three"); t.insert(1, "one");
    t.insert(4, "four"); t.insert(9, "nine"); t.insert(7, "seven");
    EXPECT_THROW(t.erase(6), std::logic_error);
}

TEST(TestBSTreeLib, check_insert_after_erase) {
    BSTree<int, std::string> t;
    t.insert(1, "one"); t.erase(1);
    EXPECT_TRUE(t.is_empty());
    t.insert(2, "two");
    EXPECT_EQ(2, t.root()->data.first);
    EXPECT_FALSE(t.is_empty());
}

TEST(TestBSTreeLib, check_clear_empty_tree) {
    BSTree<int, std::string> t;
    EXPECT_NO_THROW(t.clear());
    EXPECT_TRUE(t.is_empty());
}

TEST(TestBSTreeLib, clear_not_empty_tree) {
    BSTree<int, std::string> t;
    t.insert(5, "five"); t.insert(1, "one"); t.insert(3, "three");
    t.clear();
    EXPECT_TRUE(t.is_empty());
    EXPECT_EQ(nullptr, t.root());
}

TEST(TestBSTreeLib, try_find_after_clear_tree) {
    BSTree<int, std::string> t;
    t.insert(5, "five"); t.insert(1, "one"); t.insert(3, "three");
    t.clear();
    EXPECT_EQ(nullptr, t.find(5));
    EXPECT_EQ(nullptr, t.find(1));
    EXPECT_EQ(nullptr, t.find(3));
}

TEST(TestBSTreeLib, clear_then_insert_works) {
    BSTree<int, std::string> t;
    t.insert(5, "five"); t.insert(1, "one");
    t.clear();
    t.insert(3, "three");
    EXPECT_TRUE(!t.is_empty());
    EXPECT_EQ(3, t.root()->data.first);
}

TEST(TestBSTreeLib, print_lcr_tree) {
    BSTree<int, std::string> t;
    srand(time(NULL));
    for (int i = 0; i < 10; i++) {
        try {
            t.insert(1 + rand() % 10, "rand_val");
        }
        catch (std::exception& e) {}
    }
    t.print_DLCR();
    std::cout << "\n";
}