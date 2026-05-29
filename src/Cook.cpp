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
    _ingredients(ingredients)
    {
        _clock = std::chrono::steady_clock::now();
    }

void Plazza::Cook::cooking()
{
    auto now = std::chrono::steady_clock::now();
    if (std::chrono::duration<double>(now - _clock).count() > _time) {
        _cooking = false;
        _active = false;
        _finishedOrders.push(_pizza);
    }
}

bool Plazza::Cook::waiting()
{
    try {
        _pizza = _orders.pop();
    } catch (SafeQueue<Utils::Pizza>::SafeQueueException &) {
        return true;
    }
    _active = true;
    auto recipe = Kitchen::recipes.at(_pizza.first);
    try {
        _ingredients.consume(recipe.first);
    } catch (SafeStock::SafeStockException &) {
        return true;
    }
    _time = recipe.second * _multiplier;
    _clock = std::chrono::steady_clock::now();
    _cooking = true;
    return false;
}

void Plazza::Cook::run()
{
    while (_loop.load()) {
        if (_cooking)
            cooking();
        else if (waiting())
            return;
    }
}
