#ifndef HEAP_H_
#define HEAP_H_

#include <assert.h>

#include "utils.hpp"
#include "pair.hpp"

struct HeapNode {
    int index;
    double cost;
    double cost1;
    bool exist;
    friend bool operator< (const HeapNode& n1, const HeapNode& n2) {
        return (n1.cost < n2.cost) || ((std::abs(n1.cost - n2.cost) < 1e-5) && (n1.cost1 < n2.cost1));
    }
    HeapNode(): index(0), exist(0) {}
};

class Heap {
private:
    Pair* pairs;
    
    int n;
    int pairNum;

    int down(int k) {
        int i = k, j = k;
        while (true) {
            if (((i << 1) + 1 < n) && (data[(i << 1) + 1] < data[j])) {
                j = (i << 1) + 1;
            }
            if (((i << 1) + 2 < n) && (data[(i << 1) + 2] < data[j])) {
                j = (i << 1) + 2;
            }
            if (i == j) {
                return i;
            }
            else {
                HeapNode temp = data[i]; data[i] = data[j]; data[j] = temp;
                if (data[i].exist) {
                    assert(pairs[data[i].index].heapIndex == j);
                    pairs[data[i].index].heapIndex = i;
                }
                if (data[j].exist) {
                    if (pairs[data[j].index].heapIndex != i) {
                        std::cout << i << " " << pairs[data[j].index].heapIndex << std::endl;
                        std::cout << data[j].exist << std::endl;
                    }
                    assert(pairs[data[j].index].heapIndex == i);
                    pairs[data[j].index].heapIndex = j;
                }
              i = j;
            }
        }
        return i;
    }

    int up(int k) {
        int i = k;
        while (i > 0) {
            int j = (i - 1) >> 1;
            if (data[i] < data[j]) {
                HeapNode temp = data[i]; data[i] = data[j]; data[j] = temp;
                if (data[i].exist) {
                    assert(pairs[data[i].index].heapIndex == j);
                    pairs[data[i].index].heapIndex = i;
                }
                if (data[j].exist) {
                    assert(pairs[data[j].index].heapIndex == i);
                    pairs[data[j].index].heapIndex = j;
                }
                i = j;
            }
            else {
                return i;
            }
        }
        return i;
    }

public:
    HeapNode* data; //store pair index. its index is heapIndex, start from 0
    Heap() {
        this->pairs = nullptr;
        this->n = 0;
        this->pairNum = 0;
        data = new HeapNode[MAX_HEAP_NODE];
    }
    ~Heap() {
        delete[] data;
    }
    void build(Pair* pairs, int n) {
        this->pairs = pairs;
        this->n = n;
        this->pairNum = n;
        for (int i = 0; i < n; ++i) {
            data[i].cost = pairs[i].cost;
            data[i].cost1 = pairs[i].cost1;
            data[i].index = i;
            data[i].exist = true;
        }
        for (int i = 0; i < n; ++i) {
            pairs[data[i].index].heapIndex = i;
        }
        for (int i = (n - 2) >> 1; i >= 0; --i) {
            down(i);
        }
    }
    int add(Pair& pair) {
        assert(0 < n);
        assert(n < MAX_HEAP_NODE);
        data[n].cost = pair.cost;
        data[n].cost1 = pair.cost1;
        data[n].index = pair.index;
        data[n].exist = true;
        pair.heapIndex = n;
        ++n;
        int temp = up(n - 1);

        return temp;

    }
    void del() {
        assert(n - 1 < MAX_HEAP_NODE);
        if (data[0].exist) {
            --pairNum;
        }
        data[0] = data[--n];
        if (data[0].exist) {
            assert(pairs[data[0].index].heapIndex == n);
            pairs[data[0].index].heapIndex = 0;
        }
        down(0);
    }
    void remove(const Pair& pair) {
        assert(data[pair.heapIndex].exist == true);
        data[pair.heapIndex].exist = false;
        --pairNum;
    }
    void update(Pair& pair) {
        data[pair.heapIndex].exist = false;
        add(pair);
    }
    int top() {
        while (0 < n && !data[0].exist) {
            del();
        }
        if (0 < n) {
            return data[0].index; 
        }
        return -1;
    }
};

#endif