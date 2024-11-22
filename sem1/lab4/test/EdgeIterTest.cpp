#include <gtest/gtest.h>
#include "../EdgeIter.h"

class EdgeIterTest : public ::testing::Test {
protected:
    std::list<size_t> edgeList{1, 2, 3, 4, 5};
};

TEST_F(EdgeIterTest, DereferenceOperator) {
    EdgeIter<size_t> it(edgeList.begin());
    EXPECT_EQ(*it, 1);
}

TEST_F(EdgeIterTest, IncrementOperator) {
    EdgeIter<size_t> it(edgeList.begin());
    ++it;
    EXPECT_EQ(*it, 2);
}

TEST_F(EdgeIterTest, PostIncrementOperator) {
    EdgeIter<size_t> it(edgeList.begin());
    EdgeIter<size_t> itCopy = it++;
    EXPECT_EQ(*itCopy, 1);
    EXPECT_EQ(*it, 2);
}

TEST_F(EdgeIterTest, EqualityOperator) {
    EdgeIter<size_t> it1(edgeList.begin());
    EdgeIter<size_t> it2(edgeList.begin());
    EXPECT_TRUE(it1 == it2);

    ++it2;
    EXPECT_FALSE(it1 == it2);
}

TEST_F(EdgeIterTest, InequalityOperator) {
    EdgeIter<size_t> it1(edgeList.begin());
    EdgeIter<size_t> it2(edgeList.begin());
    EXPECT_FALSE(it1 != it2);

    ++it2;
    EXPECT_TRUE(it1 != it2);
}