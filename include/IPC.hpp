/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** IPC
*/

#ifndef IPC_HPP
    #define IPC_HPP

#include <string>
#include <unistd.h>
#include "Exception.hpp"

namespace Plazza {
    class IPC {
        public:
            IPC(int fd) : _fd(fd) {};
            ~IPC()
            {
                if (_fd != -1)
                    close(_fd);
            };

            template<typename T>
            void send(const T msg) const
            {
                if (write(_fd, &msg, sizeof(T)) < 0)
                    throw SendException();
            }

            template<typename T>
            T receive() const
            {
                T buf = {};
                if (read(_fd, &buf, sizeof(T)) <= 0)
                    throw CloseException();
                return buf;
            }

            int getFd() const {return _fd;}

            class IPCException : public PlazzaException {
                public:
                    IPCException(std::string str)
                        : PlazzaException("IPC Error: " + str) {};
            };

            class SendException : public IPCException {
                public:
                    SendException() : IPCException("Send Failed!") {};
            };

            class CloseException : public IPCException {
                public:
                    CloseException() : IPCException("Close Connection!") {};
            };

        private:
            int _fd;
    };
}

#endif