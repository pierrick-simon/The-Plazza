/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** Kitchen
*/

#include <unistd.h>
#include <iostream>
#include "Kitchen.hpp"
#include "Utils.hpp"
#include "Connect.hpp"

namespace Plazza {
    Kitchen::Kitchen(int fd) :
        _ipc(fd), _loop(true)
    {
        for (int i = 0; i < Utils::NB_INGREDIENT; i++) {
            auto ingredient = static_cast<Utils::IngredientType>(i);
            _ingredientsStock.insert(std::make_pair(ingredient, START_INGREDIENT));
        }
        _inactivity = std::chrono::steady_clock::now();
        _commands[CLOSE] = [this]() {close();};
    }

    Kitchen::~Kitchen()
    {
       _ipc.send(CLOSE); 
    }

    void Kitchen::run(int fd)
    {
        Kitchen kitchen(fd);

        while (kitchen._loop) {
            auto now = std::chrono::steady_clock::now();
            if (std::chrono::duration<double>(now - kitchen._inactivity)
                .count() > OPEN_TIME)
                break;
            if (!kitchen._orders.empty())
                kitchen._inactivity = now;
            auto info = Connect::infoToRead({kitchen._ipc.getFd()});
            if (info.size() == 1 && info[0])
                kitchen.readMsg();
        }
    }

    void Kitchen::readMsg()
    {
        try {
            int value = _ipc.receive<int>();
            auto find = _commands.find(value);
            if (find != _commands.end())
                find->second();
        } catch (IPC::CloseException &_) {
            _loop = false;
        }
    }

    void Kitchen::close()
    {
        _loop = false;
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
            Utils::Fantasia,
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
