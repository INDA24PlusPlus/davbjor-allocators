#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "Utils.h"

class Allocator {
    public:
        Allocator(const size_t size) : mem_totalsize(size), mem_used(0) {};

        virtual ~Allocator() {mem_totalsize = 0; };

        virtual void* Allocate(const size_t size, const size_t alignment) = 0;

        virtual void Free(void* ptr) = 0;

        virtual void PrintState() = 0;

        virtual void Init() = 0;

    protected:
        size_t mem_totalsize;
        size_t mem_used;
};

#endif