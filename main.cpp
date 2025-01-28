#include "Test.cpp"
#include "LinearAllocator.cpp"

int main(){
    Allocator* linearAllocator = new LinearAllocator((size_t)8 * 120000);
    linearAllocator->Init();

    Test test;
    Result r;
    int n = 100000;
    r = test.TestAllocate(linearAllocator, false, n);

    cout << "Linear Allocator " << n <<" long long allocations: \n";
    r.Print();

    return 0;
}