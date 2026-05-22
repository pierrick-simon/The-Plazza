/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** tests_parse_order
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <unistd.h>
#include <fcntl.h>

#include "Exception.hpp"
#include "Plazza.hpp"

static void redirect_all_std()
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

static const char *testErrorMain(std::string line)
{
    try {
        Plazza::Plazza plazza({"1", "1", "1"});
        plazza.parsePizzaOrders(line);
    } catch (Plazza::PlazzaException &e) {
        std::string *tmp = new std::string(e.what());
        return tmp->c_str();
    }
    return "No Error";
}

static bool testSuccessMain(std::string line, std::map<Plazza::Utils::Pizza, std::size_t> test)
{
    try {
        Plazza::Plazza plazza({"1", "1", "1"});
        auto pizzas = plazza.parsePizzaOrders(line);
        cr_assert_eq(pizzas.size(), test.size());
        auto iterPizza = pizzas.begin();
        auto iterTest = test.begin();
        for (; iterPizza != pizzas.end() && iterTest != test.end(); iterPizza++, iterTest++) {
            cr_assert_eq(iterPizza->first.first, iterTest->first.first);
            cr_assert_eq(iterPizza->first.second, iterTest->first.second);
            cr_assert_eq(iterPizza->second, iterTest->second);
        }
    } catch (Plazza::PlazzaException &e) {
        std::string *tmp = new std::string(e.what());
        return false;
    }
    return true;
}

Test(PizzaOrder, InvlaidOrder)
{
    cr_assert_str_eq(testErrorMain("Hello World!"), "Plazza Error: Shell Error: Order Error: Invalide Order. TYPE SIZE NUMBER.");
}

Test(PizzaOrder, WrongPizzaType)
{
    cr_assert_str_eq(testErrorMain("Chicken S x1"), "Plazza Error: Shell Error: Order Error: The pizza chicken is not available.");
}

Test(PizzaOrder, WrongPizzaSize)
{
    cr_assert_str_eq(testErrorMain("regina V x1"), "Plazza Error: Shell Error: Order Error: The size V doesn't exist.");
}

Test(PizzaOrder, NotValidNumber)
{
    cr_assert_str_eq(testErrorMain("regina M x0"), "Plazza Error: Shell Error: Order Error: The number x0 is not valid.");
}

Test(PizzaOrder, SingleOrder)
{
    std::map<Plazza::Utils::Pizza, std::size_t> test = {
        {std::make_pair(Plazza::Utils::Fantasia, Plazza::Utils::M), 3}
    };

    cr_assert(testSuccessMain("fantasia M x3", test));
}

Test(PizzaOrder, MultipleOrder)
{
    std::map<Plazza::Utils::Pizza, std::size_t> test = {
        {std::make_pair(Plazza::Utils::Regina, Plazza::Utils::XXL), 12},
        {std::make_pair(Plazza::Utils::Fantasia, Plazza::Utils::M), 3},
        {std::make_pair(Plazza::Utils::Margarita, Plazza::Utils::S), 1},
    };

    cr_assert(testSuccessMain("regina XXL x2; fantasia M x3; margarita S x1; regina XXL x10", test));
}