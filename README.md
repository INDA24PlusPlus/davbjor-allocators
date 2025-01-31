# davbjor-allocations
A custom C++ memory allocation library.

## Implementations
### Linear Allocator
Implemented a linear allocator (no deallocations)

### Pool Allocator
Implemented a pool allocator (fixed chunk size)

## Comparisons
A pool allocator is marginally faster than a linear allocator at assigning 8-byte long long's repeatedly. It also has the advantage of possible deallocations.

Yet the Linear Allocator can handle different sized chunks, which the pool allocator can not do.

In summary, the choice of which allocator to use is entirely dependent on your data-structure and the memory usage of your algorithm.