/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** Plazza
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include "Plazza.hpp"
#include "Exception.hpp"

namespace Plazza {
    Plazza::Plazza(std::vector<std::string> args)
    {
        if (args.size() != NBARGS) {
            showHelp();
            throw WrongArgsException();
        }
        std::istringstream stream1(args[MULTIPLIER]);
        stream1 >> _multiplier;
        std::istringstream stream2(args[NBCOOK]);
        stream2 >> _nbCook;
        std::istringstream stream3(args[RESTOCK]);
        stream3 >> _restock;
        if (stream1.fail() || !stream1.eof() || _multiplier < 0
            || stream2.fail() || !stream2.eof() || _nbCook == 0
            || stream3.fail() || !stream3.eof() || _restock < 0)
            throw WrongArgsException();
    }

    void Plazza::showHelp()
    {
        std::ifstream file({std::string(HELP)});

    if (file.is_open())
        std::cout << file.rdbuf();
    }
};