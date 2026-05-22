/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** Plazza
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include "Plazza.hpp"
#include "Exception.hpp"
#include "Connect.hpp"
#include "Kitchen.hpp"

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
        _commands["status"] = [this]() {_reception.status();};
    }

    std::size_t Plazza::parseNumber(std::string strNb)
    {
        if (strNb.empty() || strNb.front() != 'x')
            throw NotValidNumberException(strNb);
        std::stringstream nbStream(strNb.substr(1));
        std::size_t nb;
        nbStream >> nb;
        if (nbStream.fail() || !nbStream.eof() || nb == 0)
            throw NotValidNumberException(strNb);
        return nb;
    }

    void Plazza::addNewPizza(Utils::Pizza pizza,
        std::map<Utils::Pizza, std::size_t> &pizzas, std::string strNb)
    {
        try {
            std::size_t nb = parseNumber(strNb);
            for (auto &tmp: pizzas) {
                if (tmp.first.first == pizza.first
                    && tmp.first.second == pizza.second) {
                    tmp.second += nb;
                    return;
                }
            }
            pizzas.insert(std::make_pair(pizza, nb));
        } catch (NotValidNumberException &e) {
            throw e;
        }
    }

    void Plazza::parsePizzaOrder(
        std::string order, std::map<Utils::Pizza, std::size_t> &pizzas)
    {
        std::string type;
        std::string size;
        std::string strNb;
        std::stringstream tmp(order);
        tmp >> type >> size >> strNb;
        if (tmp.fail() || !tmp.eof())
            throw InvalidOrderException();
        std::transform(type.begin(), type.end(), type.begin(),
            [](unsigned char c) {return std::tolower(c);});
        auto findType = _pizzaType.find(type);
        if (findType == _pizzaType.end())
            throw WrongPizzaTypeException(type);
        std::transform(size.begin(), size.end(), size.begin(),
            [](unsigned char c) {return std::toupper(c);});
        auto findSize = _pizzaSize.find(size);
        if (findSize == _pizzaSize.end())
            throw WrongPizzaSizeException(size);
        try {
            addNewPizza(std::make_pair(findType->second, findSize->second),
                pizzas, strNb);
        } catch (NotValidNumberException &e) {
            throw e;
        }
    }

    std::map<Utils::Pizza, std::size_t> Plazza::parsePizzaOrders(std::string line)
    {
        std::map<Utils::Pizza, std::size_t> pizzas;
        std::stringstream orders(line);
        std::string segment;
        std::vector<std::string> seglist;

        while(std::getline(orders, segment, ';'))
            seglist.push_back(segment);
        for (auto order: seglist) {
            try {
                parsePizzaOrder(order, pizzas);
            } catch (OrderException &e) {
                throw e;
            }
        }
        return pizzas;
    }

    void Plazza::newCommand(std::string line)
    {
        try {
            auto newCommand = parsePizzaOrders(line);
        } catch (OrderException &e) {
            throw e;
        }
    }

    void Plazza::parseCommands(std::string command)
    {
        auto iter = _commands.find(command);

        if (iter == _commands.end())
            throw WrongCommandException();
        iter->second();
    }

    bool Plazza::getCommand(std::string str)
    {
        std::string command;
        std::istringstream stream(str);
        stream >> command;
        bool exist = false;

        try {
        if (!stream.eof() || stream.fail())
            newCommand(str);
        else if (command == "exit")
            exist = true;
        else
            parseCommands(command);
        } catch (ShellException &e) {
            throw e;
        }
        return exist;
    }

    void Plazza::run()
    {
        std::string str;
        std::cout << "> ";
        bool exist = false;
    
        while (!exist && std::getline(std::cin, str)) {
            try {
                exist = getCommand(str);
            } catch (ShellException &e) {
                std::cerr << e.what() << std::endl;
            }
            if (!exist)
                std::cout << "> ";
        }
    }

    void Plazza::showHelp()
    {
        std::ifstream file({std::string(HELP)});

        if (file.is_open())
            std::cout << file.rdbuf();
    }

    const std::unordered_map<std::string, Utils::PizzaType>
        Plazza::_pizzaType =
    {
        {"regina", Utils::PizzaType::Regina},
        {"margarita", Utils::PizzaType::Margarita},
        {"americana", Utils::PizzaType::Americana},
        {"fantasia", Utils::PizzaType::Fantasia}
    };

    const std::unordered_map<std::string, Utils::PizzaSize>
        Plazza::_pizzaSize =
    {
        {"S", Utils::PizzaSize::S},
        {"M", Utils::PizzaSize::M},
        {"L", Utils::PizzaSize::L},
        {"XL", Utils::PizzaSize::XL},
        {"XXL", Utils::PizzaSize::XXL},
    };
};