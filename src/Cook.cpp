/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** Cook
*/

#include "Cook.hpp"
#include "Utils.hpp"
#include "Kitchen.hpp"
#include "Packet.hpp"

#include <iostream>

Plazza::Cook::Cook(std::mutex &mut, std::counting_semaphore<> &sem, IPC &ipc,
    std::queue<Utils::Pizza> &orders, double multiplier, bool &loop):
    _mut(mut),
    _orders(orders),
    _thread([this]() { run(); }),
    _multiplier(multiplier),
    _sem(sem),
    _ipc(ipc),
    _loop(loop) {}

void Plazza::Cook::run()
{
    while (_loop) {
        _sem.acquire();

        auto front = _orders.front();
        _mut.lock();
        _orders.pop();
        _mut.unlock();

        _available = false;
        auto time = Kitchen::recipes.at(front.first).second
            * _multiplier * 1000;
        std::this_thread::sleep_for(
            std::chrono::milliseconds(static_cast<int>(time)));

        if (!_loop)
            return;
        Packet<sizeof(Utils::Pizza)> packet;
        packet << front;
        _mut.lock();
        _ipc.send(COMMAND);
        _ipc.send(packet);
        _mut.unlock();
        _available = true;
    }
}
