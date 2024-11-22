#ifndef EDGE_ITER_H
#define EDGE_ITER_H

#include <iterator>
#include <list>
#include <vector>

template <typename T>
class EdgeIter {
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = size_t*;
    using reference = size_t&;

    EdgeIter(typename std::list<size_t>::iterator iter) : iter(iter) {}

    reference operator*() const {
        return *iter;
    }

    pointer operator->() const {
        return &(*iter);
    }

    EdgeIter& operator++() {
        ++iter;
        return *this;
    }

    EdgeIter operator++(int) {
        EdgeIter temp = *this;
        ++(*this);
        return temp;
    }

    bool operator==(const EdgeIter& other) const {
        return iter == other.iter;
    }

    bool operator!=(const EdgeIter& other) const {
        return iter != other.iter;
    }

private:
    typename std::list<size_t>::iterator iter;
};

#endif // EDGE_ITER_H