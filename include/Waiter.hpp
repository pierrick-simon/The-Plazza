/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** Waiter
*/

#ifndef WAITER_HPP_
#define WAITER_HPP_

#include <thread>

#include "Utils.hpp"
#include "IPC.hpp"
#include "SafeQueue.hpp"

namespace Plazza {

    class Waiter {
        public:
            Waiter(SafeQueue<Utils::Pizza> &finishedOrders,
                bool &loop, IPC &ipc);

            void join() { _thread.join(); };

        private:
            std::thread _thread;
            SafeQueue<Utils::Pizza> &_finishedOrders;
            IPC &_ipc;
            bool &_loop;

            void run();
    };
};

#endif /* !WAITER_HPP_ */
