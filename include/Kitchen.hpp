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

namespace Plazza {

    constexpr std::size_t START_INGREDIENT = 5;

    class Kitchen {
        public:
            Kitchen();

        private:
            Plazza::Ingredient _ingredientsStock;
            static const Plazza::Recipes _recipes;
    };
}

#endif
