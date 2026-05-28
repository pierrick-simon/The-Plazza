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

namespace Plazza {

    class SafeStock {
        public:
            SafeStock(const std::size_t &v = 0);

            SafeStock &operator<<(const std::size_t &v);
            SafeStock &operator>>(const std::size_t &v);

        private:
            std::size_t _value;
            std::size_t _max;
            std::condition_variable _cond_var;
            std::mutex _mut;
    };
};


#endif /* !SAFESTOCK_HPP_ */
