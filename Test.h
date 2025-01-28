#ifndef TEST_H
#define TEST_H

#include "Allocator.h"
#include <chrono>
#include <iostream>

struct Result {
    chrono::time_point<std::chrono::high_resolution_clock> start_time;
    chrono::time_point<std::chrono::high_resolution_clock> end_time;

    void Print(){
        cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count() << "ms\n";
    }
};

class Test {
    public:
        Test() {};

        Result RandomAllocate(Allocator* allocator);

        Result TestAllocate(Allocator* allocator, bool debug, int n);

};

#endif