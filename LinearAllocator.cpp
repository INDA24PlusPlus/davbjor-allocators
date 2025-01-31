#include "LinearAllocator.h"

LinearAllocator::LinearAllocator(const size_t mem_size) : Allocator(mem_size) {
    Init();
};

void LinearAllocator::Init(){
    cout << "Called INIT();\n";
    if(mem_start_ptr != nullptr){
        free(mem_start_ptr);
        mem_start_ptr = nullptr;
    }

    assert(mem_totalsize != 0 && "Can't Allocate 0 Total Size Memory");

    mem_start_ptr = malloc(mem_totalsize);
    mem_offset = 0;
}

LinearAllocator::~LinearAllocator() {
    if(mem_start_ptr){
        free(mem_start_ptr);
        mem_start_ptr = nullptr;
    }
}

void* LinearAllocator::Allocate(const size_t size, const size_t alignment){
    size_t padding = 0;
    size_t padded_address = 0;
    size_t current_address = (size_t)mem_start_ptr + mem_offset;

    // Check if alignment is a multiple of offset
    // alignment & (alignment - 1) != 0
    if(alignment != 0 && mem_offset % alignment != 0){
        // Find the next aligned memory address
        padding = FindPadding(current_address, alignment);
    }

    // Cant find space to allocate
    if(mem_offset + padding + size > mem_totalsize){
        return nullptr;
    }

    size_t next_address = current_address + padding;
    mem_offset += padding + size;

    bool debug = false;
    if(debug){
        cout << "---------------\n";
        cout << "Allocating " << size << " bytes with alignment " << alignment << "\n";
        cout << "Current address: " << (void*)current_address << " (" << current_address << ")\n";
        cout << "Next aligned address: " << (void*)next_address << " (" << next_address << ")\n";
        cout << "Offset after allocation: " << mem_offset << "\n";
        cout << "Padding added: " << padding << "\n\n";
    }

    mem_used = mem_offset;

    return (void*)next_address;
}

// Can't free with linear allocator
void LinearAllocator::Free(void* ptr){
    assert(false && "Can't free linear-allocator, use Reset()");
}

void LinearAllocator::Reset(){
    mem_used = 0;
    mem_offset = 0;
}

void LinearAllocator::PrintState(){
    cout << "===================\n";
    cout << "Linear Allocator: " << mem_totalsize << " bytes\n";
    cout << "Memory used: " << mem_used << " bytes\n";
    cout << "Memory offset: " << mem_offset << " bytes\n";
    cout << "Memory start: " << mem_start_ptr << "\n";
    cout << "Memory current: " << (void*)((size_t)mem_start_ptr + mem_offset) << " (" << (size_t)mem_start_ptr + mem_offset << ")\n";
    cout << "Memory end: " << (void*)((size_t)mem_start_ptr + mem_totalsize) << " (" << (size_t)mem_start_ptr + mem_totalsize << ")\n";
    cout << "Memory used: " << mem_used << " bytes\n";
    cout << "Memory free: " << mem_totalsize - mem_used << " bytes\n";
    cout << "Memory used percentage: " << (float)mem_used / mem_totalsize * 100 << "%\n";
    cout << "Memory free percentage: " << (float)(mem_totalsize - mem_used) / mem_totalsize * 100 << "%\n";
    cout << "\n";
}