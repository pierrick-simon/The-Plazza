/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** Kitchen
*/

#ifndef KITCHEN_HPP
    #define KITCHEN_HPP

    #include <unordered_map>
    #include <vector>
    #include <string>
    #include <atomic>
    #include "Plazza.hpp"
    #include "IPC.hpp"
    #include "Utils.hpp"
    #include "SafeQueue.hpp"
    #include "Cook.hpp"
    #include "Chef.hpp"
    #include "IngredientMap.hpp"

namespace Plazza {

    constexpr std::size_t START_INGREDIENT = 5;
    constexpr double OPEN_TIME = 5.0;


    class Kitchen {
        public:
            static void run(int fd, double multiplier,
                std::size_t nbCook, std::size_t _restock);

            static const Utils::Recipes recipes;

        private:
            Kitchen(int fd, double multiplier,
                std::size_t nbCook, std::size_t restock);
            ~Kitchen();
            void close();
            void command();
            void readMsg();
            std::size_t getActiveCookNumber();
            void sendFinishedOrders();

            IPC _ipc;
            double _multiplier;
            std::size_t _nbCook;
            std::size_t _restock;
            IngredientMap _ingredients;
            Utils::Clock _inactivity;
            Utils::Clock _oven;
            SafeQueue<Utils::Pizza> _orders;
            SafeQueue<Utils::Pizza> _finishedOrders;
            std::vector<Cook> _cooks;
            Chef _chef;

            std::atomic<bool> _loop;

            std::unordered_map<int, std::function<void ()>> _commands;
    };
}

#endif
