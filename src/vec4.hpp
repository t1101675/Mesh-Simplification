#ifndef VEC4_H_
#define VEC4_H_

#include "vec3.hpp"

class Vec4 {
public:
    double data[4];
    Vec4(double xx = 0, double yy = 0, double zz = 0, double ww = 0) {
        data[0] = xx;
        data[1] = yy;
        data[2] = zz;
        data[3] = ww;
    }
    Vec4(const Vec3& v3, double ww) {
        data[0] = v3.x;
        data[1] = v3.y;
        data[2] = v3.z;
        data[3] = ww;
    }

    double dot(const Vec4& v) {
        return data[0] * v.data[0] + data[1] * v.data[1] + data[2] * v.data[2] + data[3] * v.data[3];
    }
};

#endif