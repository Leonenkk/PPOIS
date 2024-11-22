#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <list>
#include "EdgeIter.h"
#include "VertexIter.h"
#include "IncidentEdgeIter.h"
#include "AdjacentVertexIter.h"

template <typename T>
class DirectedGraph {
private:
    struct Node {
        T value;
        std::list<size_t> edges;
    };

    std::vector<Node> nodes;
    std::unordered_map<T, size_t> vertexIndexMap;

public:
    bool containsVertex(const T& vertex) const {
        return vertexIndexMap.find(vertex) != vertexIndexMap.end();
    }

    bool containsEdge(const T& from, const T& to) const {
        if (!containsVertex(from) || !containsVertex(to)) return false;
        size_t fromIdx = vertexIndexMap.at(from);
        size_t toIdx = vertexIndexMap.at(to);
        for (const auto& edge : nodes[fromIdx].edges) {
            if (edge == toIdx) return true;
        }
        return false;
    }

    size_t vertexCount() const {
        return nodes.size();
    }

    size_t edgeCount() const {
        size_t count = 0;
        for (const auto& node : nodes) {
            count += node.edges.size();
        }
        return count;
    }

    size_t vertexOutDegree(const T& vertex) const {
        if (!containsVertex(vertex)) {
            throw std::invalid_argument("Vertex does not exist");
        }
        size_t idx = vertexIndexMap.at(vertex);
        return nodes[idx].edges.size();
    }

    size_t vertexInDegree(const T& vertex) const {
        if (!containsVertex(vertex)) {
            throw std::invalid_argument("Vertex does not exist");
        }
        size_t idx = vertexIndexMap.at(vertex);
        size_t inDegree = 0;
        for (const auto& node : nodes) {
            for (const auto& edge : node.edges) {
                if (edge == idx) {
                    ++inDegree;
                }
            }
        }
        return inDegree;
    }

    void addVertex(const T& vertex) {
        if (containsVertex(vertex)) {
            throw std::invalid_argument("Vertex already exists");
        }
        vertexIndexMap[vertex] = nodes.size();
        nodes.push_back({vertex, {}});
    }

    void addEdge(const T& from, const T& to) {
        if (!containsVertex(from) || !containsVertex(to)) {
            throw std::invalid_argument("One or both vertices do not exist");
        }
        size_t fromIdx = vertexIndexMap[from];
        size_t toIdx = vertexIndexMap[to];
        if (!containsEdge(from, to)) {
            nodes[fromIdx].edges.push_back(toIdx);
        }
    }

    void removeVertex(const T& vertex) {
        if (!containsVertex(vertex)) {
            throw std::invalid_argument("Vertex does not exist");
        }
        size_t idx = vertexIndexMap[vertex];
        for (auto& node : nodes) {
            node.edges.remove(idx);
        }
        nodes.erase(nodes.begin() + idx);
        vertexIndexMap.erase(vertex);
        for (auto& [key, value] : vertexIndexMap) {
            if (value > idx) {
                --value;
            }
        }
    }

    void removeEdge(const T& from, const T& to) {
        if (!containsVertex(from) || !containsVertex(to)) {
            throw std::invalid_argument("One or both vertices do not exist");
        }
        size_t fromIdx = vertexIndexMap[from];
        size_t toIdx = vertexIndexMap[to];
        nodes[fromIdx].edges.remove(toIdx);
    }

    void removeEdgeByIter(const typename std::list<size_t>::iterator& edgeIter, const T& from) {
        if (!containsVertex(from)) {
            throw std::invalid_argument("Vertex does not exist");
        }
        size_t fromIdx = vertexIndexMap.at(from);
        nodes[fromIdx].edges.erase(edgeIter);
    }

    void removeVertexByIter(typename std::vector<Node>::iterator vertexIter) {
        size_t idx = vertexIter - nodes.begin();
        for (auto& node : nodes) {
            node.edges.remove(idx);
        }
        vertexIndexMap.erase(vertexIter->value);
        nodes.erase(vertexIter);
        for (auto& [key, value] : vertexIndexMap) {
            if (value > idx) {
                --value;
            }
        }
    }

    EdgeIter<T> edgeBegin(const T& vertex) {
        if (!containsVertex(vertex)) {
            throw std::invalid_argument("Vertex does not exist");
        }
        size_t idx = vertexIndexMap.at(vertex);
        return EdgeIter<T>(nodes[idx].edges.begin());
    }

    EdgeIter<T> edgeEnd(const T& vertex) {
        if (!containsVertex(vertex)) {
            throw std::invalid_argument("Vertex does not exist");
        }
        size_t idx = vertexIndexMap.at(vertex);
        return EdgeIter<T>(nodes[idx].edges.end());
    }

    IncidentEdgeIter<T> incidentEdgeBegin(const T& vertex) {
        if (!containsVertex(vertex)) {
            throw std::invalid_argument("Vertex does not exist");
        }
        size_t idx = vertexIndexMap.at(vertex);
        return IncidentEdgeIter<T>(nodes[idx].edges.begin(), nodes[idx].edges.begin(), nodes[idx].edges.end());
    }

    IncidentEdgeIter<T> incidentEdgeEnd(const T& vertex) {
        if (!containsVertex(vertex)) {
            throw std::invalid_argument("Vertex does not exist");
        }
        size_t idx = vertexIndexMap.at(vertex);
        return IncidentEdgeIter<T>(nodes[idx].edges.end(), nodes[idx].edges.begin(), nodes[idx].edges.end());
    }

    VertexIter<T> vertexBegin() {
        std::vector<T> vertexValues;
        for (const auto& node : nodes) {
            vertexValues.push_back(node.value);
        }
        return VertexIter<T>(vertexValues.begin());
    }

    VertexIter<T> vertexEnd() {
        std::vector<T> vertexValues;
        for (const auto& node : nodes) {
            vertexValues.push_back(node.value);
        }
        return VertexIter<T>(vertexValues.end());
    }

    AdjacentVertexIter<T> adjacentVertexBegin(const T& vertex) {
        if (!containsVertex(vertex)) {
            throw std::invalid_argument("Vertex does not exist");
        }
        size_t idx = vertexIndexMap.at(vertex);
        std::vector<T> neighbors;
        for (const auto& edgeIdx : nodes[idx].edges) {
            if (edgeIdx < nodes.size()) {
                neighbors.push_back(nodes[edgeIdx].value);
            }
        }
        return AdjacentVertexIter<T>(neighbors.begin(), neighbors.end());
    }

    AdjacentVertexIter<T> adjacentVertexEnd(const T& vertex) {
        if (!containsVertex(vertex)) {
            throw std::invalid_argument("Vertex does not exist");
        }
        size_t idx = vertexIndexMap.at(vertex);
        std::vector<T> neighbors;
        for (const auto& edgeIdx : nodes[idx].edges) {
            neighbors.push_back(nodes[edgeIdx].value);
        }
        return AdjacentVertexIter<T>(neighbors.end(), neighbors.end());
    }
};

#endif // DIRECTED_GRAPH_H