#ifndef PAIR_H_
#define PAIR_H_

#include "vertex.h"
#include "vec4.hpp"
#include "mat4.hpp"


class Pair{
private:
    double cost;
    Vec3 optPos;
public:
    int heapIndex;
    int index;
    int v[2];

    Pair() {
        cost = 0.0;
        optPos = Vec3();
        heapIndex = 0;
        index = 0;
        v[0] = v[1] = 0;
    }

    Vec3 optimalPos() const {
        return optPos;
    }

    void updateOptiPos(const Vertex* vertices) {
        optPos = (vertices[v[0]].p + vertices[v[1]].p) / 2; //if no solution, choose the middle
        Mat4 A = vertices[v[0]].Q + vertices[v[1]].Q;
        A.set(3, 0, 0.0);
        A.set(3, 1, 0.0);
        A.set(3, 2, 0.0);
        A.set(3, 3, 1.0);
        Vec4 Y(0.0, 0.0, 0.0, 1.0);
        for (int i = 0; i < 4; ++i) {
            A.set(i, 3, -A.get(i, 3));
        }
	    for (int i = 0; i < 3; ++i) {
	    	int j = 0;
	    	for (j = 0; j < 3; ++j) {
	    		if (std::abs(A.get(i, j)) >= 1e-6) {
	    			break;
                }
            }
	    	if (j == 3) return; //no solution
	    	for (int p = 0; p < 3; ++p) {
                if (p != i) {
                    double d = A.get(p, j) / A.get(i, j);
                    for (int k = 0; k < 4; ++k) {
                        A.set(p, k, A.get(p, k) - A.get(i, k) * d);
                    }
                }
            }
	    }
	    for(int i = 0; i < 3; ++i) {
	    	int count = 0;
	    	for (int j = 0; j < 3; ++j) {
	    		if (std::abs(A.get(i, j)) < 1e-6) count++;
            }
	    	if (count == 3) return; //no solution
	    }
	    double index[3];
	    for (int i = 0; i < 3; ++i) {
	    	for (int j = 0; j < 3; ++j) {
	    		if (std::abs(A.get(i, j)) > 1e-6) {
	    			index[j] = A.get(i, 3) / A.get(i, j);
                }
            }
        }
	    optPos.x = index[0];
	    optPos.y = index[1];
	    optPos.z = index[2];
    }

    void updateCost(const Vertex* vertices) {
        Vec4 y(optPos, 1.0);
        Mat4 A = vertices[v[0]].Q + vertices[v[1]].Q;
        Vec4 Ay = A * y;
        cost = y.dot(Ay);   
    }

    friend bool operator< (const Pair& p1, const Pair& p2) {
        return p1.cost < p2.cost;
    }
};

#endif