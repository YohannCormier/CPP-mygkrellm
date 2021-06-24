/*
** EPITECH PROJECT, 2021
** MyGKrellm
** File description:
** ModuleUser
*/

#ifndef MODULEUSER_HPP_
#define MODULEUSER_HPP_

#include "IMonitorModule.hpp"

/* User Module Class that holds most of the generic user variables of the system */
class ModuleUser : public IMonitorModule {
    public:
        ModuleUser();
        ~ModuleUser();

        virtual std::string getModuleName() const;

        std::string getUsername() const;
        std::string getHostname() const;
        std::string getCompname() const;
        std::string getSysname() const;
        std::string getKername() const;
        std::string getOsname() const;

        time_t getTime() const;
        time_t getUptime() const;

    protected:
        std::string _username;
        std::string _hostname;
        std::string _compname;
        std::string _sysname;
        std::string _kername;
        std::string _osname;
};

#endif /* !MODULEUSER_HPP_ */
