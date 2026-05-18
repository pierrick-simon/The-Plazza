/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** Exception
*/

#ifndef PLAZZAEXCEPTION_HPP
    #define PLAZZAEXCEPTION_HPP

#include <exception>
#include <string>

namespace Plazza {
    class PlazzaException : public std::exception {
        public:
            PlazzaException(std::string str) : _str("Plazza Error: " + str) {};

            virtual const char *what() const noexcept override
                    { return _str.c_str(); };
        private:
            std::string _str;
    };

    class WrongArgsException : public PlazzaException {
        public:
            WrongArgsException() : PlazzaException("Wrongs Args.") {};
    };

    class ShellException : public PlazzaException {
        public:
            ShellException(std::string str)
                : PlazzaException("Shell Error: " + str) {};
    };

    class OrderException : public ShellException {
        public:
            OrderException(std::string str)
                : ShellException("Order Error: " + str) {};
    };

    class WrongPizzaTypeException : public OrderException {
        public:
            WrongPizzaTypeException(std::string str)
                : OrderException("The pizza " + str + " is not available.") {};
    };

    class WrongPizzaSizeException : public OrderException {
        public:
            WrongPizzaSizeException(std::string str)
                : OrderException("The size " + str + " doesn't exist.") {};
    };

    class NotValidNumberException : public OrderException {
        public:
            NotValidNumberException(std::string str)
                : OrderException("The number " + str + " is not valid.") {};
    };

    class InvalidOrderException : public OrderException {
        public:
            InvalidOrderException()
                : OrderException("Invalide Order. TYPE SIZE NUMBER.") {};
    };

    class WrongCommandException : public ShellException {
        public:
            WrongCommandException() : ShellException("Wrong Command!") {};
    };
};

#endif