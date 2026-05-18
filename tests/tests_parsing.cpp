/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** tests_parsing
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

static const char *testMain(std::vector<std::string> args)
{
    try {
        Plazza::Plazza plazza(args);
    } catch (Plazza::PlazzaException &e) {
        std::string *tmp = new std::string(e.what());
        return tmp->c_str();
    }
    return "No Error";
}

Test(Parsing, noArgs, .init = redirect_all_std)
{
    cr_assert_str_eq(testMain({}), "Plazza Error: Wrongs Args.");
}

Test(Parsing, nanArgs1, .init = redirect_all_std)
{
    cr_assert_str_eq(testMain({"hello", "world", "!"}), "Plazza Error: Wrongs Args.");
}

Test(Parsing, nanArgs2, .init = redirect_all_std)
{
    cr_assert_str_eq(testMain({"1", "world", "!"}), "Plazza Error: Wrongs Args.");
}

Test(Parsing, nanArgs3, .init = redirect_all_std)
{
    cr_assert_str_eq(testMain({"1", "1", "!"}), "Plazza Error: Wrongs Args.");
}

Test(Parsing, negativeArgs1, .init = redirect_all_std)
{
    cr_assert_str_eq(testMain({"-1", "1", "1"}), "Plazza Error: Wrongs Args.");
}

Test(Parsing, zeroArgs2, .init = redirect_all_std)
{
    cr_assert_str_eq(testMain({"1.0", "0", "1"}), "Plazza Error: Wrongs Args.");
}

Test(Parsing, negativeArgs3, .init = redirect_all_std)
{
    cr_assert_str_eq(testMain({"1.0", "1", "-1"}), "Plazza Error: Wrongs Args.");
}

Test(Parsing, validArgs, .init = redirect_all_std)
{
    cr_assert_str_eq(testMain({"2", "5", "2000"}), "No Error");
}