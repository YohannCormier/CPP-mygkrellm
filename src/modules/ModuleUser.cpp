/*
** EPITECH PROJECT, 2021
** MyGKrellm
** File description:
** ModuleUser
*/

#include "../../include/ModuleUser.hpp"
#include <string>
#include <sys/utsname.h>
#include <fstream>

ModuleUser::ModuleUser() {
    _username = getenv("USER");

    struct utsname stats;
    uname(&stats);

    _hostname = stats.nodename;
    _compname = stats.machine;
    _sysname = stats.sysname;
    _kername = stats.release;
    _osname = stats.version;
}

ModuleUser::~ModuleUser() {}

/* Returns the name of the Module */
std::string ModuleUser::getModuleName() const {
    return ("User Module");
}

/* Returns the username of the current user, NULL if undefined in the env */
std::string ModuleUser::getUsername() const {
    return (this->_username);
}

/* Returns the machine name according to utsname.h */
std::string ModuleUser::getCompname() const {
    return (this->_compname);
}

/* Returns the hostname according to utsname.h */
std::string ModuleUser::getHostname() const {
    return (this->_hostname);
}

/* Returns the system name according to utsname.h */
std::string ModuleUser::getSysname() const {
    return (this->_sysname);
}

/* Returns the kernel name according to utsname.h */
std::string ModuleUser::getKername() const {
    return (this->_kername);
}

/* Returns the os name according to utsname.h */
std::string ModuleUser::getOsname() const {
    return (this->_osname);
}

/* Returns the current time as a time_t containing the current UNIX Timestamp in seconds*/
time_t ModuleUser::getTime() const {
    return (time(0));
}

/* Returns the current uptime of the computer in seconds as a time_t */
time_t ModuleUser::getUptime() const {
    double uptimeSeconds;

    std::ifstream("/proc/uptime", std::ios::in) >> uptimeSeconds;
    time_t upTime = uptimeSeconds;
    return (upTime);
}