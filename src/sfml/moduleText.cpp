/*
** EPITECH PROJECT, 2021
** Cpp Pool rush3
** File description:
** GKrellM
*/

#include "moduleText.hpp"

void setHostText(monitor& Objects)
{
    sf::Text addedText;

    addedText.setCharacterSize(18);
    addedText.setFont(Objects._Font);
    addedText.setFillColor(sf::Color::White);
    addedText.setStyle(sf::Text::Bold);
    addedText.setPosition(0, 0);
    Objects._coreInfo = addedText;
}

void updateHostText(monitor& Objects)
{
    ModuleUser uStats;

    std::string host = uStats.getHostname();
    std::string user = uStats.getUsername();
    std::string sys = uStats.getSysname();
    std::string os = uStats.getOsname();
    std::string kernam = uStats.getKername();
    std::string model = uStats.getModuleName();
    time_t uTime = uStats.getTime();

    Objects._coreInfo.setString(host + "--" + user + "--" + sys + "--" + os + "\n" + kernam + "--" + model + "\n" + ctime(&uTime));
    Objects._window.draw(Objects._coreInfo);
}

void setRamText(monitor& Objects)
{
    sf::Text addedText;

    addedText.setCharacterSize(18);
    addedText.setFont(Objects._Font);
    addedText.setFillColor(sf::Color::White);
    addedText.setStyle(sf::Text::Bold);
    addedText.setPosition(0, Objects._window.getSize().y - 50);
    Objects._ramInfo = addedText;
}

void updateRamText(monitor& Objects)
{
    ModuleSystem sys;

    size_t totalRam = sys.getTotalRam();
    size_t freeRam = sys.getFreeRam();
    size_t usedRam = totalRam - freeRam;
    size_t totalSwap = sys.getTotalSwap();
    size_t freeSwap = sys.getFreeSwap();
    size_t usedSwap = totalSwap - freeSwap;

    Objects._ramInfo.setString("Press Q to exit\nTotalRAM: " + std::to_string(totalRam)
    + " FreeRAM:" + std::to_string(freeRam)
    + " UsedRam: " + std::to_string(usedRam)
    + " TotalSwap: " + std::to_string(totalSwap)
    + " FreeSwap: " + std::to_string(freeSwap)
    + " UsedSwap: " + std::to_string(usedSwap));
    Objects._window.draw(Objects._ramInfo);
}

void updateModuleText(monitor& Objects)
{
    updateHostText(Objects);
    updateRamText(Objects);
    for (int i = 0; i != Objects._modulesList._modules.size(); i++);
}

void setModuleText(monitor& Objects)
{
    setHostText(Objects);
    setRamText(Objects);
    for (int i = 0; i != Objects._modulesList._modules.size(); i++);
}