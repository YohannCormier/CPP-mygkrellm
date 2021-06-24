/*
** EPITECH PROJECT, 2021
** MyGKrellm
** File description:
** main
*/

#include <iostream>
#include <unistd.h>
#include "../include/ModuleUser.hpp"
#include "../include/ModuleSystem.hpp"
#include "../include/DisplayNcurses.hpp"
#include "sfml/moduleText.hpp"

int main(int ac, char **av)
{
    if (ac > 2)
        return (84);
    std::string text = "text";
    std::string graphic = "graphical";
    if (ac == 1 || text == av[1])
        launch_ncurses();
    else if (graphic == av[1])
        start_sfml();
    return (0);
}