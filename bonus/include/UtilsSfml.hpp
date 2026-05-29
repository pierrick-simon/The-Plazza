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
    constexpr unsigned int CHAR_SIZE = 40; 
    inline const sf::Color LIGHTGREY = sf::Color(150, 150, 150);
    inline const sf::Color DARKBLUE = sf::Color(51, 75, 99);
    inline const sf::Color LIGHTBLUE = sf::Color(135, 206, 255);
    inline const sf::Color GREEN = sf::Color(50, 255, 50);
    inline const sf::Color RED = sf::Color(255, 50, 50);
    inline const sf::Color ORANGE = sf::Color(255, 128,  0);
    inline const sf::Color BROWN = sf::Color(145, 108,  70);
    inline const sf::Color DARKBROWN = sf::Color(101, 67,  31);
    inline const sf::Color BACKGROUND_COLOR = sf::Color(50, 50, 75);

    constexpr static float GAP = 5;
    constexpr static std::size_t NB_X_KITCHEN = 5;
    constexpr static std::size_t NB_Y_KITCHEN = 2;
    constexpr static float BOX_X = WINDOW_SIZE_X / float(NB_X_KITCHEN) - GAP * 2;
    constexpr static float BOX_Y = WINDOW_SIZE_Y / float(NB_Y_KITCHEN)  - GAP * 2;

    class UtilsSfml {
        public:
            static sf::Color colorOffset(const sf::Color &color, int offset)
            {
                return sf::Color(color.r + offset, color.g + offset, color.b + offset);
            }
    };
};

#endif
