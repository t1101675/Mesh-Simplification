#ifndef UTILS_H_
#define UTILS_H_

#include "vec3.hpp"

const int MAX_VERTEX = 500000;
const int MAX_PAIR = 5000000;
const int MAX_HEAP_NODE = 5000000;
const int MAX_FACE = 3 * MAX_VERTEX;
const int P = 131313;
const int EVAL_COUNT = 100;
const double INVERSE_LIMIT = -0.9;

inline double maxd(double d1, double d2) { return d1 < d2 ? d2 : d1; }
inline double mind(double d1, double d2) { return d1 < d2 ? d1 : d2; }

inline Vec3 eachMax(const Vec3 &v1, const Vec3 &v2) { return Vec3(maxd(v1.x, v2.x), maxd(v1.y, v2.y), maxd(v1.z, v2.z)); }
inline Vec3 eachMin(const Vec3 &v1, const Vec3 &v2) { return Vec3(mind(v1.x, v2.x), mind(v1.y, v2.y), mind(v1.z, v2.z)); }

#endif 