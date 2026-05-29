/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** Chef
*/

#ifndef CHEF_HPP_
#define CHEF_HPP_

#include <thread>
#include <atomic>

#include "Utils.hpp"
#include "IngredientMap.hpp"

namespace Plazza {

    class Chef {
        public:
            Chef(std::atomic<bool> &loop, IngredientMap &ingredients,
                std::size_t restock);

            void start() { _thread = std::thread([this]() { run(); }); };

            void join() { if (_thread.joinable()) _thread.join();};

        private:
            std::thread _thread;
            IngredientMap &_ingredients;
            double _restock;
            std::atomic<bool> &_loop;
            Utils::Clock _clock;

            void run();
    };

};

#endif /* !CHEF_HPP_ */
