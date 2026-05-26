/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** Kitchen
*/

#ifndef KITCHEN_HPP
    #define KITCHEN_HPP

    #include <unordered_map>
    #include <vector>
    #include <string>
    #include <queue>
    #include <mutex>
    #include <semaphore>
    #include "Plazza.hpp"
    #include "IPC.hpp"
    #include "Utils.hpp"

namespace Plazza {

    constexpr std::size_t START_INGREDIENT = 5;
    constexpr double OPEN_TIME = 5.0;

    class Cook;

    class Kitchen {
        public:
            static void run(int fd, double multiplier,
                std::size_t nbCook, double _restock);

            static const Utils::Recipes recipes;

        private:
            Kitchen(int fd, double multiplier,
                std::size_t nbCook, double restock);
            ~Kitchen();
            void close();
            void command();
            void readMsg();

            IPC _ipc;
            double _multiplier;
            std::size_t _nbCook;
            double _restock;
            Utils::Ingredient _ingredientsStock;
            Utils::Clock _inactivity;
            Utils::Clock _oven;
            std::queue<Utils::Pizza> _orders;
            std::vector<Cook> _cooks;
            bool _loop;

            std::mutex _mut;
            std::counting_semaphore<> _sem;

            std::unordered_map<int, std::function<void ()>> _commands;
    };
}

#endif
