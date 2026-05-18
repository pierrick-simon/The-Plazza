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

    std::size_t Plazza::parseNumber(std::string strNb)
    {
        std::stringstream nbStream(strNb);
        std::size_t nb;
        std::string x;
        nbStream >> x >> nb;
        if (nbStream.fail() || !nbStream.eof() || x != "x" || nb == 0)
            throw NotValidNumberException(strNb);
        return nb;
    }

    std::vector<Pizza> Plazza::parsePizzaOrder(std::string order)
    {
        std::string type;
        std::string size;
        std::string strNb;
        std::stringstream tmp(order);
        tmp >> type >> size >> strNb;
        if (tmp.fail() || !tmp.eof())
            throw InvalidOrderException();
        auto findType = _pizzaType.find(type);
        if (findType == _pizzaType.end())
            throw WrongPizzaTypeException(type);
        auto findSize = _pizzaSize.find(size);
        if (findSize == _pizzaSize.end())
            throw WrongPizzaSizeException(size);
        std::vector<Pizza> pizzas;
        try {
            std::size_t nb = parseNumber(strNb);
            for (std::size_t i = 0; i < nb; i++)
                pizzas.emplace_back(
                    std::make_pair(findType->second, findSize->second));
        } catch (NotValidNumberException &e) {
            throw e;
        }
        return pizzas;
    }

    std::vector<Pizza> Plazza::parsePizzaOrders(std::string line)
    {
        std::vector<Pizza> pizza;
        std::stringstream orders(line);
        std::string segment;
        std::vector<std::string> seglist;

        while(std::getline(orders, segment, ';'))
            seglist.push_back(segment);
        for (auto order: seglist) {
            try {
                auto newPizza = parsePizzaOrder(order);
                pizza.emplace(pizza.end(), newPizza.begin(), newPizza.end());
            } catch (OrderException &e) {
                throw e;
            }
        }
        return pizza;
    }

    void Plazza::showHelp()
    {
        std::ifstream file({std::string(HELP)});

        if (file.is_open())
            std::cout << file.rdbuf();
    }

    const std::unordered_map<std::string, Plazza::PizzaType>
        Plazza::_pizzaType =
    {
        {"regina", Plazza::PizzaType::Regina},
        {"margarita", Plazza::PizzaType::Margarita},
        {"americana", Plazza::PizzaType::Americana},
        {"fantasia", Plazza::PizzaType::Fantasia}
    };

    const std::unordered_map<std::string, Plazza::PizzaSize>
        Plazza::_pizzaSize =
    {
        {"s", Plazza::PizzaSize::S},
        {"M", Plazza::PizzaSize::M},
        {"L", Plazza::PizzaSize::L},
        {"XL", Plazza::PizzaSize::XL},
        {"XXL", Plazza::PizzaSize::XXL},
    };
};