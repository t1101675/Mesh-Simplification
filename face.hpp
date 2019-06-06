#ifndef FACE_H_
#define FACe_H_

class Face {
private:
public:
    int indices[3];
    Face(const int indices[]) {
        this->indices[0] = indices[0];
        this->indices[1] = indices[1];
        this->indices[2] = indices[2];
    }
};

#endif