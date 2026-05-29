/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** SafeStock
*/

#ifndef SAFESTOCK_HPP_
#define SAFESTOCK_HPP_

#include <mutex>
#include <condition_variable>
#include "Exception.hpp"

namespace Plazza {

    class SafeStock {
        public:
            SafeStock(const std::size_t &v = 0);

            SafeStock &operator<<(const std::size_t &v);
            SafeStock &operator>>(const std::size_t &v);

            void shutdown();

            std::size_t seek();

            class SafeStockException : public PlazzaException {
                public:
                    SafeStockException(std::string str)
                        : PlazzaException("SafeStock Error: " + str) {};
            };

        private:
            std::size_t _value;
            std::size_t _max;
            std::condition_variable _cond_var;
            std::mutex _mut;
            bool _shutdown = false;

    };
};


#endif /* !SAFESTOCK_HPP_ */
