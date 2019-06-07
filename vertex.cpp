#include <assert.h>

#include "vec4.hpp"
#include "mat4.hpp"
#include "pair.hpp"
#include "vertex.h"

Vertex::Vertex(double x, double y, double z): p(x, y, z) {

}

bool Vertex::isNeighbor(int index) const {
    for (int i = 0; i < neighbor.size(); ++i) {
        if (neighbor[i] == index) {
            return true;
        }
    }
    return false;
}

void Vertex::addNeighbor(int index) {
    //assume index is not in neighbor
    neighbor.push_back(index);
}

void Vertex::delNeighbor(int index) {
    for (int i = 0; i < neighbor.size(); ++i) {
        if (neighbor[i] == index) {
            neighbor[i] = neighbor.back();
            neighbor.pop_back();
            return;
        }
    }
    assert(0 == 1);
}

bool Vertex::hasPair(int index, const Pair* pairs) const {
    for (int i = 0; i < this->pairs.size(); ++i) {
        if (((pairs[index].v[0] == pairs[this->pairs[i]].v[0]) && (pairs[index].v[1] == pairs[this->pairs[i]].v[1])) 
         || ((pairs[index].v[0] == pairs[this->pairs[i]].v[1]) && (pairs[index].v[1] == pairs[this->pairs[i]].v[0]))) 
        {
            return true;
        }
    }
    return false;
}

void Vertex::addPair(int index) {
    //assume this pair is not in pairs
    pairs.push_back(index);
}

void Vertex::delPair(int index) {
    for (int i = 0; i < pairs.size(); ++i) {
        if (pairs[i] == index) {
            pairs[i] = pairs.back();
            pairs.pop_back();
            return;
        }
    }
    assert(0 == 1);
}

void Vertex::computeQ(const Vertex* vertices) {
    for (int i = 0; i < neighbor.size(); ++i) {
        for (int j = i + 1; j < neighbor.size(); ++j) {
            if (vertices[neighbor[i]].isNeighbor(neighbor[j])) {
                //form a triangle
                Vec3 norm = (vertices[neighbor[i]].p - p).cross(vertices[neighbor[j]].p - p).normal();
                double w = -(p.dot(norm));
                Vec4 v4(norm, w);
                Q += Mat4(v4);
            }
        }
    }
}