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

            void showHelp();

        private:
            double _multiplier;
            std::size_t _nbCook;
            double _restock;
    };
};

#endif
