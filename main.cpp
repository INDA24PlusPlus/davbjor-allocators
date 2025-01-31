#include "Test.cpp"
#include "LinearAllocator.cpp"
#include "FreeListAllocator.cpp"
#include "PoolAllocator.cpp"

int main(){
    /* ------------ Linear Allocator, Repeated long long insertions ----------------  */
    LinearAllocator* linearAllocator = new LinearAllocator((size_t)(8 * 120000));

    Test test;
    Result r;
    int n = 1000000;

    r = test.TestAllocations(linearAllocator, false, n);
    cout << "Linear Allocator - long long (8byte) allocations: \n";
    r.Print();


    /* ------------ Pool Allocator, Repeated long long insertions ----------------  */
    PoolAllocator* poolAllocator = new PoolAllocator((size_t)(sizeof(long long) * 120000), sizeof(long long));

    Test test2;
    Result r2;
    int n2 = 1000000;

    r2 = test2.TestAllocations(poolAllocator, false, n2);
    cout << "Pool Allocator - long long (8byte) allocations: \n";
    r2.Print();


    /* ------------ Linear Allocator, Random byte-size insertions ----------------  */
    linearAllocator->Reset();

    r = test.TestRandomAllocations(linearAllocator, false, n);
    cout << "Linear Allocator - (1-512 byte) allocations: \n";
    r.Print();

    return 0;
}