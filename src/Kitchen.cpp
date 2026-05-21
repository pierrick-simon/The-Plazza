/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** Kitchen
*/

#include "Kitchen.hpp"

namespace Plazza {
    Kitchen::Kitchen()
    {
        for (int i = 0; i < Plazza::Plazza::NB_INGREDIENT; i++) {
            auto ingredient = static_cast<Plazza::Plazza::IngredientType>(i);
            _ingredientsStock.insert(std::make_pair(ingredient, START_INGREDIENT));
        }
    }

    const Plazza::Recipes Kitchen::_recipes =
    {
        {
            Plazza::Margarita,
            {
                {
                    {Plazza::DOUGH, 1},
                    {Plazza::TOMATO, 1},
                    {Plazza::GRUYERE, 1}
                }, 
                1
            }
        },
        {
            Plazza::Regina,
            {
                {
                    {Plazza::DOUGH, 1},
                    {Plazza::TOMATO, 1},
                    {Plazza::GRUYERE, 1},
                    {Plazza::HAM, 1},
                    {Plazza::MUSHROOMS, 1}
                }, 
                2
            }
        },
        {
            Plazza::Americana,
            {
                {
                    {Plazza::DOUGH, 1},
                    {Plazza::TOMATO, 1},
                    {Plazza::GRUYERE, 1},
                    {Plazza::STEAK, 1}
                }, 
                2
            }
        },
        {
            Plazza::Regina,
            {
                {
                    {Plazza::DOUGH, 1},
                    {Plazza::TOMATO, 1},
                    {Plazza::EGGPLANT, 1},
                    {Plazza::GOAT_CHEESE, 1},
                    {Plazza::CHIEF_LOVE, 1}
                }, 
                4
            }
        },
    };
}
