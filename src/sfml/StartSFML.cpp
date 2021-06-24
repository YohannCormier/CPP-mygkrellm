/*
** EPITECH PROJECT, 2021
** Cpp Pool rush3
** File description:
** GKrellM
*/

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "module.hpp"
#include "moduleText.hpp"
#include <iostream>

void updateMonitor(monitor& Objects)
{
    Objects._modulesList.setSize(Objects._window);
    Objects._modulesList.setPositions(Objects._window);
    for (int i = 0; i != Objects._modulesList._modules.size(); i++) {
        Objects._window.draw(Objects._modulesList._modules[i]._background);
        Objects._modulesList._modules[i]._graph.graph(Objects._modulesList._modules[i]._type, Objects._modulesList._modules[i]._background, i);
        Objects._modulesList._modules[i]._graph.drawGraph(Objects._window);
        Objects._modulesList._modules[i]._title.setPosition(Objects._modulesList._modules[i]._background.getPosition());
        Objects._window.draw(Objects._modulesList._modules[i]._title);
    }
    updateModuleText(Objects);
}

void setMonitor(monitor& Objects)
{
    setModuleText(Objects);
    Objects._modulesList.setTitles(Objects._Font);
}

int start_sfml()
{
    monitor Objects;
    Objects._fpsClock;
    setMonitor(Objects);

    while (Objects._window.isOpen())
    {
        sf::Event event;

        if (Objects._fpsClock.getElapsedTime().asSeconds() > 1) {
            Objects._fpsClock.restart();
            Objects._window.clear(sf::Color(100, 100, 100));
            updateMonitor(Objects);
            while (Objects._window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    Objects._window.close();
                if (event.key.code == sf::Keyboard::Escape ||
                    event.key.code == sf::Keyboard::Q)
                    Objects._window.close();
            }
            Objects._window.display();
        }
    }

    return EXIT_SUCCESS;
}