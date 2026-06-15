#include "optimizations/simd_parser.hpp"
#include <immintrin.h>
#include <cstring>

namespace optimizations {

std::vector<parser::Tick> parse_simd(const uint8_t* data, std::size_t length) {
    std::vector<parser::Tick> ticks;
    std::size_t offset = 0;

    // Example: process 2 ticks at a time using AVX
    while (offset + 2 * sizeof(parser::Tick) <= length) {
        __m256i chunk = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(data + offset));

        alignas(32) parser::Tick tmp[2];
        std::memcpy(tmp, &chunk, 2 * sizeof(parser::Tick));

        ticks.push_back(tmp[0]);
        ticks.push_back(tmp[1]);

        offset += 2 * sizeof(parser::Tick);
    }

    // Handle remainder
    while (offset + sizeof(parser::Tick) <= length) {
        parser::Tick tick{};
        std::memcpy(&tick, data + offset, sizeof(parser::Tick));
        ticks.push_back(tick);
        offset += sizeof(parser::Tick);
    }

    return ticks;
}

} // namespace optimizations