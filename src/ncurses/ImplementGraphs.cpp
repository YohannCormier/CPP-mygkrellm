/*
** EPITECH PROJECT, 2021
** B-CPP-300-NCY-3-1-CPPrush3-pierre.perrin
** File description:
** ImplementGraphs
*/

#include "../../include/DisplayNcurses.hpp"
#include "../../include/ModuleUser.hpp"

class info
{
    public:
        info(std::string name, int max, int value) : _name(name), _max_value(max), _value(value) {};
        ~info() {};
        std::string _name;
        int _max_value;
        int _value;
};

window displayGraph(window wind)
{
    int quarter, mid, threequarter;
    mid = wind._height / 2;
    quarter = mid * 1.5;
    threequarter = quarter - mid;
    int tmpw = wind._width - 2;
    int tmpg = wind._graph.size();
    for (int i = 0; tmpw - i > 0 && tmpg - i > 0; i++) {
        int value = wind._graph[(tmpg - i) - 1];
        if (wind.rev == true)
            wattroff(wind._win, A_REVERSE);
        else if (wind.rev == false)
            wattron(wind._win, A_REVERSE);
        for (int a = wind._height - 2; value > 1 ; a--, value--) {
            if (a > quarter) {
                init_pair(1, COLOR_GREEN, COLOR_BLACK);
                wattron(wind._win, COLOR_PAIR(1));
                mvwprintw(wind._win, a, tmpw - i, "|");
                wattroff(wind._win, COLOR_PAIR(1));
            }
            else if (a <= threequarter) {
                init_pair(2, COLOR_RED, COLOR_BLACK);
                wattron(wind._win, COLOR_PAIR(2));
                mvwprintw(wind._win, a, tmpw - i, "|");
                wattroff(wind._win, COLOR_PAIR(2));
            }
            else if (a <= mid && a > threequarter) {
                init_color(COLOR_MAGENTA, 999, 300, 0);
                init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
                wattron(wind._win, COLOR_PAIR(3));
                mvwprintw(wind._win, a, tmpw - i, "|");
                wattroff(wind._win, COLOR_PAIR(3));
            }
            else if (a <= quarter && a > mid) {
                init_pair(4, COLOR_YELLOW, COLOR_BLACK);
                wattron(wind._win, COLOR_PAIR(4));
                mvwprintw(wind._win, a, tmpw - i, "|");
                wattroff(wind._win, COLOR_PAIR(4));
            }
        }
    }
    return(wind);
}

std::vector<window> implementGraphs(std::vector<window> wind, std::vector<info> data)
{
    for (int i = 0 ; i < wind.size(); i++) {
        int cell = data[i]._max_value / (wind[i]._height - 2);
        int graph = data[i]._value / cell;
        wind[i]._graph.push_back(graph);
        wind[i] = displayGraph(wind[i]);
    }
    return(wind);
}

std::vector<window> setInformations(std::vector<window> wind, ModuleSystem sys)
{
    std::vector<info> data;
    int top, mid;
    top = 1;
    mid = wind[0]._height / 2;
    for (int i = 0; i < wind.size() ;i++) {
        std::string name = "CPU ";
        int max = 100;
        int value = sys.getLoadPercent(i);
        info in(name, max, value);
        data.push_back(in);
    }
    wind = implementGraphs(wind, data);
    for (int i = 0; i < wind.size(); i++) {
        if (wind[i].rev == true)
            wattroff(wind[i]._win, A_REVERSE);
        else if (wind[i].rev == false)
            wattron(wind[i]._win, A_REVERSE);
        mvwprintw(wind[i]._win, 0, 0, data[i]._name.c_str());
        wprintw(wind[i]._win, "%d", i);
        mvwprintw(wind[i]._win, top, 1, "100%%");
        mvwprintw(wind[i]._win, mid, 1, "50%%");
        mvwprintw(wind[i]._win, 0, wind[i]._width - 5, "%d%%" , data[i]._value);
        mvwprintw(wind[i]._win, wind[i]._height - 1, 0, "%.2f", sys.getCPUFreqMHz(i));
    }
    return (wind);
}

