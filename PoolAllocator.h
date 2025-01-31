#ifndef POOLALLOCATOR_H
#define POOLALLOCATOR_H

#include "Allocator.h"

class PoolAllocator : public Allocator {
    public:
        PoolAllocator(const size_t size, const size_t chunk_size);

        virtual ~PoolAllocator();

        virtual void* Allocate(const size_t size, const size_t alignment) override;

        virtual void Free(void* ptr) override;

        virtual void PrintState() override;

        virtual void Init() override;

        virtual void Reset() override;


    protected:
        struct Chunk
		{
			Chunk* mem_next;
		};
		Chunk* mem_head;
		size_t mem_chunk_size;
		size_t mem_current_block;
		vector<void*> mem_blocks;
		bool mem_resizeable;

    private:
		Chunk* AllocateBlock();
};

#endif