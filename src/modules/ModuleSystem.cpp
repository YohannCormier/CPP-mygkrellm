/*
** EPITECH PROJECT, 2021
** B-CPP-300-NCY-3-1-CPPrush3-pierre.perrin [WSL: Ubuntu-20.04]
** File description:
** ModuleSystem
*/

#include "../../include/ModuleSystem.hpp"
#include <iostream>
#include <string>
#include <thread>

#include <fstream>
#include <sstream>

static std::string removeWhitespace(const std::string& line) {
    const char* whitespace = " \t\v\r\n";
    std::size_t begin = line.find_first_not_of(whitespace);
    std::size_t end = line.find_last_not_of(whitespace);
    if (begin == end)
        return (std::string());
    else
        return (line.substr(begin, end - begin + 1));
}

ModuleSystem::ModuleSystem() {
    std::ifstream cpufile("/proc/cpuinfo");
    std::string delim = ":";
    std::string line;

    size_t pos = 0;
    if (cpufile.is_open()) {
        while (std::getline(cpufile, line)) {
            std::string token = line.substr(line.find(':') + 1);
            if (line.rfind("vendor_id", 0) == 0)
                _vendorId = removeWhitespace(token);
            if (line.rfind("model name", 0) == 0)
                _modelName = removeWhitespace(token);
            if (line.rfind("cpu cores", 0) == 0)
                _numCores = std::stoi(token);
        }
    }
    cpufile.close();
    _numLogCores = std::thread::hardware_concurrency();
}

ModuleSystem::~ModuleSystem() {}

void ModuleSystem::readRAMStats() {
    std::ifstream cpufile("/proc/meminfo");
    std::string delim = ":";
    std::string line;

    size_t pos = 0;
    if (cpufile.is_open()) {
        while (std::getline(cpufile, line)) {
            std::string token = removeWhitespace(line.substr(line.find(':') + 1));
            if (line.rfind("MemTotal", 0) == 0)
                _totalRam = std::stoi(token);
            if (line.rfind("MemFree", 0) == 0)
                _freeRam = std::stoi(token);
            if (line.rfind("SwapTotal", 0) == 0)
                _totalSwap = std::stoi(token);
            if (line.rfind("SwapFree", 0) == 0)
                _freeSwap = std::stoi(token);
        }
    }
    cpufile.close();
}

void ModuleSystem::readCPUStats(std::vector<CPUData>& stats) {
    std::ifstream cpustat("/proc/stat");
    std::string line;

    if (cpustat.is_open()) {
        while (std::getline(cpustat, line)) {
            if (line.rfind("cpu", 0) == 0) {
                std::istringstream iss(line);
                stats.emplace_back(CPUData());
                CPUData& stat = stats.back();

                iss >> stat.cpu;
                if (stat.cpu.size() > 3)
                    stat.cpu.erase(0, 3);
                else
                    stat.cpu = "tot";

                for (int i = 0; i < 10; i++)
                    iss >> stat.times[i];
            }
        }
    }
}

void ModuleSystem::setStats(const std::vector<CPUData>& snap1, const std::vector<CPUData>& snap2) {
    for (int i = 0; i < snap1.size(); i++) {
        const CPUData& t1 = snap1[i];
        const CPUData& t2 = snap2[i];

        _loadTime.push_back(static_cast<float>(getSTLoadTime(t2) - getSTLoadTime(t1)));
        _idleTime.push_back(static_cast<float>(getSTIdleTime(t2) - getSTIdleTime(t1)));
        _totalTime.push_back(_loadTime[i] + _idleTime[i]);

        _loadPercent.push_back((100.0f * _loadTime[i] / _totalTime[i]));
        _idlePercent.push_back((100.0f * _idleTime[i] / _totalTime[i]));
    }
}

size_t ModuleSystem::getSTIdleTime(const CPUData& data) const {
    return (data.times[IDLE] + data.times[IOWAIT]);
}

size_t ModuleSystem::getSTLoadTime(const CPUData& data) const {
    return (data.times[USER] +
            data.times[NICE] +
            data.times[SYSTEM] +
            data.times[IRQ] +
            data.times[SOFTIRQ] +
            data.times[STEAL] +
            data.times[GUEST] +
            data.times[GUEST_NICE]);
}

/** @param core ID of the core you want to get the value
 * Returns the load time of the processor in the last 100ms.
 * WARNING !! This function call a thread.sleep(100);
 * Therefore it isn't really threadsafe or anything
 */
float ModuleSystem::getLoadTime(int core) {
    readCPUStats(_snap1);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    readCPUStats(_snap2);
    setStats(_snap1, _snap2);
    return (_loadTime[core]);
}

/** @param core ID of the core you want to get the value
 * Returns the idle time of the processor in the last 100ms.
 * WARNING !! This function call a thread.sleep(100);
 * Therefore it isn't really threadsafe or anything
 */
float ModuleSystem::getIdleTime(int core) {
    readCPUStats(_snap1);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    readCPUStats(_snap2);
    setStats(_snap1, _snap2);
    return (_idleTime[core]);
}

/** @param core ID of the core you want to get the value 
 * Returns the idle percent of the processor in the last 100ms.
 * WARNING !! This function call a thread.sleep(100);
 * Therefore it isn't really threadsafe or anything
 */
float ModuleSystem::getIdlePercent(int core) {
    readCPUStats(_snap1);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    readCPUStats(_snap2);
    setStats(_snap1, _snap2);
    return (_idlePercent[core]);
}

/** @param core ID of the core you want to get the value
 * Returns the load percent of the processor in the last 100ms.
 * WARNING !! This function call a thread.sleep(100);
 * Therefore it isn't really threadsafe or anything
 */
float ModuleSystem::getLoadPercent(int core) {
    readCPUStats(_snap1);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    readCPUStats(_snap2);
    setStats(_snap1, _snap2);
    return (_loadPercent[core]);
}

/** @param core ID of the core you want to get the value
 * Returns the total time of the processor in the last 100ms.
 * WARNING !! This function call a thread.sleep(100);
 * Therefore it isn't really threadsafe or anything
 */
float ModuleSystem::getTotalTime(int core) {
    readCPUStats(_snap1);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    readCPUStats(_snap2);
    setStats(_snap1, _snap2);
    return (_totalTime[core]);
}

/* Returns the total memory available on the system in KB */
size_t ModuleSystem::getTotalRam() {
    readRAMStats();
    return (this->_totalRam);
}

/* Returns the current free memory of the system in KB*/
size_t ModuleSystem::getFreeRam() {
    readRAMStats();
    return (this->_freeRam);
}

/* Returns the total memory available in the swap in KB*/
size_t ModuleSystem::getTotalSwap() {
    readRAMStats();
    return (this->_totalSwap);
}

/* Returns the free memory in the swap in KB*/
size_t ModuleSystem::getFreeSwap() {
    readRAMStats();
    return (this->_freeSwap);
}

/* Returns the name of the current module */
std::string ModuleSystem::getModuleName() const {
    return ("System Module");
}

/* Returns the vendor ID of the processor */
std::string ModuleSystem::getVendorId() const {
    return (_vendorId);
}

/* Returns the name of the current module */
std::string ModuleSystem::getModelname() const {
    return (_modelName);
}

/* Returns the number of physical cores fetched from /proc/cpuinfo */
int ModuleSystem::getNumCores() const {
    return (_numCores);
}

/* Returns the number of logical cores fetched from /proc/cpuinfo */
int ModuleSystem::getLogCores() const {
    return (_numLogCores);
}

/** @param Core The ID of the core you want to get the frequency. Should be less than the total number of logical cores.
 *  Returns the frequency of given core fetched from /proc/cpuinfo
*/
float ModuleSystem::getCPUFreqMHz(int core) const {
    std::ifstream cpufile("/proc/cpuinfo");
    std::string delim = ":";
    std::string line;

    int count = 0;
    float freq = 0;
    if (cpufile.is_open()) {
        while (std::getline(cpufile, line)) {
            std::string token = line.substr(line.find(':') + 1);
            if (line.rfind("cpu MHz", 0) == 0 && count != core)
                count++;
            else if (line.rfind("cpu MHz", 0) == 0 && count == core)
                freq = std::stof(token);
        }
    }
    cpufile.close();
    return (freq);
}
