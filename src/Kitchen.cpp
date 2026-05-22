/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** Kitchen
*/

#include <unistd.h>
#include <iostream>
#include "Kitchen.hpp"

namespace Plazza {
    Kitchen::Kitchen(int fd) :
        _ipc(fd)
    {
        for (int i = 0; i < Utils::NB_INGREDIENT; i++) {
            auto ingredient = static_cast<Utils::IngredientType>(i);
            _ingredientsStock.insert(std::make_pair(ingredient, START_INGREDIENT));
        }
    }

    void Kitchen::run(int fd)
    {
        Kitchen kitchen(fd);

        sleep(1);
        std::cout << "End" << std::endl;
    }

    const Utils::Recipes Kitchen::_recipes =
    {
        {
            Utils::Margarita,
            {
                {
                    {Utils::DOUGH, 1},
                    {Utils::TOMATO, 1},
                    {Utils::GRUYERE, 1}
                }, 
                1
            }
        },
        {
            Utils::Regina,
            {
                {
                    {Utils::DOUGH, 1},
                    {Utils::TOMATO, 1},
                    {Utils::GRUYERE, 1},
                    {Utils::HAM, 1},
                    {Utils::MUSHROOMS, 1}
                }, 
                2
            }
        },
        {
            Utils::Americana,
            {
                {
                    {Utils::DOUGH, 1},
                    {Utils::TOMATO, 1},
                    {Utils::GRUYERE, 1},
                    {Utils::STEAK, 1}
                }, 
                2
            }
        },
        {
            Utils::Regina,
            {
                {
                    {Utils::DOUGH, 1},
                    {Utils::TOMATO, 1},
                    {Utils::EGGPLANT, 1},
                    {Utils::GOAT_CHEESE, 1},
                    {Utils::CHIEF_LOVE, 1}
                }, 
                4
            }
        },
    };
}
