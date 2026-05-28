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
        _restock(restock) {};
    
    void Chef::run()
    {
        while (_loop.load()) {
            std::this_thread::sleep_for(
                std::chrono::milliseconds(_restock));
            _ingredients.refill(1);
        }
    }
};
