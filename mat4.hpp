#ifndef MAT4_H_
#define MAT4_H_

class Mat4 {
private:
    double data[16];
public:
    Mat4();
    void operator+=(const Mat4& mat) {
        for (int i = 0; i < 16; ++i) {
            data[i] += mat.data[i];
        }
    }

};

#endif