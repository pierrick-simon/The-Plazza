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
};

#endif