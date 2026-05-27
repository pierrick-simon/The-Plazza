/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** Cook
*/

#ifndef COOK_HPP_
#define COOK_HPP_

#include <thread>

#include "Utils.hpp"
#include "SafeQueue.hpp"

namespace Plazza {

    class Cook {
        public:
            Cook(SafeQueue<Utils::Pizza> &orders,
                SafeQueue<Utils::Pizza> &finishedOrders,
                double multiplier, bool &loop);

            void join() { _thread.join(); };

            bool isActive() { return _active; };

        private:
            std::thread _thread;
            SafeQueue<Utils::Pizza> &_orders;
            SafeQueue<Utils::Pizza> &_finishedOrders;
            double _multiplier;
            bool _active = false;
            bool &_loop;

            void run();
    };
};

#endif /* !COOK_HPP_ */
