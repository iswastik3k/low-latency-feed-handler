#pragma once
#include <cstddef>
#include <cstdint>
#include <immintrin.h>

namespace io {

// Aligned buffer for SIMD-friendly packet parsing
struct alignas(64) PacketBuffer {
    uint8_t data[4096];
    std::size_t length;
};

} // namespace io