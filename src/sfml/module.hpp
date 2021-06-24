/*
** EPITECH PROJECT, 2021
** Cpp Pool rush3
** File description:
** GKrellM
*/

#ifndef GKRELLM_WINDOW_
#define GKRELLM_WINDOW_

#include <vector>
#include <SFML/Graphics.hpp>
#include "SFML/System/Vector2.hpp"
#include "graph.hpp"

class module
{
public:
    module(bool, std::string);
    ~module();

    void setPosition(sf::Vector2u pos);
    void setBackground(sf::Color color);
    void setText(std::string *content);
    void drawModule();
    bool isActive();

    bool _active;
    std::string _type;
    sf::RectangleShape _background;
    sf::Font _font;
    sf::Text _title;
    std::vector<sf::Text> _text;
    sf::Vector2u _begin;
    sf::Vector2u _end;
    Graph _graph;
};

class moduleList
{
public:
    explicit moduleList();
    ~moduleList();

    void setPositions(sf::RenderWindow& window);
    void setSize(sf::RenderWindow& window);
    void setTitles(sf::Font);
    void setModuleTitle(std::string title, int i);

    std::vector<module> _modules;
    unsigned int _size;
    unsigned int _coreNbr;
};

class monitor
{
public:
    monitor();
    ~monitor() {};

    sf::Font _Font;
    sf::Text _coreInfo;
    sf::Text _ramInfo;
    moduleList _modulesList;
    sf::RenderWindow _window;
    sf::Clock _fpsClock;
};

#endif /* !GKRELLM_WINDOW_ */
