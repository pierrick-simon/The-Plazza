/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** Plazza
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include "../include/Exception.hpp"
#include "Plazza.hpp"

namespace Plazza {
    Plazza::Plazza(std::vector<std::string> args) : _window(sf::RenderWindow(
        sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y, WINDOW_BITS),
        "Plazza", sf::Style::Close | sf::Style::Resize)),
        _view(sf::FloatRect(0.0, 0.0, WINDOW_SIZE_X, WINDOW_SIZE_Y)),
        _font(loadFromFile("public/Font.ttf")),
        _reception(_font),
        _command(_font)
    {
        if (args.size() != NBARGS) {
            throw WrongArgsException();
        }
        double multiplier;
        std::istringstream stream1(args[MULTIPLIER]);
        stream1 >> multiplier;
        std::size_t nbCook;
        std::istringstream stream2(args[NBCOOK]);
        stream2 >> nbCook;
        std::size_t restock;
        std::istringstream stream3(args[RESTOCK]);
        stream3 >> restock;
        if (stream1.fail() || !stream1.eof() || multiplier < 0
            || stream2.fail() || !stream2.eof() || nbCook == 0
            || stream3.fail() || !stream3.eof() || restock < 0)
            throw WrongArgsException();
        _reception.setMultiplier(multiplier);
        _reception.setNbCook(nbCook);
        _reception.setRestock(restock);
        _window.setFramerateLimit(FPS);
        _window.setView(_view);
        _rec.setSize({WINDOW_SIZE_X, WINDOW_SIZE_Y});
        _rec.setFillColor(BACKGROUND_COLOR);
    }

    sf::Font Plazza::loadFromFile(std::string file)
    {
        sf::Font font;
        font.loadFromFile(file);
        return font;
    }

    void Plazza::run()
    {
        while (_window.isOpen()) {
            event();
            _window.clear(sf::Color::Black);
            _window.setView(_view);
            _window.draw(_rec);
            _reception.draw(_window);
            if (_command.getShow())
                _command.draw(_window);
            _window.display();
            _reception.checkKitchens();
        }
    }

    void Plazza::event()
    {
        sf::Event event;
        sf::Vector2f mousePos = _window.mapPixelToCoords(sf::Mouse::getPosition(_window));
        while (_window.pollEvent(event)) {
            if (_command.getShow())
                _command.event(mousePos, event, _reception);
            handleResize(event);
            _reception.event(event);
            if (event.type == sf::Event::Closed ||
                    (event.type == sf::Event::KeyPressed
                        && event.key.code == sf::Keyboard::Escape))
                _window.close();
            if (event.type == sf::Event::KeyPressed
                && event.key.code == sf::Keyboard::N)
                _command.reset();
        }
    }

    void Plazza::handleResize(sf::Event event)
    {
        if (event.type != sf::Event::Resized)
            return;
        const float gameW = static_cast<float>(WINDOW_SIZE_X);
        const float gameH = static_cast<float>(WINDOW_SIZE_Y);
        float windowRatio = static_cast<float>(_window.getSize().x) /
                            static_cast<float>(_window.getSize().y);
        float viewRatio = gameW / gameH;
        sf::Vector2f size = {1, 1};
        sf::Vector2f pos = {0, 0};

        if (windowRatio >= viewRatio) {
            size.x = viewRatio / windowRatio;
            pos.x = (1.0 - size.x) / 2.0;
        } else {
            size.y = windowRatio / viewRatio;
            pos.y = (1.0 - size.y) / 2.0;
        }
        _view.setViewport(sf::FloatRect(pos.x, pos.y, size.x, size.y));
        _window.setView(_view);
    }
}
