#include "io/network_io.hpp"
#include <sys/epoll.h>
#include <unistd.h>
#include <vector>
#include <stdexcept>
#include <iostream>

namespace io {

class EpollIO : public NetworkIO {
    int epoll_fd;
    int sock_fd; // placeholder, will be bound to multicast/UDP later

public:
    EpollIO(int socket_fd) : sock_fd(socket_fd) {
        epoll_fd  = epoll_create1(0);
        if (epoll_fd == -1) throw std::runtime_error("epol_create1 failed");
    }

    void run(PacketHandler handler) override {
        struct epoll_event ev{};
        ev.events = EPOLLIN;
        ev.data.fd = sock_fd;
        epoll_ctl(epoll_fd, EPOLL_CTL_ADD, sock_fd, &ev);

        std::vector<uint8_t> buffer(4096);

        while (true) {
            struct epoll_event events[16];
            int nfds = epoll_wait(epoll_fd, events, 16, -1);
            for (int i = 0; i < nfds; ++i) {
                if (events[i].data.fd == sock_fd) {
                    ssize_t len = ::read(sock_fd, buffer.data(), buffer.size());
                    if (len > 0) handler(buffer.data(), static_cast<std::size_t>(len));
                }
            }
        }
    }
};


} // namespace io