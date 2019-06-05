#ifndef HEAP_H_
#define HEAP_H_

#include <assert.h>

#include "pair.hpp"


const int MAX_HEAP_NODE = 1000000;

struct HeapNode {
    int index;
    bool exist;
    HeapNode(): index(0), exist(0) {}
};

class Heap {
private:
    Pair* pairs;
    HeapNode* data; //store pair index. its index is heapIndex, start from 0
    
    int n;
    int pairNum;

    int down(int k) {
        int i = k, j = k;
        while (true) {
          if (((i << 1) + 1 < n) && (pairs[data[(i << 1) + 1].index] < pairs[data[j].index])) {
            j = (i << 1) + 1;
          }
          if (((i << 1) + 2 < n) && (pairs[data[(i << 1) + 2].index] < pairs[data[j].index])) {
            j = (i << 1) + 2;
          }
          if (i == j) {
            return i;
          }
          else {
            HeapNode temp = data[i]; data[i] = data[j]; data[j] = temp;
            assert(pairs[data[i].index].heapIndex == j);
            assert(pairs[data[j].index].heapIndex == i);
            pairs[data[i].index].heapIndex = i;
            pairs[data[j].index].heapIndex = j;
            i = j;
          }
        }
        return i;
    }

    int up(int k) {
        int i = k;
        while (i > 0) {
            int j = (i - 1) >> 1;
            if (pairs[data[i].index] < pairs[data[j].index]) {
                HeapNode temp = data[i]; data[i] = data[j]; data[j] = temp;
                assert(pairs[data[i].index].heapIndex == j);
                assert(pairs[data[j].index].heapIndex == i);
                pairs[data[i].index].heapIndex = i;
                pairs[data[j].index].heapIndex = j;
                i = j;
            }
            else {
                return i;
            }
        }
        return i;
    }

public:
    void build(Pair* pairs, int n) {
        this->pairs = pairs;
        this->n = n;
        this->pairNum = n;
        data = new HeapNode[MAX_HEAP_NODE];
        for (int i = 0; i < n; ++i) {
            data[i].index = i;
            data[i].exist = true;
        }
        for (int i = (n - 2) >> 1; i >= 0; --i) {
            down(i);
        }
    }
    int add(const Pair& pair) {
        data[n].index = pair.index;
        data[n].exist = true;
        ++n;
        return up(n - 1);
    }
    void del() {
        data[0] = data[--n];
        down(0);
    }
    void remove(const Pair& pair) {
        data[pair.heapIndex].exist = false;
    }
    void update(Pair& pair) {
        data[pair.heapIndex].exist = false;
        pair.heapIndex = add(pair);
    }
    int top() {
        while (0 < n && !data[0].exist) {
            del();
        }
        if (0 < n) {
            return 0; 
        }
        return -1;
    }
};

#endif