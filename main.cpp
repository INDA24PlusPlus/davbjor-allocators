#include "Test.cpp"
#include "LinearAllocator.cpp"

int main(){
    LinearAllocator* linearAllocator = new LinearAllocator((size_t)(8 * 120000));
    linearAllocator->Init();

    Test test;
    Result r;
    int n = 1000000;

    r = test.TestAllocations(linearAllocator, false, n);
    cout << "Linear Allocator - long long (8byte) allocations: \n";
    r.Print();

    linearAllocator->Reset();

    r = test.TestRandomAllocations(linearAllocator, false, n);
    cout << "Linear Allocator - (1-512 byte) allocations: \n";
    r.Print();

    return 0;
}