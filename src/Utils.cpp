/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** Utils
*/

#include <algorithm>
#include "Utils.hpp"
#include "Exception.hpp"

namespace Plazza {

    Utils::PizzaType Utils::getType(std::string str)
    {
        std::transform(str.begin(), str.end(), str.begin(),
            [](unsigned char c) {return std::tolower(c);});
        for (auto [key, value]: _strPizzaType) {
            if (value == str)
                return key;
        }
        throw WrongPizzaTypeException(str);
    }

    Utils::PizzaSize Utils::getSize(std::string str)
    {
        std::transform(str.begin(), str.end(), str.begin(),
            [](unsigned char c) {return std::toupper(c);});
        for (auto [key, value]: _strPizzaSize) {
            if (value == str)
                return key;
        }
        throw WrongPizzaSizeException(str);
    }

    std::string Utils::typeToString(PizzaType type)
    {
        return _strPizzaType.at(type);
    }

    std::string Utils::sizeToString(PizzaSize size)
    {
        return _strPizzaSize.at(size);
    }

    std::string Utils::pizzaToString(Pizza pizza)
    {
        return Utils::typeToString(pizza.first)
            + " " + Utils::sizeToString(pizza.second);
    }

    std::ostream &operator<<(std::ostream &os, const Utils::Pizza &pizza)
    {
        os << Utils::typeToString(pizza.first)
        << " "
        << Utils::sizeToString(pizza.second);

        return os;
    }

    const std::unordered_map<Utils::PizzaType, std::string>
        Utils::_strPizzaType =
    {
        {Utils::PizzaType::Regina, "regina"},
        {Utils::PizzaType::Margarita, "margarita"},
        {Utils::PizzaType::Americana, "americana"},
        {Utils::PizzaType::Fantasia, "fantasia"}
    };

    const std::unordered_map<Utils::PizzaSize, std::string>
        Utils::_strPizzaSize =
    {
        {Utils::PizzaSize::S, "S"},
        {Utils::PizzaSize::M, "M"},
        {Utils::PizzaSize::L, "L"},
        {Utils::PizzaSize::XL, "XL"},
        {Utils::PizzaSize::XXL, "XXL"},
    };

    const std::unordered_map<Utils::IngredientType, std::string>
        Utils::_strIngredientType =
    {
        {Utils::IngredientType::DOUGH, "Dough"},
        {Utils::IngredientType::TOMATO, "Tomato"},
        {Utils::IngredientType::GRUYERE, "Gruyere"},
        {Utils::IngredientType::HAM, "Ham"},
        {Utils::IngredientType::MUSHROOMS, "Mushrooms"},
        {Utils::IngredientType::STEAK, "Steak"},
        {Utils::IngredientType::EGGPLANT, "Eggplant"},
        {Utils::IngredientType::GOAT_CHEESE, "Goat Cheese"},
        {Utils::IngredientType::CHIEF_LOVE, "Chief Love"},
    };
}
