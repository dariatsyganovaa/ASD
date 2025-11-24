#include <gtest/gtest.h>
#include "../lib_dsu/dsu.h"

TEST(TestDSULib, size_constructor) {
    DSU dsu(5);
    EXPECT_EQ(dsu.size(), 5);

    for (size_t i = 0; i < dsu.size(); i++) {
        EXPECT_EQ(dsu.parent()[i], i);
    }
}

TEST(TestDSULib, copy_constructor) {
    DSU dsu1(5);
    EXPECT_EQ(dsu1.size(), 5);

    DSU dsu2(dsu1);
    EXPECT_EQ(dsu2.size(), 5);

    for (size_t i = 0; i < dsu1.size(); i++) {
        EXPECT_EQ(dsu1.parent()[i], dsu2.parent()[i]);
    }
}

TEST(TestDSULib, try_union_with_uncorrect_value) {
    DSU dsu(5);
    EXPECT_THROW(dsu.union_dsu(6, -1), std::out_of_range);
}

TEST(TestDSULib, union_first_case) {
    DSU dsu(5);

    dsu.union_dsu(1, 1);
    for (size_t i = 0; i < dsu.size(); i++) {
         EXPECT_EQ(dsu.rank()[i], 0);
    }
}

TEST(TestDSULib, union_second_case) {
    DSU dsu(3);

    dsu.union_dsu(0, 1);  dsu.union_dsu(1, 2);    
    EXPECT_EQ(dsu.find(1), 0);
    EXPECT_EQ(dsu.find(2), 0);
}

TEST(TestDSULib, union_third_case) {
    DSU dsu(6);

    dsu.union_dsu(0, 1); dsu.union_dsu(2, 3);
    dsu.union_dsu(4, 5); dsu.union_dsu(2, 4);
    dsu.union_dsu(1, 2);
    
    for (size_t i = 0; i < dsu.size(); i++) {
        EXPECT_EQ(dsu.find(i), 2);
    }
}

TEST(TestDSULib, union_forth_case) {
    DSU dsu(4);

    dsu.union_dsu(0, 1); dsu.union_dsu(2, 3); 
    dsu.union_dsu(1, 3);

    for (size_t i = 0; i < dsu.size(); i++) {
        EXPECT_EQ(dsu.find(i), 0);
    }
}

TEST(TestDSULib, try_find_with_uncorrect_value) {
    DSU dsu(5);
    EXPECT_THROW(dsu.find(6), std::out_of_range);
}

TEST(TestDSULib, find) {
    DSU dsu(4);

    dsu.union_dsu(0, 1);
    dsu.union_dsu(2, 3);
    dsu.union_dsu(1, 3);
    EXPECT_EQ(dsu.parent()[3], 2);
    int root = dsu.find(3);
    EXPECT_EQ(root, 0);
    EXPECT_EQ(dsu.parent()[3], 2);
}

TEST(TestDSULib, try_find_rec_with_uncorrect_value) {
    DSU dsu(5);
    EXPECT_THROW(dsu.find_rec(-1), std::out_of_range);
}

TEST(TestDSULib, find_rec) {
    DSU dsu(4);

    dsu.union_dsu(0, 1);
    dsu.union_dsu(2, 3);
    dsu.union_dsu(1, 3);
    EXPECT_EQ(dsu.parent()[3], 2);
    int root = dsu.find_rec(3);
    EXPECT_EQ(root, 0);
    EXPECT_EQ(dsu.parent()[3], 0);
}
