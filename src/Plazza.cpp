/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** Plazza
*/

#include <iostream>
#include <fstream>
#include "Plazza.hpp"
#include "Exception.hpp"

namespace Plazza {
    Plazza::Plazza(std::queue<std::string> args)
    {
        if (args.size() != NBARGS) {
            showHelp();
            throw WrongArgsException();
        }
    }

    void Plazza::showHelp()
    {
        std::ifstream file({std::string(HELP)});

    if (file.is_open())
        std::cout << file.rdbuf();
    }
};