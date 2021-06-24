/*
** EPITECH PROJECT, 2021
** B-CPP-300-NCY-3-1-CPPrush3-pierre.perrin
** File description:
** DisplayNcurses
*/

#include "../../include/DisplayNcurses.hpp"
#include "../../include/ModuleUser.hpp"
#include <chrono>
#include "../../include/ModuleSystem.hpp"

/*make and return a window vector in function of the number passed in parametter*/
std::vector<window> evenBasedPos(int procnbr)
{
    procnbr += (procnbr / 10) + 1;
    std::vector<window> tab;
    std::vector<int> cut;
    int count = 2;
    int max_y, max_x;
    int div_y, div_x;
    div_y = div_x = 1;
    int tmp_x, tmp_y;

    getmaxyx(stdscr, max_y, max_x);
    max_y -= 2;
    while (procnbr > 1)
    {
        if ((procnbr / count) % 2 == 0) {
            procnbr /= count;
            cut.push_back(count);
            count = 2;
        } else if (procnbr / count == 1) {
            procnbr /= count;
            cut.push_back(count);
        } else
            count++;
    }
    for (int i = 0; i < cut.size(); i++) {
        if (max_x > max_y) {
            max_x /= cut[i];
            div_x *= cut[i];
        }
        else {
            max_y /= cut[i];
            div_y *= cut[i];
        }
    }
    tmp_x = div_x;
    tmp_y = div_y;
    while (div_y != 0) {
        while (div_x != 0) {
            window win(max_y, max_x, ((max_y) * ((tmp_y - div_y)) + 1), (max_x) * (tmp_x - div_x));
            box(win._win, 0, 0);
            tab.push_back(win);
            div_x--;
        }
        div_y--;
        div_x = tmp_x;
    }
    return (tab);
}

/*make and return a window vector in function of the number passed in parametter*/
std::vector<window> oddBasedPos(int procnbr)
{
    procnbr += (procnbr / 10) + 1;
    std::vector<window> tab;
    std::vector<int> cut;
    int count = 2;
    int max_y, max_x;
    int div_y, div_x;
    div_y = div_x = 1;
    int tmp_x, tmp_y;

    getmaxyx(stdscr, max_y, max_x);
    max_y -= 2;
    while (procnbr > 1)
    {
        if ((procnbr / count) % 2 == 0) {
            procnbr /= count;
            cut.push_back(count);
            count = 2;
        } else if (procnbr / count == 1) {
            procnbr /= count;
            cut.push_back(count);
        } else
            count++;
    }
    for (int i = 0; i < cut.size(); i++) {
        if (max_x > max_y) {
            max_x /= cut[i];
            div_x *= cut[i];
        }
        else {
            max_y /= cut[i];
            div_y *= cut[i];
        }
    }
    tmp_x = div_x;
    tmp_y = div_y;
    while (div_y != 0) {
        while (div_x != 0) {
            window win(max_y, max_x, ((max_y) * (tmp_y - div_y)) + 1, (max_x) * (tmp_x - div_x));
            box(win._win, 0, 0);
            tab.push_back(win);
            div_x--;
        }
        div_y--;
        div_x = tmp_x;
    }
    return (tab);
}

/*choice the disposition of window between the odd one and even one return a vector of all CPU window*/
std::vector<window> create_window_disposition(int procnbr)
{
    if (procnbr % 2 == 0) {
        return (evenBasedPos(procnbr));
    } else {
        return (oddBasedPos(procnbr));
    }
}

/*update all windows*/
std::vector<window> window_disposition(std::vector<window> wind, int procnbr)
{
    std::vector<window> tab;
    if (procnbr % 2 == 0) {
        tab = evenBasedPos(procnbr);
    } else {
        tab = oddBasedPos(procnbr);
    }
    for (int i = 0; i < wind.size() ; i++) {
        tab[i]._graph = wind[i]._graph;
        tab[i].rev = wind[i].rev;
    }
    return(tab);
}

/*function that start the ncurses part of the project*/
int launch_ncurses ()
{
    ModuleUser user;
    ModuleSystem sys;
    int procnbr = sys.getLogCores();
    time_t prev, now;
    char* date_time;
    int max_x, max_y;
    std::vector<window> tab;


    initscr();
    noecho();
    start_color();
    keypad(stdscr, true);
    tab = create_window_disposition(procnbr);
    char c = 0;
    prev = time(0);
    while (c != 'q') {
        getmaxyx(stdscr, max_y, max_x);
        now = time(0);
        date_time = ctime(&now);
        if (prev + 0.4 < now) {
            // clear();
            refresh(); // refresh tout l'ecran
            mvwprintw(stdscr, 0, 0, "%s--%s--%s--%s--%s--%s", user.getHostname().c_str(),user.getUsername().c_str(), user.getSysname().c_str(), user.getKername().c_str(), sys.getModelname().c_str(), date_time);
            mvwprintw(stdscr, max_y - 1, 0, "Pess Q to quit  ");
            if (tab[0].rev == true)
                printw("Press L for light mode |||| TotalRAM: %dkB FreeRAM: %dkB UseRAM: %dkB |||| TotalSwap: %dkB FreeSwap: %dKB UseSwap: %dkB", sys.getTotalRam(), sys.getFreeRam(), sys.getTotalRam()-sys.getFreeRam(), sys.getTotalSwap(), sys.getFreeSwap(), sys.getTotalSwap()-sys.getFreeSwap());
            else if (tab[0].rev == false)
                printw(" Press D for dark mode |||| TotalRAM: %dkB FreeRAM: %dKB UseRAM: %dkB |||| TotalSwap: %dkB FreeSwap: %dKB UseSwap: %dkB", sys.getTotalRam(), sys.getFreeRam(), sys.getTotalRam()-sys.getFreeRam(), sys.getTotalSwap(), sys.getFreeSwap(), sys.getTotalSwap()-sys.getFreeSwap());
            for (int i = 0; i < tab.size(); i++) {
                if (i >= procnbr) {}
                else {
                    wrefresh(tab[i]._win); // refresh une windw en particuler
                }
            }
            tab = window_disposition(tab, procnbr);
            tab = setInformations(tab, sys);
            prev = now;
        }
        curs_set(0);
        timeout(500);
        c = getch();
        if (c == 'l') {
            attron(A_REVERSE);
            for (int i = 0; i < tab.size(); i++) {
                if (c == 'l') {
                    tab[i].rev = false;
                } else if (c == 'd') {
                    tab[i].rev = true;
                }
            }
        }
        if (c == 'd') {
            attroff(A_REVERSE);
            for (int i = 0; i < tab.size(); i++) {
                if (c == 'l') {
                    tab[i].rev = false;
                } else if (c == 'd') {
                    tab[i].rev = true;
                }
            }
        }
    }
    endwin();
    return (0);
}