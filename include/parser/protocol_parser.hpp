#pragma once
#include <cstddef>
#include <cstdint>
#include <vector>
#include "parser/tick.hpp"

namespace parser {

class ProtocolParser {
public:
    virtual ~ProtocolParser() = default;
    virtual std::vector<Tick> parse(const uint8_t* data, std::size_t length) = 0;
};

} // namespace parser