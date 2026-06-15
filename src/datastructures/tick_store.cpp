#include "datastructures/lockfree_ringbuffer.hpp"
#include "parser/tick.hpp"
#include <iostream>

namespace datastructures {

class TickStore {
    LockFreeRingBuffer<parser::Tick, 1024> ring;

public:
    bool add(const parser::Tick& tick) {
        return ring.push(tick);
    }

    bool get(parser::Tick& tick) {
        return ring.pop(tick);
    }
};

} // namespace datastructures