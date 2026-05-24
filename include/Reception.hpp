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
    #include "Utils.hpp"
    #include "IPC.hpp"

namespace Plazza {

    constexpr std::string_view LOG_FILE = "log.txt";

    class Reception {
        public:
            Reception();
            ~Reception();

            void order(std::map<Utils::Pizza, std::size_t>);
            void status();
            void checkKitchens();

            void closeKitchen(std::size_t);

            void setMultiplier(double multiplier) {_multiplier = multiplier;}
            void setNbCook(double nbCook) {_nbCook = nbCook;}
            void setRestock(double restock) {_restock = restock;}

        private:
            std::pair<std::size_t, const IPC &>openNewKitchen();
            void logMsg(std::string);
            bool sendOrderToKitchen(const IPC &ipc, std::size_t, Utils::Pizza);
            void sendOrder(Utils::Pizza);

            double _multiplier = 1;
            std::size_t _nbCook = 1;
            double _restock = 1;
            std::ofstream _file;
            std::map<std::size_t, IPC> _kitchenFd;
            std::unordered_map<int, std::function<void (std::size_t)>> _commands;
    };
}

#endif
