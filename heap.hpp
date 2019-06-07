#ifndef HEAP_H_
#define HEAP_H_

#include <assert.h>

#include "pair.hpp"


const int MAX_HEAP_NODE = 2000000;

struct HeapNode {
    int index;
    double cost;
    bool exist;
    friend bool operator< (const HeapNode& n1, const HeapNode& n2) {
        return n1.cost < n2.cost;
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
                //std::cout << i << " " << data[i].exist << " " << pairs[data[i].index].heapIndex << std::endl;
                //std::cout << j << " " << data[j].exist << " " << pairs[data[j].index].heapIndex << std::endl;
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
        data[n].index = pair.index;
        data[n].exist = true;
        pair.heapIndex = n;
        ++n;
        int temp = up(n - 1);
        //if (pair.index == 55032)
        //{
        //    std::cout << pairs[55032].heapIndex << " ssssss heap index " << data[pairs[55032].heapIndex].exist << std::endl;
        //}

        return temp;

    }
    void del() {
        assert(n - 1 < MAX_HEAP_NODE);
        if (data[0].exist) {
            --pairNum;
        }
        //std::cout << "before " << data[0].index << std::endl;
        data[0] = data[--n];
        //std::cout << "after " << data[0].index << std::endl;
        if (data[0].exist) {
            //std::cout << pairs[data[0].index].heapIndex << " " << n - 1 << std::endl;
            assert(pairs[data[0].index].heapIndex == n);
            pairs[data[0].index].heapIndex = 0;
        }
        down(0);
    }
    void remove(const Pair& pair) {
        //if (pair.index == 55032) {
        //    std::cout << "qaaaaaaaaaaa " << data[pair.heapIndex].index << " " << pair.heapIndex << std::endl;
        //}
        assert(data[pair.heapIndex].exist == true);
        data[pair.heapIndex].exist = false;
        --pairNum;
    }
    void update(Pair& pair) {
        data[pair.heapIndex].exist = false;
        add(pair);
        //std::cout << "exist " << data[0].exist << " " << data[0].index << std::endl;
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