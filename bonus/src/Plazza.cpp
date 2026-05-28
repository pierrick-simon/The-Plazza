/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** Plazza
*/

#include "Plazza.hpp"

namespace Plazza {
    Plazza::Plazza() : _window(sf::RenderWindow(
        sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y, WINDOW_BITS),
        "Plazza", sf::Style::Close | sf::Style::Resize)),
        _view(sf::FloatRect(0.0, 0.0, WINDOW_SIZE_X, WINDOW_SIZE_Y))
    {
        _window.setFramerateLimit(FPS);
        _window.setView(_view);
        _rec.setSize({WINDOW_SIZE_X, WINDOW_SIZE_Y});
        _rec.setFillColor(BACKGROUND_COLOR);
    }

        void Plazza::run()
    {
        while (_window.isOpen()) {
            event();
            _window.clear(sf::Color::Black);
            _window.setView(_view);
            _window.draw(_rec);
            _window.display();
        }
    }

    void Plazza::event()
    {
        sf::Event event;
        while (_window.pollEvent(event)) {
            handleResize(event);
            if (event.type == sf::Event::Closed ||
                    (event.type == sf::Event::KeyPressed
                        && event.key.code == sf::Keyboard::Q))
                _window.close();
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
