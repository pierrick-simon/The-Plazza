/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** SafeQueue
*/

#ifndef SAFEQUEUE_HPP_
#define SAFEQUEUE_HPP_

#include <queue>
#include <mutex>
#include <condition_variable>

namespace Plazza {

    template <typename T>
    class SafeQueue {
        public:
            void push(T value)
            {
                std::unique_lock lock(_mut);
                _queue.push(value);
                _cond_var.notify_one();
            }

            T pop()
            {
                std::unique_lock lock(_mut);
                _cond_var.wait(lock, [this]() { return this->_queue.empty() == false; });
                        
                auto value = _queue.front();
                _queue.pop();
                return value;
            }

            bool empty() { return _queue.empty(); }
            std::size_t size() { return _queue.size(); }

        private:
            std::queue<T> _queue;
            std::condition_variable _cond_var;
            std::mutex _mut;
    };
};

#endif /* !SAFEQUEUE_HPP_ */
