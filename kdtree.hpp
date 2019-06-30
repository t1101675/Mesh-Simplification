#ifndef KDTREE_H_
#define KDTREE_H_

#include <algorithm>
#include <iostream>
#include <vector>
#include <algorithm>

#include "vec3.hpp"
#include "vertex.h"
#include "utils.hpp"

struct Node {
    int index; //vertex index
    int left; //tree index
    int right;
    Vec3 minBound;
    Vec3 maxBound;
    int dim;
    Node() {
        this->index = 0;
        this->left = 0;
        this->right = 0;
        this->minBound = Vec3();
        this->maxBound = Vec3();
        this->dim = 0;
    }
};

class Kdtree {
private:
    Node* nodes;
    Vertex* vB;
    int offset;
    int vpNum;
public:
    int root;

    Kdtree() {
        offset = 1; //0 for null
        root = 0;
        nodes = new Node[MAX_VERTEX];
        vB = nullptr;
        this->vpNum = -1;
    }

    ~Kdtree() {
        delete[] nodes;
    }

    int buildLayer(int* indices, int l, int r, int dim, double t) {
        if (l >= r) return 0;
        int mid = (l + r) >> 1;
        std::nth_element(indices + l, indices + mid, indices + r, VertexCmp(dim, vB));
        int tIndex = offset;
        ++offset;
        int midIndex = indices[mid];
        nodes[tIndex].index = midIndex;
        nodes[tIndex].dim = dim;
        nodes[tIndex].maxBound = vB[midIndex].p + t;
        nodes[tIndex].minBound = vB[midIndex].p - t;
        nodes[tIndex].left = buildLayer(indices, l, mid, (dim + 1) % 3, t);
        if (nodes[tIndex].left) {
            nodes[tIndex].maxBound = eachMax(nodes[nodes[tIndex].left].maxBound, nodes[tIndex].maxBound);
            nodes[tIndex].minBound = eachMin(nodes[nodes[tIndex].left].minBound, nodes[tIndex].minBound);
        }
        nodes[tIndex].right = buildLayer(indices, mid + 1, r, (dim + 1) % 3, t);
        if (nodes[tIndex].right) {
            nodes[tIndex].maxBound = eachMax(nodes[nodes[tIndex].right].maxBound, nodes[tIndex].maxBound);
            nodes[tIndex].minBound = eachMin(nodes[nodes[tIndex].right].minBound, nodes[tIndex].minBound);
        }
        return tIndex;
    }

    void buildTree(Vertex* vB, int vpNum, double t) {
        this->vB = vB;
        this->vpNum = vpNum;
        int* indices = new int[MAX_VERTEX];
        for (int i = 0; i < vpNum; ++i) {
            indices[i] = i;
        }
        root = buildLayer(indices, 0, this->vpNum, 0, t);
        delete[] indices;
    }

    void query(int node, const Vec3 &pos, std::vector<int> &v_hit, double t) const {
        if (pos.x > nodes[node].maxBound.x || pos.x < nodes[node].minBound.x ||
            pos.y > nodes[node].maxBound.y || pos.y < nodes[node].minBound.y ||
            pos.z > nodes[node].maxBound.z || pos.z < nodes[node].minBound.z)
        {
            return;
        }
        int vIndex = nodes[node].index;

        if ((vB[vIndex].p - pos).squareLength() <= t * t) {
            v_hit.push_back(vIndex);
        }
        
        if (nodes[node].left)
            query(nodes[node].left, pos, v_hit, t);
       
        if (nodes[node].right)
            query(nodes[node].right, pos, v_hit, t);
    }

    void clear() {
        offset = 1;
        root = 0;    
    }
};

#endif //KDTREE