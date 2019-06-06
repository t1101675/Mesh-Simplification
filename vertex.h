#ifndef VERTEX_H_
#define VERTEX_H_

#include <set>
#include <vector>
#include "mat4.hpp"
#include "vec3.hpp"

class Pair;

class Vertex {
private:

public:
    Vec3 p;
    Mat4 Q;

    std::vector<int> neighbor;
    std::vector<int> pairs; //pair index

    Vertex(double x = 0, double y = 0, double z = 0);
    bool isNeighbor(int index) const;
    void addNeighbor(int index);
    void delNeighbor(int index);
    void computeQ(const Vertex* vertices);
    void setPos(const Vec3& pos) { p = pos; }
    bool hasPair(int index, const Pair* pairs) const;
    void addPair(int index);
    void delPair(int index);
};


#endif