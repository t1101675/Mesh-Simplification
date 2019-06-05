#ifndef MESH_H_
#define MESH_H_

#include <string>
#include <vector>

#include "vertex.h"
#include "face.hpp"
#include "heap.hpp"
#include "pair.hpp"
#include "mat4.hpp"

const int MAX_VERTEX = 100000;
const int MAX_PAIR = 100000;

class Mesh {
private:
    Vertex* vertices;
    Pair* pairs;
    Heap heap;
    int vOffset;
    int pOffset;
    //std::vector<int> freePos;
    bool* valid;
    double rate;

    int faceCount;
    int vertexCount;

    void computeQ();
    void computeValidPairs();
    int addVertex(const Vertex& v);
    void delVertex(int index);
    void addFace(const Face& f);
    void update(const Pair& pair);

public:
    Mesh();
    void load(const std::string& path);
    void save(const std::string& path);
    void setRate(double rate) { this->rate = rate; }
    void simplify();
};


#endif