/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** Cook
*/

#ifndef COOK_HPP_
#define COOK_HPP_

#include <thread>
#include <mutex>
#include <queue>
#include <semaphore>

#include "Utils.hpp"
#include "IPC.hpp"

namespace Plazza {

    class Cook {
        public:
            Cook(std::mutex &mut, std::counting_semaphore<> &sem, IPC &ipc,
                std::queue<Utils::Pizza> &orders, double multiplier, bool &loop);

            void join() { _thread.join(); };

        private:
            std::thread _thread;
            std::mutex &_mut;
            std::queue<Utils::Pizza> &_orders;
            std::counting_semaphore<> &_sem;
            IPC &_ipc;
            double _multiplier;
            bool _available = true;
            bool &_loop;

            void run();
    };
};

#endif /* !COOK_HPP_ */
