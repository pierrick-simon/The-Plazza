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

    constexpr std::string_view LOG_FILE = "plazza.log";

    class Reception {
        public:
            Reception();
            ~Reception();

            void order(std::map<Utils::Pizza, std::size_t>);
            void status();
            void checkKitchens();

            void setMultiplier(double multiplier) {_multiplier = multiplier;}
            void setNbCook(double nbCook) {_nbCook = nbCook;}
            void setRestock(std::size_t restock) {_restock = restock;}

        private:
            std::map<std::size_t, std::pair<IPC, std::size_t>>::iterator
                openNewKitchen();
            void logMsg(std::string);
            void sendOrderToKitchen(const IPC &ipc, std::size_t,
                Utils::Pizza, std::size_t &count);
            void sendOrder(Utils::Pizza);
            void closeKitchen(std::size_t);
            void orderDone(std::size_t);
            void receiveCooksInfo(IPC &ipc);
            void receiveIngredientsInfo(IPC &ipc);
            void printStatus(std::size_t);

            double _multiplier = 1;
            std::size_t _nbCook = 1;
            std::size_t _restock = 1;
            std::ofstream _file;
            std::map<std::size_t, std::pair<IPC, std::size_t>> _kitchenFd;
            std::unordered_map<int, std::function<void (std::size_t)>> _commands;
    };
}

#endif
