#ifndef TEST_H
#define TEST_H

#include "Allocator.h"
#include <chrono>
#include <iostream>

struct Result {
    size_t allocations = 0;
    chrono::time_point<std::chrono::high_resolution_clock> start_time;
    chrono::time_point<std::chrono::high_resolution_clock> end_time;

    void Print(){
        cout << "Allocations: " << allocations << "\n";
        cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count() << "ms\n\n";
    }
};

class Test {
    public:
        Test() {};

        Result RandomAllocate(Allocator* allocator);

        Result TestRandomAllocations(Allocator* allocator, bool debug, int n);

        Result TestAllocations(Allocator* allocator, bool debug, int n);

};

#endif