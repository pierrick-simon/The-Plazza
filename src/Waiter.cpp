/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** Waiter
*/

#include "Waiter.hpp"
#include "Packet.hpp"

Plazza::Waiter::Waiter(SafeQueue<Utils::Pizza> &finishedOrders,
    bool &loop, IPC &ipc):
    _finishedOrders(finishedOrders),
    _loop(loop),
    _ipc(ipc) {}

void Plazza::Waiter::run()
{
    while (_loop) {
        auto pizza = _finishedOrders.pop();

        Packet<sizeof(Utils::Pizza)> packet;
        packet << pizza;
        _ipc.send(COMMAND);
        _ipc.send(packet);
    }
}
