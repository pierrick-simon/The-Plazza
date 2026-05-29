/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** Reception
*/

#ifndef RECEPTION_HPP
    #define RECEPTION_HPP

    #include <vector>
    #include <fstream>  
    #include <map>
    #include <string_view>
    #include <functional>
    #include <unordered_map>
    #include "../include/Utils.hpp"
    #include "../include/IPC.hpp"
    #include "UtilsSfml.hpp"
    #include "KitchenDisplay.hpp"

namespace Plazza {

    constexpr std::string_view LOG_FILE = "plazza.log";

    struct Info {
        IPC _ipc;
        std::size_t _queue;
        KitchenDisplay _display;
        bool _status;
        double _elapsed;
    };

    class Reception {
        public:
            Reception(sf::Font &font);
            ~Reception();

            void order(std::map<Utils::Pizza, std::size_t>);
            void status();
            void checkKitchens();

            void setMultiplier(double multiplier) {_multiplier = multiplier;}
            void setNbCook(double nbCook) {_nbCook = nbCook;}
            void setRestock(std::size_t restock) {_restock = restock;}

            void draw(sf::RenderWindow &win);
            void event(sf::Event &event);

        private:
            std::map<std::size_t, Info>::iterator
                openNewKitchen();
            void logMsg(std::string);
            void sendOrderToKitchen(const IPC &ipc, std::size_t,
                Utils::Pizza, std::size_t &count);
            void sendOrder(Utils::Pizza);
            void closeKitchen(std::size_t);
            void orderDone(std::size_t);
            std::vector<bool> receiveCooksInfo(IPC &ipc);
            std::unordered_map<Utils::IngredientType, std::size_t> receiveIngredientsInfo(IPC &ipc);
            void printStatus(std::size_t);

            double _multiplier = 1;
            std::size_t _nbCook = 1;
            std::size_t _restock = 1;
            std::ofstream _file;
            std::map<std::size_t, Info> _kitchenFd;
            std::unordered_map<int, std::function<void (std::size_t)>> _commands;
            sf::Clock _clock;
            sf::Vector2f _pos = {0, 0};

            sf::Font &_font;
    };
}

#endif
