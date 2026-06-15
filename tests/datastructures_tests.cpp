#include "datastructures/lockfree_ringbuffer.hpp"
#include "parser/tick.hpp"
#include <cassert>
#include <iostream>

int main() {
    datastructures::LockFreeRingBuffer<int, 8> rb;
    int val;

    assert(rb.push(42));
    assert(rb.pop(val));
    assert(val == 42);

    std::cout << "Phase 04 datastructures test passed." << std::endl;
    return 0;
}