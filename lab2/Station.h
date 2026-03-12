#pragma once
#include <vector>
#include <string>
#include "Robot.h"
#include "Module.h"

class Station {
private:
    std::string stationName;
    int day;
    int energy;
    int maxEnergy;
    int bits;
    
    std::vector<Robot> robots;
    std::vector<Module> modules;
    std::vector<std::string> logs;

    void ProcessProduction();
    void ProcessHousing();
    void ProcessSignal();
    void ProcessTaxes(); // Вариант 7
    void ProcessCleanup();

public:
    Station();
    void Init(std::string name);
    void ProcessDay();
    void PrintStatus() const;
    bool IsGameOver() const;
};