#pragma once
#include <atomic>
#include <cstddef>
#include <stdexcept>

namespace datastructures {

template<typename T, std::size_t Capacity>
class LockFreeRingBuffer {
    static_assert((Capacity & (Capacity - 1)) == 0, "Capacity must be power of 2");

    T buffer[Capacity];
    std::atomic<std::size_t> head{0};
    std::atomic<std::size_t> tail{0};

public:
    bool push(const T& item) {
        auto h = head.load(std::memory_order_relaxed);
        auto t = tail.load(std::memory_order_acquire);
        if (((h + 1) & (Capacity - 1)) == (t & (Capacity - 1))) {
            return false; // full
        }
        buffer[h & (Capacity - 1)] = item;
        head.store(h + 1, std::memory_order_release);
        return true;
    }

    bool pop(T& item) {
        auto t = tail.load(std::memory_order_relaxed);
        auto h = head.load(std::memory_order_acquire);
        if (t == h) {
            return false; // empty
        }
        item = buffer[t & (Capacity - 1)];
        tail.store(t + 1, std::memory_order_release);
        return true;
    }
};

} // namespace datastructures