/*
** EPITECH PROJECT, 2026
** bonus
** File description:
** AButton
*/


#ifndef ABUTTONHPP
    #define ABUTTONHPP

    #include <SFML/Graphics.hpp>

namespace Plazza {

    enum class ButtonType {
        DropDown,
        Presse
    };

    class AButton {
        public:
            AButton(ButtonType type) : _hover(false), _type(type) {};
            virtual ~AButton() = default;

            bool isHover(sf::Vector2f mousePos);
            void click(sf::Vector2f mousePos, sf::Event event);

            bool getHover() {return _hover;}
            void setBound(sf::FloatRect bound) {_bound = bound;}
            ButtonType getType() {return _type;}

            virtual void func() = 0;
            virtual void draw(sf::RenderWindow &window) = 0;

        protected:
            sf::FloatRect _bound;
            bool _hover;
            ButtonType _type;
    };
}

#endif