#include <gtest/gtest.h>
#include "../AdjacentVertexIter.h"

class AdjacentVertexIterTest : public ::testing::Test {
protected:
    std::vector<int> vertices{10, 20, 30, 40, 50};
};

TEST_F(AdjacentVertexIterTest, DereferenceOperator) {
    AdjacentVertexIter<int> it(vertices.begin(), vertices.end());
    EXPECT_EQ(*it, 10);
}

TEST_F(AdjacentVertexIterTest, IncrementOperator) {
    AdjacentVertexIter<int> it(vertices.begin(), vertices.end());
    ++it;
    EXPECT_EQ(*it, 20);
}

TEST_F(AdjacentVertexIterTest, PostIncrementOperator) {
    AdjacentVertexIter<int> it(vertices.begin(), vertices.end());
    AdjacentVertexIter<int> itCopy = it++;
    EXPECT_EQ(*itCopy, 10);
    EXPECT_EQ(*it, 20);
}

TEST_F(AdjacentVertexIterTest, EqualityOperator) {
    AdjacentVertexIter<int> it1(vertices.begin(), vertices.end());
    AdjacentVertexIter<int> it2(vertices.begin(), vertices.end());
    EXPECT_TRUE(it1 == it2);

    ++it2;
    EXPECT_FALSE(it1 == it2);
}

TEST_F(AdjacentVertexIterTest, InequalityOperator) {
    AdjacentVertexIter<int> it1(vertices.begin(), vertices.end());
    AdjacentVertexIter<int> it2(vertices.begin(), vertices.end());
    EXPECT_FALSE(it1 != it2);

    ++it2;
    EXPECT_TRUE(it1 != it2);
}

TEST_F(AdjacentVertexIterTest, EndIterator) {
    AdjacentVertexIter<int> it(vertices.end(), vertices.end());
    EXPECT_EQ(it, AdjacentVertexIter<int>(vertices.end(), vertices.end()));
}

TEST_F(AdjacentVertexIterTest, IteratorTraversal) {
    AdjacentVertexIter<int> it(vertices.begin(), vertices.end());
    std::vector<int> results;

    for (; it != AdjacentVertexIter<int>(vertices.end(), vertices.end()); ++it) {
        results.push_back(*it);
    }

    EXPECT_EQ(results, vertices);
}