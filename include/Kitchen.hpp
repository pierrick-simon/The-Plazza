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
    #include <queue>
    #include "Plazza.hpp"
    #include "IPC.hpp"
    #include "Utils.hpp"

namespace Plazza {

    constexpr std::size_t START_INGREDIENT = 5;
    constexpr double OPEN_TIME = 5.0;

    class Kitchen {
        public:
            static void run(int fd, double multiplier,
                std::size_t nbCook, double _restock);

        private:
            Kitchen(int fd, double multiplier,
                std::size_t nbCook, double restock);
            ~Kitchen();
            void handleCook();
            void close();
            void command();
            void readMsg();

            IPC _ipc;
            double _multiplier;
            std::size_t _nbCook;
            double _restock;
            Utils::Ingredient _ingredientsStock;
            Utils::Clock _inactivity;
            Utils::Clock _oven;
            bool _cook = false;
            std::queue<Utils::Pizza> _orders;
            bool _loop;

            std::unordered_map<int, std::function<void ()>> _commands;
            static const Utils::Recipes _recipes;
    };
}

#endif
