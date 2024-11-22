#include <gtest/gtest.h>
#include "../VertexIter.h"
#include <vector>

class VertexIterTest : public ::testing::Test {
protected:
    std::vector<int> vertices{1, 2, 3, 4, 5};
};

TEST_F(VertexIterTest, DereferenceOperator) {
    VertexIter<int> it(vertices.begin());
    EXPECT_EQ(*it, 1);
}

TEST_F(VertexIterTest, IncrementOperator) {
    VertexIter<int> it(vertices.begin());
    ++it;
    EXPECT_EQ(*it, 2);
}

TEST_F(VertexIterTest, PostIncrementOperator) {
    VertexIter<int> it(vertices.begin());
    VertexIter<int> itCopy = it++;
    EXPECT_EQ(*itCopy, 1);
    EXPECT_EQ(*it, 2);
}

TEST_F(VertexIterTest, EqualityOperator) {
    VertexIter<int> it1(vertices.begin());
    VertexIter<int> it2(vertices.begin());
    EXPECT_TRUE(it1 == it2);

    ++it2;
    EXPECT_FALSE(it1 == it2);
}

TEST_F(VertexIterTest, InequalityOperator) {
    VertexIter<int> it1(vertices.begin());
    VertexIter<int> it2(vertices.begin());
    EXPECT_FALSE(it1 != it2);

    ++it2;
    EXPECT_TRUE(it1 != it2);
}

TEST_F(VertexIterTest, IteratorTraversal) {
    VertexIter<int> it(vertices.begin());
    std::vector<int> results;

    for (; it != VertexIter<int>(vertices.end()); ++it) {
        results.push_back(*it);
    }

    EXPECT_EQ(results, vertices);
}

TEST_F(VertexIterTest, EndIterator) {
    VertexIter<int> it(vertices.end());
    EXPECT_EQ(it, VertexIter<int>(vertices.end()));
}