/*
** EPITECH PROJECT, 2021
** MyGKrellm
** File description:
** IMonitorModule
*/

#ifndef IMONITORMODULE_HPP_
#define IMONITORMODULE_HPP_

#include <string>

class IMonitorModule {
    public:
        IMonitorModule() {}
        virtual ~IMonitorModule() {}

        virtual std::string getModuleName() const = 0;
};

#endif /* !IMONITORMODULE_HPP_ */
