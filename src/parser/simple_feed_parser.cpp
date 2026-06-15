#include "parser/protocol_parser.hpp"
#include <cstring>
#include <iostream>

namespace parser {

// Example binary format: [timestamp_ns][symbol_id][price][size]
class SimpleFeedParser : public ProtocolParser {
public:
    std::vector<Tick> parse(const uint8_t* data, std::size_t length) override {
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
};

} // namespace parser