/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** Reception
*/

#ifndef RECEPTION_HPP
    #define RECEPTION_HPP

    #include <vector>
    #include <map>
    #include "Utils.hpp"

namespace Plazza {
    class Reception {
        public:

            void order(std::map<Utils::Pizza, std::size_t>);

            void status();

        private:
            std::vector<int> _kitchenFd;
    };
}

#endif
