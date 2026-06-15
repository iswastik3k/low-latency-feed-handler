#pragma once
#include "parser/protocol_parser.hpp"

namespace parser {

// Example binary format: [timestamp_ns][symbol_id][price][size]
class SimpleFeedParser : public ProtocolParser {
public:
    std::vector<Tick> parse(const uint8_t* data, std::size_t length) override;
};

} // namespace parser