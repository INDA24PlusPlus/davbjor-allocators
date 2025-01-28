#include <vector>
#include <unordered_map>
#include <cstddef>
#include <cassert>
#include <random>

using namespace std;

size_t FindPadding(size_t base_address, size_t alignment){
    size_t multipler = (base_address / alignment) + 1;
    size_t aligned_address = multipler * alignment;
    size_t padding = aligned_address - base_address;
    return padding;
}

size_t RandomSize(size_t max){
    return (size_t)rand() % max;
}

size_t RandomSize(size_t min, size_t max){
    return (size_t)rand() % (max - min) + min;
}