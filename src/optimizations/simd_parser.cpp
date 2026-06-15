#include "optimizations/simd_parser.hpp"
#include <immintrin.h>
#include <cstring>

namespace optimizations {

std::vector<parser::Tick> parse_simd(const uint8_t* data, std::size_t length) {
    std::vector<parser::Tick> ticks;
    std::size_t offset = 0;

#ifdef __AVX2__
    // Process 2 ticks at a time using AVX
    while (offset + 2 * sizeof(parser::Tick) <= length) {
        __m256i chunk = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(data + offset));

        // Store the 256-bit register into a 32-byte buffer
        alignas(32) uint8_t tmp[32];
        _mm256_store_si256(reinterpret_cast<__m256i*>(tmp), chunk);

        // Reinterpret the buffer as two Tick structs
        auto* ticks_ptr = reinterpret_cast<const parser::Tick*>(tmp);
        ticks.push_back(ticks_ptr[0]);
        ticks.push_back(ticks_ptr[1]);

        offset += 2 * sizeof(parser::Tick);
    }
#endif

    // Scalar fallback for remainder
    while (offset + sizeof(parser::Tick) <= length) {
        parser::Tick tick{};
        std::memcpy(&tick, data + offset, sizeof(parser::Tick));
        ticks.push_back(tick);
        offset += sizeof(parser::Tick);
    }

    return ticks;
}

} // namespace optimizations