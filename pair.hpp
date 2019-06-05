#ifndef PAIR_H_
#define PAIR_H_

#include "vertex.h"


class Pair{
private:
    double cost;
    Vec3 optPos;
public:
    int heapIndex;
    int index;
    int v[2];
    Vec3 optimalPos() const;
    void updateCost(const Vertex* vertices);
};

#endif