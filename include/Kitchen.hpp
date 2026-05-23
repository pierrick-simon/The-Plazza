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
            static void run(int fd);

        private:
            Kitchen(int fd);
            ~Kitchen();
            void close();
            void readMsg();

            IPC _ipc;
            Utils::Ingredient _ingredientsStock;
            static const Utils::Recipes _recipes;
            Utils::Clock _inactivity;
            std::queue<Utils::Pizza> _orders;
            bool _loop;
            std::unordered_map<int, std::function<void ()>> _commands;
    };
}

#endif
