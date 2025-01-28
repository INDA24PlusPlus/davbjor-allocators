#include "Test.h"

constexpr size_t max_alignment = alignof(max_align_t);

Result Test::RandomAllocate(Allocator* allocator){
    /*vector<size_t> random_sizes;
    random_sizes.reserve(1000);

    for(size_t i = 0; i < random_sizes.capacity(); i++){
        random_sizes.push_back(RandomSize(1, 500));
    }

    unordered_map<void*, vector<unsigned char>> addresses;
    addresses.reserve(1000);

    for(size_t i = 0; i < random_sizes.size(); i++){
        void* address = allocator->Allocate(i, max_alignment);
        // Fill random bytes
    }*/
   Result r;
   return r;
}

Result Test::TestRandomAllocations(Allocator* allocator, bool debug = false, int n = 1000){
    Result r;

    unordered_map<void*,vector<unsigned char>> bytes;
    vector<void*> addresses;

    r.start_time = chrono::high_resolution_clock::now();
    
    for(int i = 0; i < n; i++){
        size_t size = RandomSize(1,512);
        void* ptr = allocator->Allocate(size, max_alignment);

        if(ptr == nullptr)break;

        vector<unsigned char> v;
        for (unsigned int i = 0; i < sizeof(long long); ++i){
            // Change Random Bytes To RandomSize(65,105) for characters for debugging
            unsigned char byte = (unsigned char)(RandomSize(0,255));
            v.push_back(byte);
            *(reinterpret_cast<char*>(ptr) + i) = byte;
        }
        bytes[ptr] = v;

        addresses.push_back(ptr);
    }

    r.end_time = chrono::high_resolution_clock::now();
    r.allocations = addresses.size();

    if(debug){
        for(int i = 0; i < addresses.size(); i++){
            for (unsigned int i = 0; i < sizeof(long long); ++i){
                cout << bytes[addresses[i]][i] << " VS " << *(reinterpret_cast<unsigned char*>(addresses[i]) + i) << "\n";
            }
        }
    }

    allocator->PrintState();

    return r;
}

Result Test::TestAllocations(Allocator* allocator, bool debug = false, int n = 1000){
    Result r;
    //ptr = RandomSize(512);

    vector<long long> random_values;
    vector<void*> addresses;

    for(int i = 0; i < n; i++){
        random_values.push_back(RandomSize(1, 1000000));
    }

    r.start_time = chrono::high_resolution_clock::now();

    for(int i = 0; i < n; i++){
        void* ptr = allocator->Allocate(sizeof(long long), alignof(long long));
        if(ptr == nullptr)break;

        long long* longLongPtr = static_cast<long long*>(ptr);
        *longLongPtr = random_values[i];

        addresses.push_back(ptr);
    }

    r.end_time = chrono::high_resolution_clock::now();
    r.allocations = addresses.size();

    if(debug){
        for(int i = 0; i < addresses.size(); i++){
            cout << random_values[i] << " vs " << *reinterpret_cast<long long*>(addresses[i]) << "\n";
        }
    }
    
    allocator->PrintState();

    return r;
}