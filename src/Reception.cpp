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
#include "Packet.hpp"

namespace Plazza {

    Reception::Reception() : _file(std::string(LOG_FILE))
    {
        logMsg("Reception Opened.");
        _commands[CLOSE] = [this](std::size_t id) {closeKitchen(id);};
        _commands[COMMAND] = [this](std::size_t id) {orderDone(id);};
        _commands[STATUS] = [this](std::size_t id) {printStatus(id);};
    }

    Reception::~Reception()
    {
        for (auto &[id, value] : _kitchenFd)
            value.first.send(CLOSE);
        while (!_kitchenFd.empty())
            checkKitchens();
        Connect::waitAll();
        logMsg("Reception Closed.");
        _file.close();
    }

    std::map<std::size_t, std::pair<IPC, std::size_t>>::iterator
        Reception::openNewKitchen()
    {
        static std::size_t id = 0;

        auto fd = Connect::connect([this](int fd) {
            Kitchen::run(fd, _multiplier, _nbCook, _restock);
        });
        _kitchenFd.emplace(std::make_pair(id, std::make_pair(fd, 0)));
        logMsg("Kitchen[" + std::to_string(id) + "] Opened.");
        id++;
        return _kitchenFd.find(id - 1);
    }

    void Reception::sendOrderToKitchen(
        const IPC &ipc, std::size_t id, Utils::Pizza pizza, std::size_t &count)
    {
        Packet<sizeof(Utils::Pizza)> packet;
        bool status = false;

        packet << pizza;
        ipc.send(COMMAND);
        ipc.send(packet);
        ++count;
        logMsg("Kitchen[" + std::to_string(id) + "] Add "
            + Utils::pizzaToString(pizza) + " to the list.");
        status = true;
    }

    void Reception::sendOrder(Utils::Pizza pizza)
    {
        for (auto &kitchen: _kitchenFd) {
            if (kitchen.second.second < _nbCook * 2)
                return sendOrderToKitchen(kitchen.second.first,
                    kitchen.first, pizza, kitchen.second.second);
        }
        auto kitchen = openNewKitchen();
        sendOrderToKitchen(kitchen->second.first,
            kitchen->first, pizza, kitchen->second.second);
    }

    void Reception::order(std::map<Utils::Pizza, std::size_t> pizzas)
    {
        for (auto [pizza, nb]: pizzas) {
            for (size_t i = 0; i < nb; i++)
                sendOrder(pizza);
        }
    }

    void Reception::status()
    {
        for (auto &kitchen: _kitchenFd)
            kitchen.second.first.send(STATUS);
        logMsg("Status Command Executed");
    }

    void Reception::checkKitchens()
    {
        std::vector<int> fds;
        std::vector<std::size_t> ids;
        for (auto const &kitchen: _kitchenFd) {
            fds.push_back(kitchen.second.first.getFd());
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
                int value = kitchenFd->second.first.receive<int>();
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

    void Reception::orderDone(std::size_t id)
    {
        auto find = _kitchenFd.find(id);

        if (find == _kitchenFd.end())
            return;
        auto packet = find->second.first.receive<Packet<sizeof(Utils::Pizza)>>();
        Utils::Pizza pizza;
        packet >> pizza;
        --find->second.second;
        logMsg("Kitchen[" + std::to_string(id) + "] Pizza "
            + Utils::pizzaToString(pizza) + " is ready to be served.");
    }

    void Reception::receiveCooksInfo(IPC &ipc)
    {
        std::cout << "  Cooks:" <<  std::endl;
        for (std::size_t i = 0; i < _nbCook; ++i) {
            auto status = ipc.receive<bool>();
            std::cout << "      Cook n°" << i << ": " <<
                (status ? "active": "inactive") << std::endl;
        }
    }

    void Reception::receiveIngredientsInfo(IPC &ipc)
    {
        std::cout << "  Ingredients:" << std::endl;
        for (std::size_t i = 0; i < Utils::NB_INGREDIENT; ++i) {
            auto packet = ipc.receive
                <Packet<sizeof(std::pair<Utils::IngredientType, std::size_t>)>>();
            std::pair<Utils::IngredientType, std::size_t> ingredient;
            packet >> ingredient;
            std::cout << "      " <<
                Utils::_strIngredientType.at(ingredient.first) << ": " <<
                ingredient.second << std::endl;
        }
    }

    void Reception::printStatus(std::size_t id)
    {
        auto find = _kitchenFd.find(id);

        if (find == _kitchenFd.end())
            return;
        std::cout << "\r";
        std::cout << "Kitchen n°" << id << ":" << std::endl;
        std::cout << "  Pizza in queue: " << find->second.second << std::endl;
        receiveCooksInfo(find->second.first);
        receiveIngredientsInfo(find->second.first);
        std::cout << "> " << std::flush;
        logMsg("Kitchen[" + std::to_string(id) + "] Status given");
    }

    void Reception::logMsg(std::string msg)
    {
        auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);

        _file << "[" << std::put_time(std::localtime(&t), "%H:%M:%S") << "] ";
        _file << msg << std::endl;
    }
}