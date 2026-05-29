/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** Chef
*/

#include "Chef.hpp"

namespace Plazza {

    Chef::Chef(std::atomic<bool> &loop,
        IngredientMap &ingredients, std::size_t restock):
        _loop(loop),
        _ingredients(ingredients),
        _restock(double(restock) / 1000.0)
    {
        _clock = std::chrono::steady_clock::now();
    };
    
    void Chef::run()
    {
        while (_loop.load()) {
            auto now = std::chrono::steady_clock::now();
            if (std::chrono::duration<double>(now - _clock)
                .count() > _restock) {
                _ingredients.refill(1);
                _clock = now;
            }
        }
    }
};
