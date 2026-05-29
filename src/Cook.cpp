/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** Cook
*/

#include <functional>
#include "Cook.hpp"
#include "Utils.hpp"
#include "Kitchen.hpp"

#include <iostream>

Plazza::Cook::Cook(SafeQueue<Utils::Pizza> &orders,
                SafeQueue<Utils::Pizza> &finishedOrders,
                double multiplier, std::atomic<bool> &loop,
                IngredientMap &ingredients):
    _orders(orders),
    _finishedOrders(finishedOrders),
    _multiplier(multiplier),
    _loop(loop),
    _ingredients(ingredients) {}

void Plazza::Cook::run()
{
    while (_loop.load()) {
        Utils::Pizza front;
        try {
            front = _orders.pop();
        } catch (SafeQueue<Utils::Pizza>::SafeQueueException &) {
            return;
        }
        _active = true;

        auto recipe = Kitchen::recipes.at(front.first);
        _ingredients.consume(recipe.first);
        if (!_loop.load())
            return;
        auto time = recipe.second * _multiplier * 1000;
        std::this_thread::sleep_for(
            std::chrono::milliseconds(static_cast<int>(time)));

        _active = false;

        if (!_loop.load())
            return;
        _finishedOrders.push(front);
    }
}
