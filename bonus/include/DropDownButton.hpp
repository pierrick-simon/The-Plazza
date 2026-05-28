/*
** EPITECH PROJECT, 2026
** bonus
** File description:
** DropDownButton
*/

#ifndef DROPDOWNBUTTON_HPP
    #define DROPDOWNBUTTON_HPP

    #include <unordered_map>
    #include <optional>
    #include "AButton.hpp"
    #include "PresseButton.hpp"
    #include "UtilsSfml.hpp"

namespace Plazza {
    template <typename T>
    class DropDownButton : public AButton {
        public:
            DropDownButton(sf::Font &font, unsigned int textSize, sf::Vector2f pos,
                sf::Vector2f size, const std::unordered_map<T, std::string> &map)
                : AButton(ButtonType::DropDown), _pos(pos), _size(size),
                    _textSize(textSize)
            {
                std::size_t i = 1;
                for (const auto &info: map) {
                    _map.insert(std::make_pair(info.first,
                        std::make_pair(info.second,
                            PresseButton(font, textSize, {_pos.x, _pos.y + _size.y * i}, _size, info.second))));
                    i++;
                }
                _text.setFont(font);
                _text.setCharacterSize(textSize);
                _text.setFillColor(sf::Color::Black);
                _rec.setSize(size);
                _rec.setFillColor(LIGHTGREY);
                _rec.setOutlineColor(sf::Color::Black);
                _rec.setOutlineThickness(2);
                _rec.setPosition(_pos);
                setBound(_rec.getGlobalBounds());
            }

            void event(sf::Vector2f mousePos, sf::Event &event)
            {
                click(mousePos, event);
                if (_push) {
                    for (auto &info: _map) {
                        info.second.second.click(mousePos, event);
                        if (info.second.second.getPush()) {
                            info.second.second.reset();
                            _push = false;
                            _select = info.first;
                            break;
                        }
                    }
                }
            }

            void draw(sf::RenderWindow &win) override
            {
                if (_hover)
                    _rec.setFillColor(UtilsSfml::colorOffset(LIGHTGREY, -50));
                else
                    _rec.setFillColor(LIGHTGREY);
                win.draw(_rec);
                std::string str = "---";
                if (_select) {
                    auto find = _map.find(*_select);
                    if (find != _map.end())
                        str = find->second.first;
                }
                _text.setCharacterSize(_textSize);
                _text.setString(str);
                _text.setStyle(sf::Text::Regular);
                sf::FloatRect rc = _text.getLocalBounds();
                _text.setOrigin(rc.left + rc.width / 2.0, rc.top + rc.height / 2.0);
                _text.setPosition(_pos.x + _size.x / 2.0, _pos.y + _size.y / 2.0);
                win.draw(_text);
                _text.setCharacterSize(_size.y / 2.0);
                _text.setStyle(sf::Text::Bold);
                _text.setString(">");
                rc = _text.getLocalBounds();
                _text.setOrigin(rc.left + rc.width / 2.0, rc.top + rc.height / 2.0);
                _text.setPosition(_pos.x + _size.y / 4.0, _pos.y + _size.y / 2.0);
                if (_push) {
                    _text.setRotation(90);
                    for (auto info: _map)
                        info.second.second.draw(win);
                } else {
                    _text.setRotation(-90);
                }
                win.draw(_text);
                _text.setRotation(0);
            }

            void func() override
            {
                _push = !_push;
            }

            void reset()
            {
                _select = std::nullopt;
                for (auto &info: _map)
                    info.second.second.reset();
            }

            std::optional<T> getSelect() {return _select;}

        private:
            sf::Vector2f _pos;
            sf::Vector2f _size;
            sf::RectangleShape _rec;
            sf::Text _text;
            unsigned int _textSize;
            std::unordered_map<T, std::pair<std::string, PresseButton>> _map;
            std::optional<T> _select;
            bool _push = false;
    };
}

#endif
