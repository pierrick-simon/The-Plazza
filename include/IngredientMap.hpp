/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** IngredientMap
*/

#ifndef INGREDIENTMAP_HPP_
#define INGREDIENTMAP_HPP_

#include <unordered_map>
#include <mutex>
#include <condition_variable>
#include <iostream>

#include "Utils.hpp"

namespace Plazza {

    class SafeStock {
        public:
            SafeStock(): _value(0) {};
            SafeStock(const std::size_t &v): _value(v) {};

            SafeStock &operator<<(const std::size_t &v)
            {
                std::unique_lock lock(_mut);
                for (auto i = 0; i < v; ++i) {
                    ++_value;
                    _cond_var.notify_one();
                }
                return *this;
            }
            
            SafeStock &operator>>(const std::size_t &v)
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

            SafeStock &operator=(const std::size_t &v)
            {
                if (v >= _value)
                    return *this;
                return (*this << (v - _value));
            }

        private:
            std::size_t _value;
            std::condition_variable _cond_var;
            std::mutex _mut;
    };

    class IngredientMap {
        public:
            IngredientMap(const std::size_t &v);

            void refill(std::size_t v = 0);
            void consume(const Utils::Ingredient &ingredients);

        private:
            std::unordered_map<Utils::IngredientType, SafeStock> _map;
    };
};

#endif /* !INGREDIENTMAP_HPP_ */
