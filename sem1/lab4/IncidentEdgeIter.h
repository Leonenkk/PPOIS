#ifndef INCIDENT_EDGE_ITER_H
#define INCIDENT_EDGE_ITER_H

#include <iterator>
#include <list>

template <typename T>
class IncidentEdgeIter : public std::iterator<std::bidirectional_iterator_tag, size_t> {
private:
    typename std::list<size_t>::iterator current;
    typename std::list<size_t>::iterator begin;
    typename std::list<size_t>::iterator end;

public:
    IncidentEdgeIter(typename std::list<size_t>::iterator start,
                     typename std::list<size_t>::iterator begin,
                     typename std::list<size_t>::iterator end)
        : current(start), begin(begin), end(end) {}

    size_t& operator*() {
        return *current;
    }

    size_t* operator->() {
        return &(*current);
    }

    IncidentEdgeIter& operator++() {
        ++current;
        return *this;
    }

    IncidentEdgeIter operator++(int) {
        IncidentEdgeIter temp = *this;
        ++(*this);
        return temp;
    }

    IncidentEdgeIter& operator--() {
        --current;
        return *this;
    }

    IncidentEdgeIter operator--(int) {
        IncidentEdgeIter temp = *this;
        --(*this);
        return temp;
    }

    bool operator==(const IncidentEdgeIter& other) const {
        return current == other.current;
    }

    bool operator!=(const IncidentEdgeIter& other) const {
        return current != other.current;
    }
};

#endif // INCIDENT_EDGE_ITER_H
