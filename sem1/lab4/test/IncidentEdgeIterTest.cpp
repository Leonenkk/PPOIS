#include <gtest/gtest.h>
#include "../IncidentEdgeIter.h"
#include <list>

class IncidentEdgeIterTest : public ::testing::Test {
protected:
    std::list<size_t> edges{1, 2, 3, 4, 5};
};

TEST_F(IncidentEdgeIterTest, DereferenceOperator) {
    IncidentEdgeIter<size_t> it(edges.begin(), edges.begin(), edges.end());
    EXPECT_EQ(*it, 1);
}

TEST_F(IncidentEdgeIterTest, IncrementOperator) {
    IncidentEdgeIter<size_t> it(edges.begin(), edges.begin(), edges.end());
    ++it;
    EXPECT_EQ(*it, 2);
}

TEST_F(IncidentEdgeIterTest, PostIncrementOperator) {
    IncidentEdgeIter<size_t> it(edges.begin(), edges.begin(), edges.end());
    IncidentEdgeIter<size_t> itCopy = it++;
    EXPECT_EQ(*itCopy, 1);
    EXPECT_EQ(*it, 2);
}

TEST_F(IncidentEdgeIterTest, DecrementOperator) {
    IncidentEdgeIter<size_t> it(edges.end(), edges.begin(), edges.end());
    --it;
    EXPECT_EQ(*it, 5);
}

TEST_F(IncidentEdgeIterTest, PostDecrementOperator) {
    IncidentEdgeIter<size_t> it(edges.end(), edges.begin(), edges.end());
    IncidentEdgeIter<size_t> itCopy = it--;
    EXPECT_EQ(*itCopy, 5);
    --it;
    EXPECT_EQ(*it, 4);
}

TEST_F(IncidentEdgeIterTest, EqualityOperator) {
    IncidentEdgeIter<size_t> it1(edges.begin(), edges.begin(), edges.end());
    IncidentEdgeIter<size_t> it2(edges.begin(), edges.begin(), edges.end());
    EXPECT_TRUE(it1 == it2);

    ++it2;
    EXPECT_FALSE(it1 == it2);
}

TEST_F(IncidentEdgeIterTest, InequalityOperator) {
    IncidentEdgeIter<size_t> it1(edges.begin(), edges.begin(), edges.end());
    IncidentEdgeIter<size_t> it2(edges.begin(), edges.begin(), edges.end());
    EXPECT_FALSE(it1 != it2);

    ++it2;
    EXPECT_TRUE(it1 != it2);
}

TEST_F(IncidentEdgeIterTest, IteratorTraversal) {
    IncidentEdgeIter<size_t> it(edges.begin(), edges.begin(), edges.end());
    std::vector<size_t> results;

    for (; it != IncidentEdgeIter<size_t>(edges.end(), edges.begin(), edges.end()); ++it) {
        results.push_back(*it);
    }

    EXPECT_EQ(results.size(), edges.size());
    EXPECT_EQ(results[0], 1);
    EXPECT_EQ(results[1], 2);
    EXPECT_EQ(results[2], 3);
    EXPECT_EQ(results[3], 4);
    EXPECT_EQ(results[4], 5);
}