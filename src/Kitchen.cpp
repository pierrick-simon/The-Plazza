/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** Kitchen
*/

#include <iostream>
#include <Packet.hpp>
#include "Kitchen.hpp"
#include "Utils.hpp"
#include "Connect.hpp"

namespace Plazza {
    Kitchen::Kitchen(int fd, double multiplier,
        std::size_t nbCook, double restock) :
        _ipc(fd), _multiplier(multiplier), _nbCook(nbCook),
        _restock(restock), _loop(true)
    {
        for (int i = 0; i < Utils::NB_INGREDIENT; i++) {
            auto ingredient = static_cast<Utils::IngredientType>(i);
            _ingredientsStock.insert(std::make_pair(ingredient, START_INGREDIENT));
        }
        _inactivity = std::chrono::steady_clock::now();
        _commands[CLOSE] = [this]() {close();};
        _commands[COMMAND] = [this]() {command();};
    }

    Kitchen::~Kitchen()
    {
       _ipc.send(CLOSE);
    }

    void Kitchen::run(int fd, double multiplier,
        std::size_t nbCook, double restock)
    {
        Kitchen kitchen(fd, multiplier, nbCook, restock);

        while (kitchen._loop) {
            auto now = std::chrono::steady_clock::now();
            if (std::chrono::duration<double>(now - kitchen._inactivity)
                .count() > OPEN_TIME)
                break;
            if (!kitchen._orders.empty()) {
                kitchen._inactivity = now;
                kitchen.handleCook();
            }
            auto info = Connect::infoToRead({kitchen._ipc.getFd()});
            if (info.size() == 1 && info[0])
                kitchen.readMsg();
        }
    }

    void Kitchen::handleCook()
    {
        if (_cook) {
            auto now = std::chrono::steady_clock::now();
            auto front = _orders.front();
            auto time = _recipes.at(front.first).second * _multiplier;
            if (std::chrono::duration<double>(now - _oven)
                .count() > time) {
                Packet<sizeof(Utils::Pizza)> packet;
                packet << front;
                _ipc.send(COMMAND);
                _ipc.send(packet);
                _cook = false;
                _orders.pop();
            }
        } else {
            if (!_orders.empty()) {
                _cook = true;
                _oven = std::chrono::steady_clock::now();
            }
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

    void Kitchen::command()
    {
        auto packet = _ipc.receive<Packet<sizeof(Utils::Pizza)>>();

        if (_orders.size() < _nbCook * 2) {
            Utils::Pizza pizza;
            packet >> pizza;
            _orders.push(pizza);
            _ipc.send(OK);
            return;
        }
        _ipc.send(ERROR);
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
                1.0
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
                2.0
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
                2.0
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
                4.0
            }
        },
    };
}
