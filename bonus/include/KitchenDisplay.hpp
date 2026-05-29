/*
** EPITECH PROJECT, 2026
** bonus
** File description:
** KitchenDisplay
*/

#ifndef KITCHENDISPLAY_HPP
    #define KITCHENDISPLAY_HPP

    #include <SFML/Graphics.hpp>
    #include <unordered_map>
    #include <string_view>
    #include "UtilsSfml.hpp"
    #include "../include/Utils.hpp"

namespace Plazza {

    struct KitchenInfo {
        std::vector<bool> _cook;
        std::unordered_map<Utils::IngredientType, std::size_t> _ingredient;
        std::size_t _queue;
    };

    struct CookInfo {
        double _elapsed;
        int _current;
        sf::Vector2f _pos;
        int _forward;
    };

    class KitchenDisplay {
        public:
            KitchenDisplay(sf::Font &font, std::size_t id, std::size_t nbCook);

            void draw(sf::RenderWindow &win, sf::Vector2f pos);

            void update(KitchenInfo info) {_info = info;}

        private:
            void drawBox(sf::RenderWindow &win);
            void drawTop(sf::RenderWindow &win);
            void drawBottom(sf::RenderWindow &win);
            void drawShelf(sf::RenderWindow &win);
            void drawOven(sf::RenderWindow &win);
            void drawChef(sf::RenderWindow &win);

            KitchenInfo _info;
            sf::Vector2f _pos;
            sf::RectangleShape _rec;
            sf::CircleShape _cir;
            sf::Text _text;
            sf::Texture _ovenTexture;
            sf::Sprite _oven;
            int _ovenCurrent = 0;
            std::size_t _id;
            std::size_t _nbCook;
            double _ovenElapsed;
            sf::Clock _clock;
            sf::Texture _chefTexture;
            sf::Sprite _chef;
            sf::Texture _floorTexture;
            sf::Sprite _floor;
            sf::Texture _wallTexture;
            sf::Sprite _wall;
            std::vector<CookInfo> _cooks;
            std::unordered_map<Utils::IngredientType, sf::Texture> _ingredientTexture;
            sf::Sprite _ingredient;

            constexpr static unsigned int TEXT_SIZE = 20;
            constexpr static float GAP = 5;
            constexpr static float SMALL_GAP = 1;
            constexpr static float BOX_X = WINDOW_SIZE_X / 5 - GAP * 2;
            constexpr static float BOX_Y = WINDOW_SIZE_Y / 2  - GAP * 2;
            constexpr static float TITLE_BOX_Y = 50;
            constexpr static float COOK_BOX_Y = 75;
            constexpr static float COOK_RADIUS = 10;
            constexpr static float SHELF_POS_Y = TITLE_BOX_Y + 125;
            constexpr static float SHELF_Y = 15;
            constexpr static float SHELF_X = BOX_X * 0.8;
            constexpr static float ITEM_Y = 75;

            constexpr static float FLOOR_POS_Y = BOX_Y - COOK_BOX_Y - 25;
            constexpr static std::string_view OVEN = "public/Oven.png";
            constexpr static std::size_t OVEN_NB_SPRITE = 5;
            constexpr static int OVEN_RECT_X = 800 / OVEN_NB_SPRITE;
            constexpr static int OVEN_RECT_Y = 160;
            constexpr static float OVEN_SCALE = 0.5;
            constexpr static float OVEN_POS_X = BOX_X - GAP - OVEN_RECT_X * OVEN_SCALE;

            constexpr static std::string_view CHEF = "public/chef.png";
            constexpr static std::size_t CHEF_NB_SPRITE = 6;
            constexpr static float CHEF_SCALE = 0.5;
            constexpr static int CHEF_RECT_X = 930 / CHEF_NB_SPRITE;
            constexpr static int CHEF_RECT_Y = 600;
            constexpr static float CHEF_MIN_POS_X = GAP + CHEF_RECT_X * CHEF_SCALE / 2.0;
            constexpr static float CHEF_MAX_POS_X = 350 - CHEF_RECT_X * CHEF_SCALE / 2.0;
            constexpr static float CHEF_WIDTH = CHEF_MAX_POS_X - CHEF_MIN_POS_X;
            constexpr static float CHEF_WALK = 10;

            constexpr static std::string_view FLOOR = "public/floor.jpg";
            constexpr static float FLOOR_HEIGHT = 100;
            constexpr static float FLOOR_SCALE_X = BOX_X / 543;
            constexpr static float FLOOR_SCALE_Y = FLOOR_HEIGHT / 360;

            constexpr static std::string_view WALL = "public/wall.jpg";
            constexpr static float WALL_HEIGHT = BOX_Y - TITLE_BOX_Y - FLOOR_HEIGHT - COOK_BOX_Y;
            constexpr static float WALL_SCALE_X = BOX_X / 638;
            constexpr static float WALL_SCALE_Y = WALL_HEIGHT / 350;

            constexpr static float INGREDIANT_SIZE = 25.0;
            constexpr static float INGREDIANT_REAL_SIZE = 240.0;
            constexpr static float INGREDIANT_SCALE = INGREDIANT_SIZE / INGREDIANT_REAL_SIZE;
    };
}

#endif
