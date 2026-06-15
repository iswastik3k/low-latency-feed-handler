#pragma once
#include <cstdint>

namespace parser {

// Aligned tick structure for cache-friendly access
struct alignas(32) Tick {
    uint64_t timestamp_ns;
    uint32_t symbol_id;
    double price;
    uint32_t size;
};

} // namespace parser