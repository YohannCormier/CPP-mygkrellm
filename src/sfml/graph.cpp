/*
** EPITECH PROJECT, 2021
** B-CPP-300-NCY-3-1-CPPrush3-pierre.perrin
** File description:
** graph
*/

#include "graph.hpp"
#include <stdlib.h>

Graph::Graph() : _graph_length(10) {}

Graph::~Graph() {}

void Graph::drawGraph(sf::RenderWindow& window)
{
    for (int j = 0; j < _bars.size(); j++) {
        window.draw(_bars[j]);
    }
}

void Graph::graph(std::string type, sf::RectangleShape background, int i)
{
    ModuleSystem sys;

    int core = 0;
    float usage = rand() % 100;

    if (type.find("CPU", 0) == 0) {
        core = std::atoi((type.erase(0, 3)).c_str());
        usage = sys.getLoadPercent(core);
    }

    sf::RectangleShape newBar;
    sf::Vector2f newBarPos;

    //Sets the coordinates at those of the module
    newBarPos.x = background.getPosition().x;
    newBarPos.y = background.getPosition().y;

    //Place the bar on the x axis on the right of the module
    newBarPos.x += background.getSize().x * 0.9;

    //Defines the height of the bar based on the usage
    sf::Vector2f newBarSize;
    newBarSize.y = background.getSize().y * (usage / 100);
    newBarSize.x = background.getSize().x / 10;

    //Places the bar on the right axis based on it's height
    newBarPos.y -= newBarSize.y;
    newBarPos.y += background.getSize().y;

    newBar.setPosition(newBarPos);
    newBar.setSize(newBarSize);
    newBar.setFillColor(sf::Color(0 + 2.5 * usage, 255 - 2.5 * usage, 0));

    for (int j = 0; j < _bars.size(); j++) {
        _bars[j].setPosition(sf::Vector2f(_bars[j].getPosition().x - newBar.getSize().x, _bars[j].getPosition().y));
    }
    if (_bars.size() > 9)
        _bars.erase(_bars.begin());
    _bars.push_back(newBar);
}