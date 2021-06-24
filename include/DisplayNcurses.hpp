/*
** EPITECH PROJECT, 2021
** B-CPP-300-NCY-3-1-CPPrush3-pierre.perrin
** File description:
** DisplayNcurses
*/

#ifndef DISPLAYNCURSES_HPP_
#define DISPLAYNCURSES_HPP_

#include <ncurses.h>
#include <iostream>
#include <vector>
#include "ModuleSystem.hpp"


//create window and store all informations
class window
{
    public:
        window(int height, int width, int pos_y, int pos_x):
        _height(height), _width(width), _pos_x(pos_x), _pos_y(pos_y)
        {
            _win = newwin(_height, _width, _pos_y, _pos_x);
        };
        ~window() {};

        int _height;
        int _width;
        int _pos_x;
        int _pos_y;
        WINDOW *_win;
        std::vector<int> _graph;
        bool rev = true;
};

std::vector<window> window_disposition(int procnbr);
std::vector<window> evenBasedPos(int procnbr);
std::vector<window> oddBasedPos(int procnbr);
std::vector<window> setInformations(std::vector<window> wind, ModuleSystem sys);
int launch_ncurses ();

#endif /* !DISPLAYNCURSES_HPP_ */
