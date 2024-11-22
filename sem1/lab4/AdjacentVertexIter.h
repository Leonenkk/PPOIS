#ifndef ADJACENT_VERTEX_ITER_H
#define ADJACENT_VERTEX_ITER_H

#include <iterator>
#include <vector>

template <typename T>
class AdjacentVertexIter : public std::iterator<std::input_iterator_tag, T> {
private:
    typename std::vector<T>::iterator current;
    typename std::vector<T>::iterator end;

public:
    AdjacentVertexIter(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end)
        : current(start), end(end) {}

    T& operator*() {
        return *current;
    }

    T* operator->() {
        return &(*current);
    }

    AdjacentVertexIter& operator++() {
        if (current != end) {
            ++current;
        }
        return *this;
    }

    AdjacentVertexIter operator++(int) {
        AdjacentVertexIter tmp = *this;
        ++(*this);
        return tmp;
    }

    bool operator==(const AdjacentVertexIter& other) const {
        return current == other.current;
    }

    bool operator!=(const AdjacentVertexIter& other) const {
        return current != other.current;
    }
};

#endif // ADJACENT_VERTEX_ITER_H