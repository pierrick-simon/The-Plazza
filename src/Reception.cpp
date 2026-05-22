/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** Reception
*/

#include <chrono>
#include <iomanip>
#include "Reception.hpp"
#include "Kitchen.hpp"
#include "Connect.hpp"

namespace Plazza {

    Reception::Reception() : _file(std::string(LOG_FILE))
    {
        logMsg("Reception Open.");
    }

    Reception::~Reception()
    {
        logMsg("Reception Close.");
        _file.close();
    }

    bool Reception::openNewKitchen()
    {
        static std::size_t id = 0;
        bool value = true;

        try {
            auto fd = Connect::connect(Kitchen::run);
            _kitchenFd.emplace(std::make_pair(id, fd));
            logMsg("New Kitchen Open [" + std::to_string(id) + "].");
            id++;
        } catch (Connect::ConnectException &_) {
            value = false;
        }
        return value;
    }

    void Reception::order(std::map<Utils::Pizza, std::size_t> pizzas)
    {
        openNewKitchen();
    }

    void Reception::status()
    {
    }

    void Reception::logMsg(std::string msg)
    {
        auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);

        _file << "[" << std::put_time(std::localtime(&t), "%H:%M:%S") << "] ";
        _file << msg << std::endl;
    }
}
