#pragma once
#include <cstddef>
#include <cstdint>
#include <functional>

namespace io {

using PacketHandler = std::function<void(const uint8_t*, std::size_t)>;

class NetworkIO {
public:
    virtual ~NetworkIO() = default;
    virtual void run(PacketHandler handler) = 0;
};
} // namespace io