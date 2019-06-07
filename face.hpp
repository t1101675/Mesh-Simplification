#ifndef FACE_H_
#define FACE_H_

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

    friend bool operator==(const Face& face1, const Face& face2) {
        bool b0 = (face1.indices[0] == face2.indices[0]) && (face1.indices[1] == face2.indices[1]) && (face1.indices[2] == face2.indices[2]);
        bool b1 = (face1.indices[0] == face2.indices[0]) && (face1.indices[1] == face2.indices[2]) && (face1.indices[2] == face2.indices[1]);
        bool b2 = (face1.indices[0] == face2.indices[1]) && (face1.indices[1] == face2.indices[0]) && (face1.indices[2] == face2.indices[2]);
        bool b3 = (face1.indices[0] == face2.indices[1]) && (face1.indices[1] == face2.indices[2]) && (face1.indices[2] == face2.indices[0]);
        bool b4 = (face1.indices[0] == face2.indices[2]) && (face1.indices[1] == face2.indices[0]) && (face1.indices[2] == face2.indices[1]);
        bool b5 = (face1.indices[0] == face2.indices[2]) && (face1.indices[1] == face2.indices[1]) && (face1.indices[2] == face2.indices[0]);
        return b0 || b1 || b2 || b3 || b4 || b5;
    }
};

#endif