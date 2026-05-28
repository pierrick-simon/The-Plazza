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
    #include <string>
    #include <ostream>

namespace Plazza {

    constexpr int CLOSE = 300;
    constexpr int OK = 200;
    constexpr int COMMAND = 230;
    constexpr int ERROR = 500;

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
                std::pair<Ingredient, double>>;
            using Clock = std::chrono::_V2::steady_clock::time_point;
            
            static constexpr std::size_t START_INGREDIENT = 5;

            static PizzaType getType(std::string);
            static PizzaSize getSize(std::string);
            static std::string typeToString(PizzaType type);
            static std::string sizeToString(PizzaSize size);
            static std::string pizzaToString(Pizza);
            static const std::unordered_map<PizzaType, std::string> _strPizzaType;
            static const std::unordered_map<PizzaSize, std::string> _strPizzaSize;
    };


    std::ostream &operator<<(std::ostream &os, const Utils::Pizza &pizza);
}

#endif
