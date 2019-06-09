#ifndef MESH_H_
#define MESH_H_

#include <string>
#include <vector>

#include "utils.hpp"
#include "vertex.h"
#include "face.hpp"
#include "heap.hpp"
#include "pair.hpp"
#include "mat4.hpp"
#include "map.hpp"

class Mesh {
private:
    Vertex* vertices;
    Vec3* originVertices;
    Face* originFace;
    Pair* pairs;
    Map faceMap;
    Heap heap;
    int fOffset;
    int vOffset;
    int pOffset;
    int faceCount;
    int vertexCount;
    double t; //see the paper
    double rate;
    //std::vector<int> freePos;
    bool* valid;
    bool* inPair;
    bool* inFace;


    void computeQ();
    void computeValidPairs();
    int addVertex(const Vec3& p);
    int addPair(int v1, int v2);
    void delVertex(int index);
    void addFace(const Face& f);
    void update(const Pair& pair);

public:
    Mesh();
    ~Mesh();
    void load(const std::string& path);
    void save(const std::string& path);
    double eval();
    void setRate(double rate) { this->rate = rate; }
    void simplify();
};


#endif