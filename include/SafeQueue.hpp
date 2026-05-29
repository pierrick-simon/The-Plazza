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
#include <iostream>
#include "Exception.hpp"

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

            void shutdown()
            {
                std::unique_lock lock(_mut);
                _shutdown = true;
                _cond_var.notify_all();
            }

            T pop()
            {
                std::unique_lock lock(_mut);
                _cond_var.wait(lock, [this]() {
                    return !_queue.empty() || _shutdown;
                });
                if (_shutdown && _queue.empty())
                    throw SafeQueueException("Queue shutdown");
                auto value = _queue.front();
                _queue.pop();
                return value;
            }

            std::optional<T> tryPop() {
                std::unique_lock lock(_mut);
                if (_queue.empty() || _shutdown)
                    return std::nullopt;
                auto value = _queue.front();
                _queue.pop();
                return value;
            }

            bool empty() {
                std::unique_lock lock(_mut);
                return _queue.empty();
            }

            std::size_t size() {
                std::unique_lock lock(_mut);
                return _queue.size();
            }

            class SafeQueueException : public PlazzaException {
                public:
                    SafeQueueException(std::string str)
                        : PlazzaException("SafeQueue Error: " + str) {};
            };

        private:
            std::queue<T> _queue;
            std::condition_variable _cond_var;
            std::mutex _mut;
            bool _shutdown = false;
    };
};

#endif /* !SAFEQUEUE_HPP_ */
