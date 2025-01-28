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

/*Result Test::TestAllocate(Allocator* allocator){
    Result r;
    r.start_time = chrono::high_resolution_clock::now();
    //ptr = RandomSize(512);


    void* ptr1 = allocator->Allocate(sizeof(long double)   , alignof(long double));

    void* ptr  = allocator->Allocate(sizeof(long long)     , alignof(long long));

    allocator->PrintState();

    cout << "ptr1" << ptr << " ( "<< (size_t)ptr <<")" << "\n";

    if (reinterpret_cast<uintptr_t>(ptr) % alignof(long long) != 0) {
        cerr << "Error: Allocated memory is NOT properly aligned!" << endl;
    }else {
        cout << "Allocated memory is properly aligned!" << endl;
    }

    vector<unsigned char> bytes;

    if (ptr) {

        // Retrieve value using the original ptr
        long long* longLongPtr = static_cast<long long*>(ptr);
        *longLongPtr = 511LL;  // Store value
        
        long long retrievedValue = *reinterpret_cast<long long*>(ptr);
        cout << "Retrieved value: " << retrievedValue << endl;

    } else {
        cerr << "Allocation failed!" << endl;
    }


    void* ptr2 = allocator->Allocate(sizeof(int)           , alignof(int));
    void* ptr3 = allocator->Allocate(sizeof(size_t)        , alignof(size_t));

    

    allocator->PrintState();

    return r;
}*/

Result Test::TestAllocate(Allocator* allocator, bool debug = false, int n = 1000){
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
        long long* longLongPtr = static_cast<long long*>(ptr);
        *longLongPtr = random_values[i];

        addresses.push_back(ptr);
    }

    r.end_time = chrono::high_resolution_clock::now();

    if(debug){
        for(int i = 0; i < n; i++){
            cout << random_values[i] << " vs " << *reinterpret_cast<long long*>(addresses[i]) << "\n";
        }
    }
    
    allocator->PrintState();

    return r;
}