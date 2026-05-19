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

            enum PizzaType
            {
                Regina = 1,
                Margarita = 2,
                Americana = 4,
                Fantasia = 8
            };

            enum PizzaSize
            {
                S = 1,
                M = 2,
                L = 4,
                XL = 8,
                XXL = 16
            };

            using Pizza = std::pair<PizzaType, PizzaSize>;

            Plazza(std::vector<std::string>);
            std::map<Pizza, std::size_t> parsePizzaOrders(std::string);

            void run();

            void showHelp();

        private:
            void addNewPizza(Pizza,
                std::map<Pizza, std::size_t> &, std::string nbStr);
            std::size_t parseNumber(std::string strNb);
            void parsePizzaOrder(std::string, std::map<Pizza, std::size_t> &);

            void parseCommands(std::string command);
            bool getCommand(std::string);
            void newCommand(std::string line);

            void status();

            double _multiplier;
            std::size_t _nbCook;
            double _restock;

            std::unordered_map<std::string, std::function<void()>> _commands;

            static const std::unordered_map<std::string, PizzaType> _pizzaType;
            static const std::unordered_map<std::string, PizzaSize> _pizzaSize;
    };
};

#endif
