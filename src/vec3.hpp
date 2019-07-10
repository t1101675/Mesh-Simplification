#ifndef VEC3_H_
#define VEC3_H_

#include <math.h>
#include <iostream>

class Vec3 {
public:
    double x, y, z;
    Vec3(double xx = 0, double yy = 0, double zz = 0) : x(xx), y(yy), z(zz) {}
    Vec3(const Vec3 &p) : Vec3(p.x, p.y, p.z) {}

    Vec3 normal() const
    {
        double len = length();
        return len < 1e-8 ? Vec3() : Vec3(x / len, y / len, z / len);
    }

    friend Vec3 operator+(const Vec3 &v1, const Vec3 &v2) { return Vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z); }
    friend Vec3 operator-(const Vec3 &v1, const Vec3 &v2) { return Vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z); }
    friend Vec3 operator*(double a, const Vec3 &v) { return Vec3(v.x * a, v.y * a, v.z * a); }
    friend Vec3 operator*(const Vec3 &v, double a) { return Vec3(v.x * a, v.y * a, v.z * a); }
    friend Vec3 operator*(const Vec3 &v1, const Vec3 &v2) { return Vec3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z); }
    friend Vec3 operator-(const Vec3 &v) { return Vec3(-v.x, -v.y, -v.z); }
    friend Vec3 operator+(const Vec3 &v, double r) { return Vec3(v.x + r, v.y + r, v.z + r); }
    friend Vec3 operator-(const Vec3 &v, double r) { return Vec3(v.x - r, v.y - r, v.z - r); }
    friend Vec3 operator/(const Vec3 &v, double a) { return Vec3(v.x / a, v.y / a, v.z / a); }
    void operator+=(const Vec3 &v) { x += v.x; y += v.y; z += v.z; }

    Vec3 cross(const Vec3 &v) const { return Vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }
    double dot(const Vec3 &v) const { return x * v.x + y * v.y + z * v.z; }
    double length() const { return sqrt(x * x + y * y + z * z); }
    double squareLength() const { return x * x + y * y + z * z; }
    double distance(const Vec3 &p) const { return (Vec3(x - p.x, y - p.y, z - p.z)).length(); }
    double squareDistance(const Vec3 &p) const { return (Vec3(x - p.x, y - p.y, z - p.z)).squareLength(); }
};

#endif //VEC3_H_