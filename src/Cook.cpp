/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** Cook
*/

#include "Cook.hpp"
#include "Utils.hpp"
#include "Kitchen.hpp"

#include <iostream>

Plazza::Cook::Cook(SafeQueue<Utils::Pizza> &orders,
                SafeQueue<Utils::Pizza> &finishedOrders,
                double multiplier, SafeValue<bool> &loop):
    _orders(orders),
    _finishedOrders(finishedOrders),
    _multiplier(multiplier),
    _loop(loop) {}

void Plazza::Cook::run()
{
    while (_loop.get()) {
        auto front = _orders.pop();

        _active = true;

        auto time = Kitchen::recipes.at(front.first).second
            * _multiplier * 1000;
        std::this_thread::sleep_for(
            std::chrono::milliseconds(static_cast<int>(time)));

        _active = false;

        _finishedOrders.push(front);
    }
}
