/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** IngredientMap
*/

#include "IngredientMap.hpp"

namespace Plazza {
    IngredientMap::IngredientMap(const std::size_t &v)
    {
        for (std::size_t i = 0; i < Utils::NB_INGREDIENT; ++i) {
            auto ingredient = static_cast<Utils::IngredientType>(i);
            _map.insert(std::make_pair(ingredient, v));
        }
    }

    void IngredientMap::refill(std::size_t v)
    {
        for (auto &stock: _map)
            stock.second << v;
    }

    void IngredientMap::consume(const Utils::Ingredient &ingredients)
    {
        for (auto &ingredient: ingredients)
            _map[ingredient.first] >> ingredient.second;
    }
    
    Utils::Ingredient IngredientMap::seek()
    {
        Utils::Ingredient um;

        for (std::size_t i = 0; i < Utils::NB_INGREDIENT; ++i) {
            auto ingredient = static_cast<Utils::IngredientType>(i);
            um.insert(std::make_pair(ingredient, _map[ingredient].seek()));
        }
        return um;
    }
}
