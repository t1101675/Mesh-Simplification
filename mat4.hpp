#ifndef MAT4_H_
#define MAT4_H_

#include <memory.h>

#include "vec4.hpp"

class Mat4 {
private:
    double data[16];
public:
    Mat4() {
        for (int i = 0; i < 16; ++i) data[i] = 0.0;
    }
    Mat4& operator=(const Mat4& m) {
        if (this == &m) return *this;
        for (int i = 0; i < 16; ++i) data[i] = m.data[i];
        return *this;
    }

    Mat4(const Vec4& v4) { 
        set(v4); 
    }
    
    friend Mat4 operator+(const Mat4& m1, const Mat4& m2) {
        Mat4 m;
        for (int i = 0; i < 16; ++i) {
            m.data[i] = m1.data[i] + m2.data[i];
        }
        return m;
    }

    Vec4 operator*(const Vec4& v) {
        Vec4 re = Vec4();
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                re.data[i] += data[i * 4 + j] * v.data[j];
            }
        }
        return re;
    }


    void operator+=(const Mat4& mat) {
        for (int i = 0; i < 16; ++i) {
            data[i] += mat.data[i];
        }
    }

    void set(const Vec4& v4) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                data[4 * i + j] = v4.data[i] * v4.data[j];
            }
        }
    }

    void set(int i, int j, double x) {
        data[i * 4 + j] = x;
    }

    double get(int i, int j) const {
        return data[i * 4 + j];
    }
};

#endif