#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "mesh.h"


int main(int argc, char** argv) {
    if (argc != 4) {
        std::cout << "Error" << std::endl;
        return 1;
    }
    srand(time(0));
    Mesh mesh;
    mesh.load(argv[1]);
    std::cout << "[info] Load end" << std::endl;
    mesh.setRate(atof(argv[3]));
    std::cout << "[info] Set rate end" << std::endl;
    mesh.simplify();
    std::cout << "[info] Simplify end" << std::endl;
    mesh.save(argv[2]);
    std::cout << "[info] Saved to " << argv[2] << std::endl;
    return 0;
}