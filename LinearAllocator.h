#ifndef LINEARALLOCATOR_H
#define LINEARALLOCATOR_H

#include "Allocator.h"

class LinearAllocator : public Allocator {
    public:
        LinearAllocator(const size_t size);

        virtual ~LinearAllocator();

        virtual void* Allocate(const size_t size, const size_t alignment) override;

        virtual void Free(void* ptr) override;

        virtual void PrintState() override;

        virtual void Init() override;

        virtual void Reset();


    protected:
        void* mem_start_ptr = nullptr;
        size_t mem_offset;

    private:
        LinearAllocator(LinearAllocator &linearAllocator);
};

#endif