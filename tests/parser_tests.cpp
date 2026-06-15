#include "parser/simple_feed_parser.hpp"
#include <cassert>
#include <iostream>
#include <cstring>

int main() {
    parser::SimpleFeedParser parser;
    uint8_t buffer[sizeof(parser::Tick)]{};
    parser::Tick sample{123456789ULL, 42, 100.25, 10};
    std::memcpy(buffer, &sample, sizeof(sample));

    auto ticks = parser.parse(buffer, sizeof(buffer));
    assert(ticks.size() == 1);
    assert(ticks[0].symbol_id == 42);
    std::cout << "Phase 03 parser test passed." << std::endl;
    return 0;
}