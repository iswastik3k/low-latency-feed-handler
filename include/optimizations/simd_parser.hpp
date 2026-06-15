#pragma once
#include <cstddef>
#include <cstdint>
#include <vector>
#include "parser/tick.hpp"

namespace optimizations {

// Parse multiple ticks at once using SIMD intrinsics
std::vector<parser::Tick> parse_simd(const uint8_t* data, std::size_t length);

} // namespace optimizations