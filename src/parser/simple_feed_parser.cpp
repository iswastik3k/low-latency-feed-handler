#include "parser/simple_feed_parser.hpp"
#include <cstring>

namespace parser {

std::vector<Tick> SimpleFeedParser::parse(const uint8_t* data, std::size_t length) {
    std::vector<Tick> ticks;
    std::size_t offset = 0;
    while (offset + sizeof(Tick) <= length) {
        Tick tick{};
        std::memcpy(&tick, data + offset, sizeof(Tick));
        ticks.push_back(tick);
        offset += sizeof(Tick);
    }
    return ticks;
}

} // namespace parser
