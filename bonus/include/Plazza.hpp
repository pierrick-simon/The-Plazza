/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** Plazza
*/

#ifndef PLAZZA_HPP
    #define PLAZZA_HPP

    #include <SFML/Graphics.hpp>
    #include <vector>
    #include <string>
    #include "UtilsSfml.hpp"
    #include "../include/Reception.hpp"
    #include "Command.hpp"

namespace Plazza {
    class Plazza {
        public:

            enum Args {
                MULTIPLIER,
                NBCOOK,
                RESTOCK,
                NBARGS
            };

            Plazza(std::vector<std::string> args);
            void run();

        private:
            void event();
            void handleResize(sf::Event event);
            sf::Font loadFromFile(std::string file);

            Reception _reception;

            sf::RenderWindow _window;
            sf::View _view;
            sf::RectangleShape _rec;
            sf::Font _font;

            Command _command;
    };
}

#endif
