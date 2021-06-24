/*
** EPITECH PROJECT, 2021
** Cpp Pool rush3
** File description:
** GKrellM
*/

#include "module.hpp"
#include <iostream>

monitor::monitor() : _window(sf::VideoMode(1280, 720), "My GKrellM graphical", sf::Style::Close),
_modulesList()
{
    _Font.loadFromFile("Montserrat-Regular.ttf");
}

moduleList::moduleList()
{
    ModuleSystem sys;
    std::string types [] = {"CPU", "NONE"};

    _coreNbr = sys.getLogCores();
    _size = 1;
    module newModule(true, "CPU");
    for (int i = 0; i != _size; i++) {
        newModule._type = types[i];
        if (i == 0)
            for (int coreAdd = 0; coreAdd != _coreNbr; coreAdd++) {
                newModule._type = "CPU" + std::to_string(coreAdd);
                _modules.push_back(newModule);
            }
        else
            _modules.push_back(newModule);
    }
}

moduleList::~moduleList()
{
    _modules.clear();
}

void moduleList::setPositions(sf::RenderWindow& window)
{
    sf::Vector2u size = window.getSize();
    sf::Vector2f rectPos;

    rectPos.x = 0;
    rectPos.y = size.y / 10;
    for (int i = 0; i != _modules.size(); i++) {
        _modules[i]._background.setPosition(rectPos);
        rectPos.x += _modules[i]._background.getSize().x;
        if (rectPos.x > window.getSize().x - _modules[i]._background.getSize().x) {
            rectPos.x = 0;
            rectPos.y += _modules[i]._background.getSize().y;
        }
    }
}

void moduleList::setTitles(sf::Font font)
{
    int i = 0;
    std::string cpuCore = "CPU";
    for (int cpuCoreNbr = 0; _modules[i]._type.find("CPU", 0) == 0; i++, cpuCoreNbr++) {
        setModuleTitle(cpuCore + std::to_string(i), i);
    }
}

void moduleList::setModuleTitle(std::string data, int i)
{
    _modules[i]._font.loadFromFile("Montserrat-Regular.ttf");
    _modules[i]._title.setString(data);
    _modules[i]._title.setCharacterSize(15);
    _modules[i]._title.setFont(_modules[i]._font);
    _modules[i]._title.setFillColor(sf::Color::White);
    _modules[i]._title.setStyle(sf::Text::Bold);
}

void moduleList::setSize(sf::RenderWindow& window)
{
    sf::Vector2u size = window.getSize();

    sf::Vector2f smallRectSize;
    smallRectSize.x = size.x / 4;
    if (_coreNbr <= 4)
        smallRectSize.y = size.y / 2;
    else if (_coreNbr <= 8)
        smallRectSize.y = size.y / 3;
    else if (_coreNbr <= 16) {
        smallRectSize.y = size.y / 4;
        smallRectSize.x = size.x / 6;
    } else {
        smallRectSize.y = size.y / 6;
        smallRectSize.x = size.x / 8;
    }

    for (int i = 0; i != _modules.size(); i++) {
        _modules[i]._background.setSize(smallRectSize);
    }
}

module::module(bool active, std::string type) :
_active(active), _type(type), _graph()
{
    _background.setFillColor(sf::Color(64, 64, 64));
    _background.setOutlineColor(sf::Color(128, 128, 128));
    _background.setOutlineThickness(3);
    _background.setSize(sf::Vector2f(300, 300));
}

module::~module() {}

void module::setPosition(sf::Vector2u pos)
{
    sf::Vector2f fpos;
    fpos.x = pos.x;
    fpos.y = pos.y;

    _background.setPosition(fpos);
}

void module::setBackground(sf::Color color)
{
    _background.setFillColor(color);
}

void module::setText(std::string *content)
{
    std::string::iterator it = content->begin();
    sf::Text node;

    while (it != content->end()) {
        node.setString(*it);
        _text.push_back(node);
        it++;
    }
}

bool module::isActive()
{
    return _active;
}
