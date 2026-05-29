/*
** EPITECH PROJECT, 2026
** bonus
** File description:
** Command
*/

#include "Command.hpp"

namespace Plazza {
    Command::Command(sf::Font &font) :
        _pizzaNbDrop(font, CHAR_SIZE, sf::Vector2f(TEXT_BOX_POS_X + GAP, DROPDOWN_POS_Y), sf::Vector2f(DROPDOWN_X, DROPDOWN_Y), _nbPizza),
        _pizzaSizeDrop(font, CHAR_SIZE, sf::Vector2f(TEXT_BOX_POS_X + GAP * 2.0 + DROPDOWN_X, DROPDOWN_POS_Y), sf::Vector2f(DROPDOWN_X, DROPDOWN_Y), Utils::_strPizzaSize),
        _pizzaTypeDrop(font, CHAR_SIZE, sf::Vector2f(TEXT_BOX_POS_X + GAP * 3.0 + DROPDOWN_X * 2.0, DROPDOWN_POS_Y), sf::Vector2f(DROPDOWN_X, DROPDOWN_Y), Utils::_strPizzaType)
    {
        _validate.push_back(PresseButton(font, CHAR_SIZE, sf::Vector2f(TEXT_BOX_POS_X + 650, TEXT_BOX_POS_Y + TEXT_BOX_Y / 4.0 * 3.0), sf::Vector2f(80, 40), "YES", GREEN));
        _validate.push_back(PresseButton(font, CHAR_SIZE, sf::Vector2f(TEXT_BOX_POS_X + 550, TEXT_BOX_POS_Y + TEXT_BOX_Y / 4.0 * 3.0), sf::Vector2f(80, 40), "NO", RED));
        _text.setFont(font);
        _texture.loadFromFile(std::string(CHIEF));
        _sprite.setTexture(_texture);
        _sprite.setOrigin(CHIEF_X / 2, CHIEF_Y);
        _sprite.setPosition(WINDOW_SIZE_X / 4, WINDOW_SIZE_Y);
        _clock.restart();
    }

    void Command::draw(sf::RenderWindow &win)
    {
        drawBox(win);
        for (auto &validate: _validate)
            validate.draw(win);
        _pizzaSizeDrop.draw(win);
        _pizzaTypeDrop.draw(win);
        _pizzaNbDrop.draw(win);
        win.draw(_sprite);
    }

    void Command::event(sf::Vector2f mousePos, sf::Event &event, Reception &reception)
    {
        _pizzaNbDrop.event(mousePos, event);
        _pizzaSizeDrop.event(mousePos, event);
        _pizzaTypeDrop.event(mousePos, event);
        std::size_t i = 0;
        if (_pizzaTypeDrop.getPush()) {
            _clock.restart();
            return;
        }
        if (_clock.getElapsedTime().asMilliseconds() < 500)
            return;
        for (auto &validate: _validate) {
            validate.click(mousePos, event);
            if (validate.getPush()) {
                if (i == 0)
                    addCommand(reception);
                _show = false;
            }
            i++;
        }
    }

    void Command::addCommand(Reception &reception)
    {
        auto type = _pizzaTypeDrop.getSelect();
        auto size = _pizzaSizeDrop.getSelect();
        auto nb = _pizzaNbDrop.getSelect();
        if (type && size && nb) {
            std::map<Plazza::Utils::Pizza, std::size_t> map;
            map.emplace(std::make_pair(std::make_pair(*type, *size), *nb));
            reception.order(map);
        }
    }

    void Command::reset()
    {
        _show = true;
        _pizzaNbDrop.reset();
        _pizzaTypeDrop.reset();
        _pizzaSizeDrop.reset();
        for (auto &validate: _validate)
            validate.reset();
    }

    void Command::drawBox(sf::RenderWindow &win)
    {
        _rec.setFillColor(sf::Color::White);
        _rec.setSize({TEXT_BOX_X, TEXT_BOX_Y});
        _rec.setPosition({TEXT_BOX_POS_X, TEXT_BOX_POS_Y});
        _rec.setOutlineColor(sf::Color::Black);
        _rec.setOutlineThickness(5);
        win.draw(_rec);
        _text.setCharacterSize(CHAR_SIZE);
        _text.setFillColor(sf::Color::Black);
        _text.setString(std::string(TEXT));
        sf::FloatRect rc = _text.getLocalBounds();
        _text.setOrigin(0, rc.top + rc.height / 2.0);
        _text.setPosition({TEXT_BOX_POS_X + 10, TEXT_BOX_POS_Y + TEXT_BOX_Y / 2});
        win.draw(_text);
    }

    const std::unordered_map<std::size_t, std::string> Command::_nbPizza =
    {
        {500, "500"},
        {100, "100"},
        {50, "50"},
        {10, "10"},
        {1, "1"},
    };
};
