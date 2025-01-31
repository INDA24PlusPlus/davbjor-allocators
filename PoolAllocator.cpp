#include "PoolAllocator.h"

PoolAllocator::PoolAllocator(const size_t size, const size_t chunk_size) : Allocator(size), mem_chunk_size(chunk_size), mem_head(nullptr) {
    assert(chunk_size >= sizeof(Chunk) && "Chunk size must be greater or equal to sizeof(Chunk)");
    assert(size % chunk_size == 0 && "Size must be a multiple of chunk size");

    Init();
};

PoolAllocator::~PoolAllocator() {
    for (size_t i = 0; i < mem_blocks.size(); i++) {
        free(mem_blocks[i]);
    }
    mem_blocks.clear();
    mem_head = nullptr;
    mem_start_ptr = nullptr;
};

void* PoolAllocator::Allocate(size_t size, size_t alignment){
    assert(size == mem_chunk_size && "Size must be equal to chunk size");

    if(mem_head == nullptr)return nullptr;

    Chunk* chunk = mem_head;

    if(chunk->mem_next == nullptr && 
        (size_t)(reinterpret_cast<char*>(chunk) + mem_chunk_size) != 
        (size_t)(reinterpret_cast<char*>(mem_blocks[mem_current_block - 1]) + mem_totalsize)
    ){
        mem_head = reinterpret_cast<Chunk*>(reinterpret_cast<char*>(chunk) + mem_chunk_size);
        mem_head->mem_next = nullptr;
    }
    else mem_head = mem_head->mem_next;

    return chunk;
}

void PoolAllocator::Free(void* ptr){
    Chunk* chunk = reinterpret_cast<Chunk*>(ptr);
    chunk->mem_next = mem_head;
    mem_head = chunk;
}

void PoolAllocator::Reset(){
    for (size_t i = 0; i < mem_blocks.size(); i++) {
        free(mem_blocks[i]);
    }
    mem_blocks.clear();
    mem_head = nullptr;
    mem_start_ptr = nullptr;

    Init();
}

void PoolAllocator::Init(){
    mem_start_ptr = AllocateBlock();
    mem_head = reinterpret_cast<Chunk*>(mem_start_ptr);
    mem_blocks.push_back(mem_start_ptr);
    mem_current_block = 1;
}

void PoolAllocator::PrintState(){
    cout << "===============\n";
    cout << "Memory state:\n";
    cout << "Chunk size: " << mem_chunk_size << "\n";
    cout << "Total size: " << mem_totalsize << "\n";
    cout << "Current block: " << mem_current_block << "\n";
    cout << "Blocks: " << mem_blocks.size() << "\n";
    cout << "Head: " << mem_head << "\n";
    cout << "Memory used percentage: " << (float)mem_current_block / mem_blocks.size() * 100 << "%\n";
    cout << "Memory free percentage: " << (float)(mem_blocks.size() - mem_current_block) / mem_blocks.size() * 100 << "%\n\n";
}

PoolAllocator::Chunk* PoolAllocator::AllocateBlock() {
    void* new_block = malloc(mem_totalsize);

    Chunk* new_chunk = reinterpret_cast<Chunk*>(new_block);
    new_chunk->mem_next = nullptr;

    return new_chunk;
}