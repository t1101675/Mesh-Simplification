#include <iostream>

#include "mesh.h"


int main(int argc, char** argv) {
    if (argc != 4) {
        std::cout << "Error" << std::endl;
        return 1;
    }
    Mesh mesh;
    mesh.load(argv[1]);
    mesh.setRate(atof(argv[3]));
    mesh.simplify();
    mesh.save(argv[2]);
    return 0;
}