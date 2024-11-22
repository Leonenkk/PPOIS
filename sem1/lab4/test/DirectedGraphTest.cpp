#include <gtest/gtest.h>
#include "../DirectedGraph.h"

class DirectedGraphTest : public ::testing::Test {
protected:
    DirectedGraph<std::string> graph;

    void SetUp() override {
        graph.addVertex("A");
        graph.addVertex("B");
        graph.addVertex("C");
        graph.addEdge("A", "B");
        graph.addEdge("B", "C");
    }
};

TEST_F(DirectedGraphTest, AddVertex) {
    graph.addVertex("D");
    EXPECT_TRUE(graph.containsVertex("D"));
    EXPECT_EQ(graph.vertexCount(), 4);
}

TEST_F(DirectedGraphTest, AddExistingVertex) {
    EXPECT_THROW(graph.addVertex("A"), std::invalid_argument);
}

TEST_F(DirectedGraphTest, AddEdge) {
    graph.addEdge("C", "A");
    EXPECT_TRUE(graph.containsEdge("C", "A"));
    EXPECT_EQ(graph.edgeCount(), 3);
}

TEST_F(DirectedGraphTest, AddEdgeWithNonExistingVertex) {
    EXPECT_THROW(graph.addEdge("A", "D"), std::invalid_argument);
}

TEST_F(DirectedGraphTest, RemoveVertex) {
    graph.removeVertex("B");
    EXPECT_FALSE(graph.containsVertex("B"));
    EXPECT_EQ(graph.vertexCount(), 2);
    EXPECT_FALSE(graph.containsEdge("A", "B"));
}

TEST_F(DirectedGraphTest, RemoveNonExistingVertex) {
    EXPECT_THROW(graph.removeVertex("D"), std::invalid_argument);
}

TEST_F(DirectedGraphTest, RemoveEdge) {
    graph.removeEdge("A", "B");
    EXPECT_FALSE(graph.containsEdge("A", "B"));
    EXPECT_EQ(graph.edgeCount(), 1);
}

TEST_F(DirectedGraphTest, VertexInDegree) {
    EXPECT_EQ(graph.vertexInDegree("B"), 1);
    EXPECT_EQ(graph.vertexInDegree("A"), 0);
}

TEST_F(DirectedGraphTest, VertexOutDegree) {
    EXPECT_EQ(graph.vertexOutDegree("A"), 1);
    EXPECT_EQ(graph.vertexOutDegree("B"), 1);
}

TEST_F(DirectedGraphTest, EdgeCount) {
    EXPECT_EQ(graph.edgeCount(), 2);
}

TEST_F(DirectedGraphTest, VertexCount) {
    EXPECT_EQ(graph.vertexCount(), 3);
}

TEST_F(DirectedGraphTest, IncidentEdgeIteration) {
    auto it = graph.incidentEdgeBegin("A");
    auto end = graph.incidentEdgeEnd("A");
    std::vector<size_t> edges;

    for (; it != end; ++it) {
        edges.push_back(*it);
    }

    EXPECT_EQ(edges.size(), 1);
    EXPECT_EQ(edges[0], 1);
}