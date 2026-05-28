/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** Plazza
*/

#ifndef PLAZZA_HPP
    #define PLAZZA_HPP

    #include <SFML/Graphics.hpp>
    #include "UtilsSfml.hpp"

namespace Plazza {
    class Plazza {
        public:
            Plazza();
            void run();

        private:
            void event();
            void handleResize(sf::Event event);

            sf::RenderWindow _window;
            sf::View _view;
            sf::RectangleShape _rec;
    };
}

#endif
