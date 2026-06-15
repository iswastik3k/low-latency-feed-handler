#pragma once
#include <chrono>
#include <cstdint>

namespace benchmarks {

using Clock = std::chrono::high_resolution_clock;

inline uint64_t now_ns() {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(
        Clock::now().time_since_epoch()
    ).count();
}

} // namespace benchmarks