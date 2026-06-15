#include "optimizations/simd_parser.hpp"
#include "parser/tick.hpp"
#include <cassert>
#include <iostream>
#include <cstring>

int main() {
    parser::Tick sample{123456789ULL, 42, 100.25, 10};
    uint8_t buffer[2 * sizeof(parser::Tick)]{};
    std::memcpy(buffer, &sample, sizeof(sample));
    std::memcpy(buffer + sizeof(sample), &sample, sizeof(sample));

    auto ticks = optimizations::parse_simd(buffer, sizeof(buffer));
    assert(ticks.size() == 2);
    assert(ticks[0].symbol_id == 42);
    std::cout << "Phase 05 SIMD test passed." << std::endl;
    return 0;
}