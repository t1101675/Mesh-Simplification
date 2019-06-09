#ifndef FACE_H_
#define FACE_H_

#include "vec3.hpp"
#include "vertex.h"


class Face {
private:
public:
    int indices[3];
    Face() {
        indices[0] = indices[1] = indices[2] = 0;
    }

    Face(int v0, int v1, int v2) {
        indices[0] = v0;
        indices[1] = v1;
        indices[2] = v2;
    }

    Face(const Face& face) {
        indices[0] = face.indices[0];
        indices[1] = face.indices[1];
        indices[2] = face.indices[2];
    }

    Face(const int indices[]) {
        this->indices[0] = indices[0];
        this->indices[1] = indices[1];
        this->indices[2] = indices[2];
    }

    Face &operator=(const Face& face) {
        if (this == &face)
            return *this;
        indices[0] = face.indices[0];
        indices[1] = face.indices[1];
        indices[2] = face.indices[2];
        return *this;
    }

    Vec3 norm(const Vertex* vertices) const {
        Vec3 v0 = vertices[indices[0]].p;
        Vec3 v1 = vertices[indices[1]].p;
        Vec3 v2 = vertices[indices[2]].p;

        return (v1 - v0).cross(v2 - v0).normal();
    }

    friend bool operator==(const Face& face1, const Face& face2) {
        bool b0 = (face1.indices[0] == face2.indices[0]) && (face1.indices[1] == face2.indices[1]) && (face1.indices[2] == face2.indices[2]);
        bool b1 = (face1.indices[0] == face2.indices[0]) && (face1.indices[1] == face2.indices[2]) && (face1.indices[2] == face2.indices[1]);
        bool b2 = (face1.indices[0] == face2.indices[1]) && (face1.indices[1] == face2.indices[0]) && (face1.indices[2] == face2.indices[2]);
        bool b3 = (face1.indices[0] == face2.indices[1]) && (face1.indices[1] == face2.indices[2]) && (face1.indices[2] == face2.indices[0]);
        bool b4 = (face1.indices[0] == face2.indices[2]) && (face1.indices[1] == face2.indices[0]) && (face1.indices[2] == face2.indices[1]);
        bool b5 = (face1.indices[0] == face2.indices[2]) && (face1.indices[1] == face2.indices[1]) && (face1.indices[2] == face2.indices[0]);
        return b0 || b1 || b2 || b3 || b4 || b5;
    }

    bool inFace(const Vec3 & p, const Vertex* vertices) const {
        //using areas of trangles
        Vec3 v0 = vertices[indices[0]].p;
        Vec3 v1 = vertices[indices[1]].p;
        Vec3 v2 = vertices[indices[2]].p;

        double A0 = (v1 - v0).cross(v2 - v0).length();
        double S0 = (v1 - p).cross(v2 - p).length();
        double S1 = (v2 - p).cross(v0 - p).length();
        double S2 = (v0 - p).cross(v1 - p).length();
        if (S0 + S1 + S2 > A0) {
            return false;
        }
        else {
            return true;
        }
    }

    double distance(const Vec3& p, const Vertex* vertices) const {
        Vec3 n = norm(vertices);
        double dist_p2f = n.dot(vertices[indices[0]].p - p);
        Vec3 p_on_f = p + dist_p2f * n;
        if (inFace(p_on_f, vertices)) {
            return std::abs(dist_p2f);
        }
        else {
            double d = 10000;
            for (int i = 0; i < 3; ++i) {
                double new_d = vertices[indices[i]].p.distance(p);
                if (new_d < d) {
                    d = new_d;
                }
            }
            return d;
        }
    }
};

#endif