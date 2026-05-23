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
        logMsg("Reception Opened.");
        _commands[CLOSE] = [this](std::size_t id) {closeKitchen(id);};
    }

    Reception::~Reception()
    {
        auto id = _kitchenFd.begin()->first;
        bool ask = false;

        while (!_kitchenFd.empty()) {
            if (id != _kitchenFd.begin()->first)
                ask = false;
            if (!ask)
                _kitchenFd.begin()->second.send(CLOSE);
            checkKitchens();
        }
        logMsg("Reception Closed.");
        _file.close();
    }

    bool Reception::openNewKitchen()
    {
        static std::size_t id = 0;
        bool value = true;

        try {
            auto fd = Connect::connect(Kitchen::run);
            _kitchenFd.emplace(std::make_pair(id, fd));
            logMsg("Kitchen[" + std::to_string(id) + "] Opened.");
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

    void Reception::checkKitchens()
    {
        std::vector<int> fds;
        std::vector<std::size_t> ids;
        for (auto const &kitchen: _kitchenFd) {
            fds.push_back(kitchen.second.getFd());
            ids.push_back(kitchen.first);
        }
        auto infos = Connect::infoToRead(fds);
        if (infos.size() != ids.size())
            return;
        for (std::size_t i = 0; i < infos.size(); i++) {
            if (!infos[i])
                continue;
            auto kitchenFd = _kitchenFd.find(ids[i]);
            if (kitchenFd == _kitchenFd.end())
                continue;
            try {
                int value = kitchenFd->second.receive<int>();
                auto find = _commands.find(value);
                if (find == _commands.end())
                    continue;
                find->second(ids[i]);
            } catch (IPC::CloseException &_) {
                logMsg("Kitchen[" + std::to_string(ids[i]) + "] Closed unexpectedly.");
                closeKitchen(ids[i]);
            }
        }
    }

    void Reception::closeKitchen(std::size_t id)
    {
        auto find = _kitchenFd.find(id);

        if (find == _kitchenFd.end())
            return;
        logMsg("Kitchen[" + std::to_string(id) + "] Closed.");
        _kitchenFd.erase(id);
    }

    void Reception::logMsg(std::string msg)
    {
        auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);

        _file << "[" << std::put_time(std::localtime(&t), "%H:%M:%S") << "] ";
        _file << msg << std::endl;
    }
}