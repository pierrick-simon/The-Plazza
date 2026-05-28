/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** IngredientMap
*/

#ifndef INGREDIENTMAP_HPP_
#define INGREDIENTMAP_HPP_

#include <unordered_map>
#include <iostream>

#include "Utils.hpp"
#include "SafeStock.hpp"

namespace Plazza {

    class IngredientMap {
        public:
            IngredientMap(const std::size_t &v);

            void refill(std::size_t v = 0);
            void consume(const Utils::Ingredient &ingredients);
            
            Utils::Ingredient seek();

        private:
            std::unordered_map<Utils::IngredientType, SafeStock> _map;
    };
};

#endif /* !INGREDIENTMAP_HPP_ */
