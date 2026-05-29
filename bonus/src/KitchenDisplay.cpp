/*
** EPITECH PROJECT, 2026
** bonus
** File description:
** KitchenDisplay
*/

#include "KitchenDisplay.hpp"

namespace Plazza {
    KitchenDisplay::KitchenDisplay(sf::Font &font, std::size_t id, std::size_t nbCook)
        : _id(id), _nbCook(nbCook), _info({std::vector<bool>(nbCook), {}})
    {
        _text.setFont(font);
        _pos = {0, 0};
        _ovenTexture.loadFromFile(std::string(OVEN));
        _oven.setTexture(_ovenTexture);
        _oven.setTextureRect({0, 0, OVEN_RECT_X, OVEN_RECT_Y});
        _oven.setScale({OVEN_SCALE, OVEN_SCALE});
        _chefTexture.loadFromFile(std::string(CHEF));
        _chef.setTexture(_chefTexture);
        _chef.setScale(CHEF_SCALE, CHEF_SCALE);
        _floorTexture.loadFromFile(std::string(FLOOR));
        _floor.setTexture(_floorTexture);
        _floor.setScale(FLOOR_SCALE_X, FLOOR_SCALE_Y);
        _wallTexture.loadFromFile(std::string(WALL));
        _wall.setTexture(_wallTexture);
        _wall.setScale(WALL_SCALE_X, WALL_SCALE_Y);
        for (std::size_t i = 0; i < _nbCook; i++)
            _cooks.push_back({0, 0, {}});
        _ingredient.setScale(INGREDIANT_SCALE, INGREDIANT_SCALE);
        _ingredient.setOrigin(INGREDIANT_REAL_SIZE / 2.0, INGREDIANT_REAL_SIZE / 2.0);
        _ingredientTexture.emplace(Utils::DOUGH, sf::Texture());
        _ingredientTexture.at(Utils::DOUGH).loadFromFile("public/dough.png");
        _ingredientTexture.emplace(Utils::TOMATO, sf::Texture());
        _ingredientTexture.at(Utils::TOMATO).loadFromFile("public/tomato.png");
        _ingredientTexture.emplace(Utils::GRUYERE, sf::Texture());
        _ingredientTexture.at(Utils::GRUYERE).loadFromFile("public/cheese.png");
        _ingredientTexture.emplace(Utils::HAM, sf::Texture());
        _ingredientTexture.at(Utils::HAM).loadFromFile("public/ham.png");
        _ingredientTexture.emplace(Utils::MUSHROOMS, sf::Texture());
        _ingredientTexture.at(Utils::MUSHROOMS).loadFromFile("public/mushroom.png");
        _ingredientTexture.emplace(Utils::EGGPLANT, sf::Texture());
        _ingredientTexture.at(Utils::EGGPLANT).loadFromFile("public/eggplant.png");
        _ingredientTexture.emplace(Utils::GOAT_CHEESE, sf::Texture());
        _ingredientTexture.at(Utils::GOAT_CHEESE).loadFromFile("public/goat.png");
        _ingredientTexture.emplace(Utils::STEAK, sf::Texture());
        _ingredientTexture.at(Utils::STEAK).loadFromFile("public/steak.png");
        _ingredientTexture.emplace(Utils::CHIEF_LOVE, sf::Texture());
        _ingredientTexture.at(Utils::CHIEF_LOVE).loadFromFile("public/heart.png");
        _clock.restart();
    }

    void KitchenDisplay::draw(sf::RenderWindow &win, sf::Vector2f pos)
    {
        _oven.setTexture(_ovenTexture);
        _chef.setTexture(_chefTexture);
        _floor.setTexture(_floorTexture);
        _wall.setTexture(_wallTexture);
        _pos = pos;
        auto elapsed = _clock.getElapsedTime().asMilliseconds();
        _ovenElapsed += elapsed;
        for (auto &cook: _cooks)
            cook._elapsed += elapsed;
        _clock.restart();
        drawBox(win);
        drawTop(win);
        drawBottom(win);
        drawShelf(win);
        drawChef(win);
        drawOven(win);
    }

    void KitchenDisplay::drawBox(sf::RenderWindow &win)
    {
        _rec.setOrigin(0, 0);
        _rec.setPosition(_pos);
        _rec.setSize({BOX_X, BOX_Y});
        _rec.setFillColor(sf::Color::White);
        win.draw(_rec);
        _floor.setPosition({_pos.x, _pos.y + BOX_Y - COOK_BOX_Y - FLOOR_HEIGHT});
        win.draw(_floor);
        _wall.setPosition({_pos.x, _pos.y + TITLE_BOX_Y});
        win.draw(_wall);
    }

    void KitchenDisplay::drawTop(sf::RenderWindow &win)
    {
        _rec.setOrigin(0, 0);
        _rec.setPosition(_pos);
        _rec.setSize({BOX_X, TITLE_BOX_Y});
        bool active = false;
        bool semiActive = false;
        for (auto cook: _info._cook) {
            active |= cook;
            if (!cook)
                semiActive = true;
        }
        if (semiActive && active)
            _rec.setFillColor(ORANGE);
        else if (active)
            _rec.setFillColor(GREEN);
        else
            _rec.setFillColor(RED);
        win.draw(_rec);
        _text.setString("Kitchen #" + std::to_string(_id));
        _text.setCharacterSize(TEXT_SIZE);
        _text.setStyle(sf::Text::Bold);
        _text.setFillColor(sf::Color::Black);
        sf::FloatRect rc = _text.getLocalBounds();
        _text.setOrigin(rc.left + rc.width / 2.0, rc.top + rc.height / 2.0);
        _text.setPosition(sf::Vector2f(_pos.x + BOX_X / 2.0, _pos.y + TITLE_BOX_Y / 2.0));
        win.draw(_text);
    }

    void KitchenDisplay::drawBottom(sf::RenderWindow &win)
    {
        _rec.setOrigin(0, 0);
        _rec.setPosition({_pos.x, _pos.y + BOX_Y - COOK_BOX_Y});
        _rec.setSize({BOX_X, COOK_BOX_Y});
        _rec.setFillColor(BROWN);
        win.draw(_rec);
        _cir.setRadius(COOK_RADIUS);
        _cir.setOrigin(COOK_RADIUS, COOK_RADIUS);
        std::size_t active = 0;
        for (std::size_t i = 0; i < _info._cook.size(); i++) {
            _cir.setPosition(_pos.x + (BOX_X - COOK_RADIUS * 2.0) /
                float(_info._cook.size() + 1) * float(i + 1) + COOK_RADIUS, _pos.y + BOX_Y - COOK_BOX_Y / 3.0);
            if (_info._cook[i]) {
                _cir.setFillColor(GREEN);
                active++;
            } else
                _cir.setFillColor(LIGHTGREY);
            win.draw(_cir);
        }
        _text.setString("Cook : " + std::to_string(active) + " / " + std::to_string(_info._cook.size()));
        _text.setCharacterSize(TEXT_SIZE);
        _text.setStyle(sf::Text::Regular);
        _text.setFillColor(sf::Color::Black);
        _text.setOrigin(0, 0);
        _text.setPosition(sf::Vector2f(_pos.x + GAP, _pos.y + BOX_Y - COOK_BOX_Y + GAP));
        win.draw(_text);
        _text.setString("Queue : " + std::to_string(_info._queue) + " / " + std::to_string(_nbCook * 2));
        _text.setCharacterSize(TEXT_SIZE);
        _text.setStyle(sf::Text::Regular);
        _text.setFillColor(sf::Color::Black);
        sf::FloatRect rc = _text.getLocalBounds();
        _text.setOrigin(rc.left + rc.width, 0);
        _text.setPosition(sf::Vector2f(_pos.x + BOX_X - GAP, _pos.y + BOX_Y - COOK_BOX_Y + GAP));
        win.draw(_text);
    }

    void KitchenDisplay::drawShelf(sf::RenderWindow &win)
    {
        _rec.setOrigin(SHELF_X / 2.0, 0);
        _rec.setPosition(sf::Vector2f(_pos.x + BOX_X / 2.0, _pos.y + SHELF_POS_Y));
        _rec.setSize({SHELF_X, SHELF_Y});
        _rec.setFillColor(BROWN);
        win.draw(_rec);
        auto iter = _info._ingredient.begin();
        float size = (SHELF_X - GAP * 2.0 - SMALL_GAP * float(_info._ingredient.size() - 1)) / float(_info._ingredient.size()); 
        _rec.setOrigin(0, 0);
        _rec.setOutlineColor(sf::Color::Black);
        _rec.setOutlineThickness(1);
        for (size_t i = 0; i < _info._ingredient.size(); i++) {
            _rec.setSize({size, ITEM_Y});
            _rec.setPosition(_pos.x + (BOX_X - SHELF_X) / 2 + GAP + (size + SMALL_GAP) * float(i), _pos.y + SHELF_POS_Y - ITEM_Y);
            _rec.setFillColor(LIGHTGREY);
            win.draw(_rec);
            float percentage = float(iter->second) / 5.0;
            _rec.setSize({size, ITEM_Y * percentage});
            _rec.setPosition(_pos.x + (BOX_X - SHELF_X) / 2 + GAP + (size + SMALL_GAP) * float(i), _pos.y + SHELF_POS_Y - ITEM_Y * percentage);
            if (percentage > 2.0 / 3.0)
                _rec.setFillColor(GREEN);
            else if (percentage > 1.0 / 3.0)
                _rec.setFillColor(ORANGE);
            else
                _rec.setFillColor(RED);
            win.draw(_rec);
            auto find = _ingredientTexture.find(iter->first);
            if (find != _ingredientTexture.end()) {
                _ingredient.setTexture(find->second);
                _ingredient.setPosition(_pos.x + (BOX_X - SHELF_X) / 2 + GAP + (size + SMALL_GAP) * float(i) + size / 2.0, _pos.y + SHELF_POS_Y - ITEM_Y / 2.0);
                win.draw(_ingredient);
            }
            iter++;
        }
        _rec.setOutlineThickness(0);
    }

    void KitchenDisplay::drawOven(sf::RenderWindow &win)
    {
        bool active = false;
        for (auto cook: _info._cook)
            active |= cook;
        if (active) {
            if (_ovenElapsed > 100) {
                _ovenElapsed = 0;
                _ovenCurrent++;
                if (_ovenCurrent == OVEN_NB_SPRITE)
                    _ovenCurrent = 0;
                _oven.setTextureRect({OVEN_RECT_X * _ovenCurrent, 0, OVEN_RECT_X, OVEN_RECT_Y});
            }
        } else {
            _ovenCurrent = 0;
            _oven.setTextureRect({0, 0, OVEN_RECT_X, OVEN_RECT_Y});  
        }
        _oven.setPosition(_pos.x + OVEN_POS_X, _pos.y + FLOOR_POS_Y - OVEN_RECT_Y * OVEN_SCALE);
        win.draw(_oven);
    }

    void KitchenDisplay::drawChef(sf::RenderWindow &win)
    {
        for (std::size_t i = 0; i < _cooks.size(); i++) {
            if (!_info._cook[i])
                continue;
            if (_cooks[i]._elapsed > 100) {
                _cooks[i]._current++;
                if (_cooks[i]._current == CHEF_NB_SPRITE)
                    _cooks[i]._current = 0;
                _cooks[i]._elapsed = 0;
            }
            _cooks[i]._pos = sf::Vector2f(_pos.x + float(i) / float(_cooks.size()) * CHEF_WIDTH + CHEF_MIN_POS_X, _pos.y + FLOOR_POS_Y);
            _chef.setOrigin(sf::Vector2f(CHEF_RECT_X / 2.0, CHEF_RECT_Y * CHEF_SCALE + 50));
            _chef.setPosition(_cooks[i]._pos);
            _chef.setTextureRect({CHEF_RECT_X * _cooks[i]._current, 0, CHEF_RECT_X, CHEF_RECT_Y});
            win.draw(_chef);
        }
    }
};