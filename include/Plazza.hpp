/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** Plazza
*/

#ifndef PLAZZA_HPP
    #define PLAZZA_HPP

    #include <string>
    #include <string_view>
    #include <vector>
    #include <unordered_map>
    #include <functional>
    #include <map>
    #include "Utils.hpp"
    #include "Reception.hpp"

namespace Plazza {
    constexpr int EPISUCCESS = 0;
    constexpr int EPIERROR = 84;
    constexpr int SKIP = -1;
    constexpr int NBARGS = 3;
    constexpr std::string_view HELP = "public/help.txt";

    class Plazza {
        public:

            enum Args {
                MULTIPLIER,
                NBCOOK,
                RESTOCK
            };

            Plazza(std::vector<std::string>);
            std::map<Utils::Pizza, std::size_t> parsePizzaOrders(std::string);

            void run();

            void showHelp();

        private:
            void addNewPizza(Utils::Pizza,
                std::map<Utils::Pizza, std::size_t> &, std::string nbStr);
            std::size_t parseNumber(std::string strNb);
            void parsePizzaOrder(std::string, std::map<Utils::Pizza, std::size_t> &);

            void parseCommands(std::string command);
            bool getCommand(std::string);
            void newCommand(std::string line);

            bool readInput();

            Reception _reception;

            std::unordered_map<std::string, std::function<void()>> _commands;
    };
};

#endif
