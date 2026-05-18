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
    #include <queue>

namespace Plazza {
    constexpr int EPISUCCESS = 0;
    constexpr int EPIERROR = 84;
    constexpr int SKIP = -1;
    constexpr int NBARGS = 3;
    constexpr std::string_view HELP = "public/help.txt";

    class Plazza {
        public:
            Plazza(std::queue<std::string>);

            void showHelp();

        private:
            double _multiplier;
            int _nbCook;
            int _restock;
    };
};

#endif
