/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** Connect
*/

#include <unistd.h>
#include <sys/socket.h>
#include <poll.h>
#include <sys/wait.h>
#include "Connect.hpp"

namespace Plazza {
    int Connect::connect(std::function<void (int fd)> func)
    {
        int sv[2] = {};

        if (socketpair(AF_UNIX, SOCK_STREAM, 0, sv) < 0)
            throw SocketException();
        pid_t pid = fork();
        if (pid < 0)
            throw ForkException();
        if (pid == 0) {
            close(sv[0]);
            func(sv[1]);
            exit(0);
        }
        close(sv[1]);
        return sv[0];
    }

    void Connect::wait()
    {
        while (waitpid(-1, nullptr, 0) > 0);
    }

    std::vector<bool> Connect::infoToRead(std::vector<int> fds)
    {
        std::vector<struct pollfd> pfds;
        std::vector<bool> info;

        for (auto &fd : fds)
            pfds.push_back({fd, POLLIN | POLLHUP, 0});
        if (fds.empty())
            return info;
        if (poll(pfds.data(), pfds.size(), 0) < 0)
            throw PollException();
        for (std::size_t i = 0; i < pfds.size(); ++i)
            info.push_back((pfds[i].revents & (POLLIN | POLLHUP)));
        return info;
    }
}
