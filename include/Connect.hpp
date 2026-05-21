/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** Connect
*/

#ifndef CONNECT_HPP
    #define CONNECT_HPP

#include <functional>
#include "Exception.hpp"

namespace Plazza {
    class Connect {
        public:
            static int connect(std::function<void (int fd)>);

            static void wait();

            class ConnectException : public PlazzaException {
                public:
                    ConnectException(std::string str)
                        : PlazzaException("Connect Error: " + str) {};
            };

            class SocketException : public ConnectException {
                public:
                    SocketException() : ConnectException("Socket Failed!") {};
            };

            class ForkException : public ConnectException {
                public:
                    ForkException() : ConnectException("Fork Failed!") {};
            };
    };
};

#endif