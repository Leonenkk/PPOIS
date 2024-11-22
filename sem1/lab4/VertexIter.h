#ifndef VERTEX_ITER_H
#define VERTEX_ITER_H

#include <iterator>

template <typename T>
class VertexIter : public std::iterator<std::input_iterator_tag, T> {
private:
    typename std::vector<T>::iterator current;

public:
    VertexIter(typename std::vector<T>::iterator start)
        : current(start) {}

    T& operator*() {
        return *current;
    }

    T* operator->() {
        return &(*current);
    }

    VertexIter& operator++() {
        ++current;
        return *this;
    }

    VertexIter operator++(int) {
        VertexIter tmp = *this;
        ++(*this);
        return tmp;
    }

    bool operator==(const VertexIter& other) const {
        return current == other.current;
    }

    bool operator!=(const VertexIter& other) const {
        return current != other.current;
    }
};

#endif // VERTEX_ITER_H
