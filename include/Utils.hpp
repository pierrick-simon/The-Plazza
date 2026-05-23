/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** Utils
*/

#ifndef UTILS_HPP
    #define UTILS_HPP

    #include <unordered_map>
    #include <chrono>

namespace Plazza {

    constexpr int CLOSE = 0;

    class Utils {
        public:
            enum PizzaType
            {
                Regina = 1,
                Margarita = 2,
                Americana = 4,
                Fantasia = 8
            };

            enum PizzaSize
            {
                S = 1,
                M = 2,
                L = 4,
                XL = 8,
                XXL = 16
            };

            enum IngredientType
            {
                DOUGH,
                TOMATO,
                GRUYERE,
                HAM,
                MUSHROOMS,
                STEAK,
                EGGPLANT,
                GOAT_CHEESE,
                CHIEF_LOVE,
                NB_INGREDIENT
            };

            using Pizza = std::pair<PizzaType, PizzaSize>;
            using Ingredient = std::unordered_map<
                IngredientType, std::size_t>;
            using Recipes = std::unordered_map<PizzaType,
                std::pair<Ingredient, std::size_t>>;
            using Clock = std::chrono::_V2::steady_clock::time_point;

    };
}

#endif
