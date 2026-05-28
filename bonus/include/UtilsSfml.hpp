/*
** EPITECH PROJECT, 2026
** Plazza
** File description:
** UtilsSfml
*/

#ifndef UTILSSFML_HPP
    #define UTILSSFML_HPP

    #include <SFML/Graphics.hpp>

namespace Plazza {
    constexpr std::size_t FPS = 120;
    constexpr unsigned int WINDOW_SIZE_X = 1920;
    constexpr unsigned int WINDOW_SIZE_Y = 1080;
    constexpr unsigned int WINDOW_BITS = 32;
    inline const sf::Color LIGHTGREY = sf::Color(150, 150, 150);
    inline const sf::Color DARKBLUE = sf::Color(51, 75, 99);
    inline const sf::Color BACKGROUND_COLOR = sf::Color(50, 50, 75);
};

#endif
