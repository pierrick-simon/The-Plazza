/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** Connect
*/

#include <unistd.h>
#include <sys/socket.h>
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
}
