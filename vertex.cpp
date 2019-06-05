#include "vec4.hpp"
#include "mat4.hpp"
#include "vertex.h"

Vertex::Vertex(double x = 0, double y = 0, double z = 0): p(x, y, z) {

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
    if (!isNeighbor(index)) {
        neighbor.push_back(index);
    }
}

void Vertex::delNeighbor(int index) {
    for (int i = 0; i < neighbor.size(); ++i) {
        if (neighbor[i] == index) {
            neighbor[i] = neighbor.back();
            neighbor.pop_back();
            return;
        }
    }
}

bool Vertex::hasPair(int index, const Pair* pairs) const {
    for (int i = 0; i < neighbor.size(); ++i) {
        if ((pairs[index].v[0] == pairs[neighbor[i]].v[0]) 
         && (pairs[index].v[1] == pairs[neighbor[i]].v[1])) 
        {
            return true;
        }
    }
}

void Vertex::addPair(int index) {
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
}

void Vertex::computeQ(const Vertex* vertices) {
    for (int i = 0; i < neighbor.size(); ++i) {
        for (int j = i + 1; j < neighbor.size(); ++i) {
            if (vertices[neighbor[i]].isNeighbor(neighbor[j])) {
                Vec3 norm = (vertices[neighbor[i]].p - p).cross(vertices[neighbor[j]].p - p).normal();
                double w = -(p.dot(norm));
                Vec4 v4(norm, w);
                Q += Mat4(v4);
            }
        }
    }
}