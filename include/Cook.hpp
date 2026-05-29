/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** Cook
*/

#ifndef COOK_HPP_
#define COOK_HPP_

#include <thread>
#include <atomic>

#include "Utils.hpp"
#include "SafeQueue.hpp"
#include "IngredientMap.hpp"

namespace Plazza {

    class Cook {
        public:
            Cook(SafeQueue<Utils::Pizza> &orders,
                SafeQueue<Utils::Pizza> &finishedOrders,
                double multiplier, std::atomic<bool> &loop,
                IngredientMap &ingredients);

            void start() { _thread = std::thread([this]() { run(); }); };

            void join() { if (_thread.joinable()) _thread.join(); };

            bool isActive() { return _active; };

        private:
            std::thread _thread;
            SafeQueue<Utils::Pizza> &_orders;
            SafeQueue<Utils::Pizza> &_finishedOrders;
            IngredientMap &_ingredients;
            double _multiplier;
            bool _active = false;
            std::atomic<bool> &_loop;
            Utils::Clock _clock;
            bool _cooking = false;
            double _time = 0;
            Utils::Pizza _pizza;

            void run();
            void cooking();
            bool waiting();
    };
};

#endif /* !COOK_HPP_ */
