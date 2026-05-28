/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** SafeStock
*/

#include <algorithm>

#include "SafeStock.hpp"

namespace Plazza {
    SafeStock::SafeStock(const std::size_t &v): _value(v), _max(v) {};

    SafeStock &SafeStock::operator<<(const std::size_t &v)
    {
        auto clamped = ((_max && v > _max) ? _max: v);
        std::unique_lock lock(_mut);
        for (auto i = _value; i < clamped; ++i) {
            ++_value;
            _cond_var.notify_one();
        }
        return *this;
    }
    
    SafeStock &SafeStock::operator>>(const std::size_t &v)
    {
        std::unique_lock lock(_mut);
        for (auto i = 0; i < v; ++i) {
            _cond_var.wait(lock, [this]() {
                return this->_value != 0;
            });
            --_value;
        }
        return *this;
    }

    std::size_t SafeStock::seek()
    {
        std::unique_lock lock(_mut); // en vrai a voir sah y'a un monde ou y'a pas besoin
        return _value;
    }

}
