/*
** EPITECH PROJECT, 2026
** bonus
** File description:
** PresseButton
*/

#ifndef PRESSBUTTON_HPP
    #define PRESSBUTTON_HPP

    #include "AButton.hpp"
    #include "UtilsSfml.hpp"

namespace Plazza {
    class PresseButton : public AButton {
        public:
            PresseButton(sf::Font &font, unsigned int textSize,
                sf::Vector2f pos, sf::Vector2f size, std::string str, sf::Color color = LIGHTGREY)
                : AButton(ButtonType::Presse), _pos(pos), _size(size),
                    _textSize(textSize), _str(str), _color(color)
            {
                _text.setFont(font);
                _text.setCharacterSize(textSize);
                _text.setFillColor(sf::Color::Black);
                _text.setCharacterSize(_textSize);
                _text.setString(_str);
                sf::FloatRect rc = _text.getLocalBounds();
                _text.setOrigin(rc.left + rc.width / 2.0, rc.top + rc.height / 2.0);
                _text.setPosition(_pos.x + _size.x / 2.0, _pos.y + _size.y / 2.0);
                _rec.setSize(size);
                _rec.setOutlineColor(sf::Color::Black);
                _rec.setOutlineThickness(2);
                _rec.setPosition(_pos);
                setBound(_rec.getGlobalBounds());
            }

            void draw(sf::RenderWindow &win) override
            {
                if (_hover)
                    _rec.setFillColor(UtilsSfml::colorOffset(_color, -50));
                else
                    _rec.setFillColor(_color);
                win.draw(_rec);
                win.draw(_text);
            }

            void func() override
            {
                _push = !_push;
            }

            void reset() {_push = false;}
            bool getPush() {return _push;}

        private:
            sf::Vector2f _pos;
            sf::Vector2f _size;
            sf::RectangleShape _rec;
            sf::Text _text;
            unsigned int _textSize;
            std::string _str;
            sf::Color _color;
            bool _push = false;
    };
}

#endif
