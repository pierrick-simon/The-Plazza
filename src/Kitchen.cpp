/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** Kitchen
*/

#include <iostream>
#include "Packet.hpp"
#include "Kitchen.hpp"
#include "Cook.hpp"
#include "Utils.hpp"
#include "Connect.hpp"

namespace Plazza {
    Kitchen::Kitchen(int fd, double multiplier,
        std::size_t nbCook, std::size_t restock) :
        _ipc(fd), _multiplier(multiplier), _nbCook(nbCook),
        _restock(restock), _loop(true), _ingredients(Utils::START_INGREDIENT)
    {
        for (std::size_t i = 0; i < _nbCook; ++i)
            _cooks.emplace_back(_orders, _finishedOrders,
                _multiplier, _loop, _ingredients);
        for (std::size_t i = 0; i < _nbCook; ++i)
            _cooks[i].start();
        _inactivity = std::chrono::steady_clock::now();
        _commands[CLOSE] = [this]() {close();};
        _commands[COMMAND] = [this]() {command();};
    }

    Kitchen::~Kitchen()
    {
        _ipc.send(CLOSE);
        _loop.store(false);
        for (auto &cook: _cooks) {
            cook.join();
        }
    }

    void Kitchen::run(int fd, double multiplier,
        std::size_t nbCook, std::size_t restock)
    {
        Kitchen kitchen(fd, multiplier, nbCook, restock);

        while (kitchen._loop.load()) {
            kitchen.sendFinishedOrders();
            auto now = std::chrono::steady_clock::now();
            if (std::chrono::duration<double>(now - kitchen._inactivity)
                .count() > OPEN_TIME)
                break;
            if (!kitchen._orders.empty() || !kitchen._finishedOrders.empty() || kitchen.getActiveCookNumber())
                kitchen._inactivity = now;
            auto info = Connect::infoToRead({kitchen._ipc.getFd()});
            if (info.size() == 1 && info[0])
                kitchen.readMsg();
        }
        kitchen.sendFinishedOrders();
    }

    std::size_t Kitchen::getActiveCookNumber()
    {
        std::size_t i = 0;

        for (auto &cook: _cooks)
            if (cook.isActive())
                ++i;
        return i;
    }

    void Kitchen::sendFinishedOrders()
    {
        while (!_finishedOrders.empty()) {
            auto pizza = _finishedOrders.pop();
            
            Packet<sizeof(Utils::Pizza)> packet;
            packet << pizza;
            _ipc.send(COMMAND);
            _ipc.send(packet);
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
            _loop.store(false);
        }
    }

    void Kitchen::close()
    {
        _loop.store(false);
    }

    void Kitchen::command()
    {
        auto packet = _ipc.receive<Packet<sizeof(Utils::Pizza)>>();

        if (_orders.size() + getActiveCookNumber() < _nbCook * 2) {
            Utils::Pizza pizza;
            packet >> pizza;
            _orders.push(pizza);
            _ipc.send(OK);
            return;
        }
        _ipc.send(ERROR);
    }

    const Utils::Recipes Kitchen::recipes =
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
