/*
** EPITECH PROJECT, 2026
** bonus
** File description:
** Command
*/

#ifndef COMMAND_HPP
    #define COMMAND_HPP

    #include <SFML/Graphics.hpp>
    #include <unordered_map>
    #include <optional>
    #include <string_view>
    #include "UtilsSfml.hpp"
    #include "../include/Utils.hpp"
    #include "DropDownButton.hpp"
    #include "PresseButton.hpp"
    #include "../include/Reception.hpp"

namespace Plazza {
    class Command {
        public:
            Command(sf::Font &font);

            void draw(sf::RenderWindow &win);
            void event(sf::Vector2f mousePos, sf::Event &event, Reception &reception);

            bool getShow() {return _show;}
            void reset();
            
        private:
            void drawBox(sf::RenderWindow &win);
            void addCommand(Reception &reception);

            sf::RectangleShape _rec;
            sf::Text _text;
            sf::Texture _texture;
            sf::Sprite _sprite;
            sf::Clock _clock;
            DropDownButton<Utils::PizzaSize> _pizzaSizeDrop;
            DropDownButton<Utils::PizzaType> _pizzaTypeDrop;
            DropDownButton<std::size_t> _pizzaNbDrop;
            std::vector<PresseButton> _validate;

            bool _show = true;

            static const std::unordered_map<std::size_t, std::string> _nbPizza;

            constexpr static std::string_view CHIEF = "public/Chief.png";
            constexpr static float CHIEF_X = 402;
            constexpr static float CHIEF_Y = 621;
            constexpr static float TEXT_BOX_X = 750;
            constexpr static float TEXT_BOX_Y = 250;
            constexpr static float TEXT_BOX_POS_X = WINDOW_SIZE_X / 4 + CHIEF_X / 2;
            constexpr static float TEXT_BOX_POS_Y = WINDOW_SIZE_Y - CHIEF_Y / 3 * 2 - TEXT_BOX_Y;
            constexpr static float GAP = 10.0;
            constexpr static float DROPDOWN_X = (TEXT_BOX_X / 3.0) - GAP * 2.0;
            constexpr static float DROPDOWN_POS_Y = TEXT_BOX_POS_Y + TEXT_BOX_Y / 4.0 * 2.0;
            constexpr static float DROPDOWN_Y = 45.0;
            constexpr static std::string_view TEXT = "Hello, I'm the chief of this Pizzeria!\nI heard that you were ready to order\n\nDo you confirm your order ?";
    };
}
#endif
