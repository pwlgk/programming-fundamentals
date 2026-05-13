#pragma once
#include <vector>
#include <string>
#include "Robot.h"
#include "IntegratorRobot.h"
#include "KeeperRobot.h"
#include "LocalCalculatorRobot.h"
#include "Module.h"
#include "ArchiveModule.h"
#include "ControlCenterModule.h"
#include "HousingModule.h"
#include "GeneratorModule.h"

class Station {
private:
    std::string stationName;
    int day;
    int energy;
    int maxEnergy;
    int bits;

    std::vector<std::unique_ptr<Robot>> robots;
    std::vector<std::shared_ptr<Module>> modules;

    std::vector<std::string> logs;

    void ProcessProduction();    
    void ProcessHousing();       
    void ProcessSignal();        
    void ProcessTaxes();         
    void ProcessCleanup();       

    int stormDuration;
    bool isCoolantLeaking;

    void ClearMemory();          

public:
    Station();
    ~Station();

    void Init(std::string name);
    void ProcessDay();
    
    void SynthesizeRobot(int choice);
    void SynthesizeConsciousness(int idxA, int idxB); 
    void CheckClones(int idxA, int idxB);             
    
    void BuildModule(int choice);
    void UpgradeModule(int index);
    void CombineModules(int idxA, int idxB);          
    
    void RepairRobot(int index);                      

    Robot* GetRobot(int index) const { return (index >= 0 && index < (int)robots.size()) ? robots[index].get() : nullptr; }
    Module* GetModule(int index) const { return (index >= 0 && index < (int)modules.size()) ? modules[index].get() : nullptr; }

    void PrintStatus() const;
    void PrintModules() const;
    void PrintRobots() const;                         
    void PrintAnalytics() const;

    bool IsGameOver() const;

    // Обработчики штрафов
    void ApplyPowerSurgePenalty();
    void ApplyFirmwareGlitchPenalty();
    void ApplyMeteorStrikePenalty();
    void ApplyCoolantLeakPenalty();
    void AdvanceDayOnException(); // Чтобы счетчик дней не останавливался

    int GetDay() const { return day; }
    int GetEnergy() const { return energy; }
    int GetBits() const { return bits; }
};
