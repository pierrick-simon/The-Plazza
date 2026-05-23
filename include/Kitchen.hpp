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
            void close();

            IPC _ipc;
            Utils::Ingredient _ingredientsStock;
            static const Utils::Recipes _recipes;
            Utils::Clock _inactivity;
    };
}

#endif
