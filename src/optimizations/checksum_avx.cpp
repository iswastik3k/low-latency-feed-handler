#include <immintrin.h>
#include <cstddef>
#include <cstdint>

namespace optimizations {

// Example: compute checksum using AVX2
uint32_t checksum_avx(const uint8_t* data, std::size_t length) {
    __m256i sum = _mm256_setzero_si256();
    std::size_t i = 0;

    for (; i + 32 <= length; i += 32) {
        __m256i chunk = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(data + i));
        sum = _mm256_add_epi8(sum, chunk);
    }

    alignas(32) uint8_t tmp[32];
    _mm256_store_si256(reinterpret_cast<__m256i*>(tmp), sum);

    uint32_t total = 0;
    for (int j = 0; j < 32; ++j) total += tmp[j];

    // Handle remainder
    for (; i < length; ++i) total += data[i];

    return total;
}

} // namespace optimizations