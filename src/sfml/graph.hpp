/*
** EPITECH PROJECT, 2021
** B-CPP-300-NCY-3-1-CPPrush3-pierre.perrin
** File description:
** graph
*/

#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include "SFML/Graphics.hpp"
#include <iostream>
#include "../../include/ModuleSystem.hpp"

class Graph
{
    public:
        Graph();
        ~Graph();
        void graph(std::string type, sf::RectangleShape back, int i);
        void drawGraph(sf::RenderWindow& window);

        std::vector<sf::RectangleShape> _bars;
        std::vector<float> _points;
        sf::Vector2u _begin;
        sf::Vector2u _end;
        unsigned int _graph_length;
};

#endif /* !GRAPH_HPP_ */
