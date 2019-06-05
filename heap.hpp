#ifndef HEAP_H_
#define HEAP_H_

#include "pair.hpp"

class Heap {
private:
    Pair* pairs;
public:
    void build(Pair* pairs);
    void add(const Pair& pair);
    void del();
    void remove(const Pair& pair);
    void update(const Pair& pair);
    Pair top() const;
};

#endif