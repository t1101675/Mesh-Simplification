#ifndef MAP_H_
#define MAP_H_

#include <memory.h>
#include <iostream>

#include "utils.hpp"
#include "face.hpp"

class Map {
private:
    Face* table; //直接将堆元素作为散列表的元素
    bool* fill; //散列表是否被填充
    bool* lazy;

public:
    Map() {
      table = new Face[2 * MAX_FACE];
      fill = new bool[2 * MAX_FACE];
      lazy = new bool[2 * MAX_FACE];
      memset(fill, 0, MAX_FACE * sizeof(bool));
      memset(lazy, 0, MAX_FACE * sizeof(bool));
    }

    /*散列函数*/
    unsigned int hash(const Face &face) {
        unsigned long long int a1 = face.indices[0] + face.indices[1] + face.indices[2];
        unsigned long long int a2 = face.indices[0] * face.indices[1] + face.indices[1] * face.indices[2] + face.indices[2] * face.indices[0];
        unsigned long long int a3 = face.indices[0] * face.indices[1] * face.indices[2];
        unsigned long long int temp = (a1 * P + a2) * P + a3;
        return (unsigned int)(temp % MAX_FACE);
    }

    /*散列表插入元素*/
    void insert(const Face &face) {
        unsigned int hashCode = hash(face);
        unsigned int step = 0, position = hashCode;
        while (fill[position]) {
            step++;
            position = (hashCode + step * step) % MAX_FACE;
        }
        table[position] = face;
        fill[position] = true;
    }

    /*查询某元素*/
    bool get(const Face &face, Face& realFace) {
        unsigned int hashCode = hash(face);
        unsigned int step = 0, position = hashCode;
        while ((fill[position] && (!(table[position] == face))) || (!fill[position] && lazy[position])) {
            step++;
            position = (hashCode + step * step) % MAX_FACE;
        }
        if (fill[position]) {
            realFace = table[position];
            return true;
        }
        return false;
    }

    bool remove(const Face &face) {
        unsigned int hashCode = hash(face);
        unsigned int step = 0, position = hashCode;
        while ((fill[position] && (!(table[position] == face))) || (!fill[position] && lazy[position])) {
            step++;
            position = (hashCode + step * step) % MAX_FACE;
        }
        if (fill[position]) {
            fill[position] = false;
            lazy[position] = true;
            return true;
        }
        return false;
    }

};



#endif