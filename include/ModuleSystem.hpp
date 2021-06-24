/*
** EPITECH PROJECT, 2021
** MyGKrellm
** File description:
** ModuleSystem
*/

#ifndef MODULESYSTEM_HPP_
#define MODULESYSTEM_HPP_

#include "IMonitorModule.hpp"
#include <vector>

/* System Module Class that holds most of the generic system variables */
class ModuleSystem : public IMonitorModule {
    public:
        enum CPUStates {
            USER,
            NICE,
            SYSTEM,
            IDLE,
            IOWAIT,
            IRQ,
            SOFTIRQ,
            STEAL,
            GUEST,
            GUEST_NICE
        };

        typedef struct CPUData_s {
            std::string cpu;
            std::size_t times[10];
        } CPUData;

        ModuleSystem();
        ~ModuleSystem();

        virtual std::string getModuleName() const;

        std::string getVendorId() const;
        std::string getModelname() const;
        int getNumCores() const;
        int getLogCores() const;
        float getCPUFreqMHz(int core) const;
        float getLoadTime(int core);
        float getIdleTime(int core);
        float getLoadPercent(int core);
        float getIdlePercent(int core);
        float getTotalTime(int core);

        size_t getTotalRam();
        size_t getFreeRam();
        size_t getTotalSwap();
        size_t getFreeSwap();


    private:
        void readCPUStats(std::vector<CPUData>& stats);
        void setStats(const std::vector<CPUData>& snap1, const std::vector<CPUData>& snap2);
        size_t getSTLoadTime(const CPUData& data) const;
        size_t getSTIdleTime(const CPUData& data) const;
        void readRAMStats();

    protected:
        std::string _vendorId;
        std::string _modelName;
        int _numCores;
        int _numLogCores;
        std::vector<float> _idleTime;
        std::vector<float> _loadTime;
        std::vector<float> _idlePercent;
        std::vector<float> _loadPercent;
        std::vector<float> _totalTime;

        size_t _totalRam;
        size_t _freeRam;
        size_t _totalSwap;
        size_t _freeSwap;

    private:
        std::vector<CPUData> _snap1;
        std::vector<CPUData> _snap2;
};

#endif /* !MODULESYSTEM_HPP_ */
