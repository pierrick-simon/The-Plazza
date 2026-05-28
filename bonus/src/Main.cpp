/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** Main
*/

#include <iostream>
#include "Plazza.hpp"
#include "../include/Exception.hpp"

int main(int ac, char **av)
{
    std::vector<std::string> args(std::vector<std::string>(av + 1, av + ac));
    try {
        auto plazza = Plazza::Plazza(args);
        plazza.run();
    } catch (Plazza::PlazzaException &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}