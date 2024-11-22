#include <iostream>
#include "DirectedGraph.h"
#include "EdgeIter.h"
#include "VertexIter.h"
#include "IncidentEdgeIter.h"
#include "gtest/gtest.h"

int main() {

    DirectedGraph<int> graph;

    try {

        graph.addVertex(1);
        graph.addVertex(2);
        graph.addVertex(3);
        graph.addVertex(4);

        graph.addEdge(1, 2);
        graph.addEdge(1, 3);
        graph.addEdge(2, 4);
        graph.addEdge(3, 4);
        graph.addEdge(4, 1);

        std::cout << "Graph initialized." << std::endl;
        std::cout << "Vertex count: " << graph.vertexCount() << std::endl;
        std::cout << "Edge count: " << graph.edgeCount() << std::endl;

        std::cout << "Out-degree of vertex 1: " << graph.vertexOutDegree(1) << std::endl;
        std::cout << "In-degree of vertex 4: " << graph.vertexInDegree(4) << std::endl;

        std::cout << "Incident edges from vertex 1:" << std::endl;
        for (auto it = graph.incidentEdgeBegin(1); it != graph.incidentEdgeEnd(1); ++it) {
            std::cout << "  Edge to: " << *it << std::endl;
        }

        std::cout << "Removing edge (1 -> 3)..." << std::endl;
        graph.removeEdge(1, 3);
        std::cout << "Edge count after removal: " << graph.edgeCount() << std::endl;

        std::cout << "Removing vertex 2..." << std::endl;
        graph.removeVertex(2);
        std::cout << "Vertex count after removal: " << graph.vertexCount() << std::endl;
        std::cout << "Edge count after removal: " << graph.edgeCount() << std::endl;

        std::cout << "Outgoing edges from vertex 4:" << std::endl;
        for (auto it = graph.edgeBegin(4); it != graph.edgeEnd(4); ++it) {
            std::cout << "  Edge to: " << *it << std::endl;
        }
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
