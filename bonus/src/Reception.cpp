/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** Reception
*/

#include <chrono>
#include <iomanip>
#include "Reception.hpp"
#include "../include/Kitchen.hpp"
#include "../include/Connect.hpp"
#include "../include/Packet.hpp"

namespace Plazza {

    Reception::Reception(sf::Font &font) : _file(std::string(LOG_FILE)), _font(font)
    {
        logMsg("Reception Opened.");
        _commands[CLOSE] = [this](std::size_t id) {closeKitchen(id);};
        _commands[COMMAND] = [this](std::size_t id) {orderDone(id);};
        _commands[STATUS] = [this](std::size_t id) {printStatus(id);};
        _clock.restart();
    }

    Reception::~Reception()
    {
        for (auto &[id, value] : _kitchenFd)
            value._ipc.send(CLOSE);
        while (!_kitchenFd.empty())
            checkKitchens();
        Connect::waitAll();
        logMsg("Reception Closed.");
        _file.close();
    }

    std::map<std::size_t, Info>::iterator
        Reception::openNewKitchen()
    {
        static std::size_t id = 0;

        auto fd = Connect::connect([this](int fd) {
            Kitchen::run(fd, _multiplier, _nbCook, _restock);
        });
        IPC ipc{fd};
        _kitchenFd.emplace(id, Info{std::move(ipc), 0, KitchenDisplay{_font, id, _nbCook}, false, 0});
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
        if (!_kitchenFd.empty()) {
            auto smalest = std::min_element(std::begin(_kitchenFd), std::end(_kitchenFd),
                [](const auto& l, const auto& r) { return l.second._queue < r.second._queue; });
            if (smalest->second._queue >= _nbCook * 2)
                smalest = openNewKitchen();
            sendOrderToKitchen(_kitchenFd.at(smalest->first)._ipc,
                smalest->first, pizza, _kitchenFd.at(smalest->first)._queue);
            return;
        }
        auto kitchen = openNewKitchen();
        sendOrderToKitchen(kitchen->second._ipc,
            kitchen->first, pizza, kitchen->second._queue);
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
            kitchen.second._ipc.send(STATUS);
        logMsg("Status Command Executed");
    }

    void Reception::checkKitchens()
    {
        std::vector<int> fds;
        std::vector<std::size_t> ids;
        for (auto const &kitchen: _kitchenFd) {
            fds.push_back(kitchen.second._ipc.getFd());
            ids.push_back(kitchen.first);
        }
        auto infos = Connect::infoToRead(fds);
        if (infos.size() != ids.size())
            return;
        std::vector<std::pair<std::size_t, int>> toProcess;
        for (std::size_t i = 0; i < infos.size(); i++) {
            if (!infos[i])
                continue;
            if (_kitchenFd.find(ids[i]) == _kitchenFd.end())
                continue;
            try {
                int value = _kitchenFd.at(ids[i])._ipc.receive<int>();
                toProcess.emplace_back(ids[i], value);
            } catch (IPC::CloseException &_) {
                logMsg("Kitchen[" + std::to_string(ids[i]) + "] Closed unexpectedly.");
                closeKitchen(ids[i]);
            }
        }
        for (auto &[id, value] : toProcess) {
            auto find = _commands.find(value);
            if (find == _commands.end())
                continue;
            find->second(id);
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
        auto packet = find->second._ipc.receive<Packet<sizeof(Utils::Pizza)>>();
        Utils::Pizza pizza;
        packet >> pizza;
        --find->second._queue;
        logMsg("Kitchen[" + std::to_string(id) + "] Pizza "
            + Utils::pizzaToString(pizza) + " is ready to be served.");
    }

    std::vector<bool> Reception::receiveCooksInfo(IPC &ipc)
    {
        std::vector<bool> cook;
        for (std::size_t i = 0; i < _nbCook; ++i) {
            auto status = ipc.receive<bool>();
            cook.push_back(status);
        }
        return cook;
    }

    std::unordered_map<Utils::IngredientType, std::size_t> Reception::receiveIngredientsInfo(IPC &ipc)
    {
        std::unordered_map<Utils::IngredientType, std::size_t> map;
        for (std::size_t i = 0; i < Utils::NB_INGREDIENT; ++i) {
            auto packet = ipc.receive
                <Packet<sizeof(std::pair<Utils::IngredientType, std::size_t>)>>();
            std::pair<Utils::IngredientType, std::size_t> ingredient;
            packet >> ingredient;
            map.emplace(ingredient);
        }
        return map;
    }

    void Reception::printStatus(std::size_t id)
    {
        auto find = _kitchenFd.find(id);

        if (find == _kitchenFd.end())
            return;
        auto cook = receiveCooksInfo(find->second._ipc);
        auto ingredient = receiveIngredientsInfo(find->second._ipc);
        find->second._display.update({cook, ingredient});
        find->second._status = false;
        find->second._elapsed = 0;
    }

    void Reception::logMsg(std::string msg)
    {
        auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);

        _file << "[" << std::put_time(std::localtime(&t), "%H:%M:%S") << "] ";
        _file << msg << std::endl;
    }

    void Reception::draw(sf::RenderWindow &win)
    {
        std::size_t i = 0;

        for (auto &kitchen: _kitchenFd) {
            float col = i % NB_X_KITCHEN;
            float line = (i - col) / NB_X_KITCHEN;
            sf::Vector2f pos(GAP + (GAP * 2 + BOX_X) * col, GAP + (GAP * 2 + BOX_Y) * line - _pos.y);
            kitchen.second._display.draw(win, pos);
            i++;
        }

    }

    void Reception::event(sf::Event &event)
    {
        auto elapsed = _clock.getElapsedTime().asMilliseconds();
        for (auto &kitchen: _kitchenFd) {
            if (kitchen.second._status)
                continue;
            kitchen.second._elapsed += elapsed;
            if (kitchen.second._elapsed < 100)
                continue;
            kitchen.second._status = true;
            kitchen.second._ipc.send(STATUS);
        }
        _clock.restart();
        if (event.type == sf::Event::MouseWheelMoved) {
            _pos.y -= event.mouseWheel.delta * 30;
            float col = _kitchenFd.size() % NB_X_KITCHEN;
            float line = (_kitchenFd.size() - col) / NB_X_KITCHEN;
            auto max = GAP + (GAP * 2.0 + BOX_Y) * line - WINDOW_SIZE_Y;
            std::cout << max << std::endl;
            if (_pos.y > max)
                _pos.y = max;
            if (_pos.y < 0.0)
                _pos.y = 0;
        }
    }
}