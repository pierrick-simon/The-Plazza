/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** Chef
*/

#ifndef CHEF_HPP_
#define CHEF_HPP_

namespace Plazza {

    class Chef {
        public:
            Cook(std::atomic<bool> &loop, IngredientMap &ingredients, );

            void start() { _thread = std::thread([this]() { run(); }); };

            void join() { _thread.detach(); };

            bool isActive() { return _active; };

        private:
            std::thread _thread;
            SafeQueue<Utils::Pizza> &_orders;
            SafeQueue<Utils::Pizza> &_finishedOrders;
            IngredientMap &_ingredients;
            double _multiplier;
            bool _active = false;
            std::atomic<bool> &_loop;

            void run();
    };

};

#endif /* !CHEF_HPP_ */
