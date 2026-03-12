#pragma once
#include <string>
#include <utility>

enum class Faction { INTEGRATOR, KEEPER };

class Robot {
private:
    std::string name;
    Faction faction;
    int chassis;  // 0-100
    int firmware; // 0-100

public:
    Robot(std::string n, Faction f);
    
    std::pair<int, int> ProduceResources() const;
    void TakeDamage(int chassisDmg, int firmwareDmg);
    void Repair(int eAmount, int dAmount); // Ремонт за энергию и данные
    
    bool IsDead() const;
    int GetHousingNeed() const;
    std::string GetName() const { return name; }
    std::string GetFactionName() const;
    int GetChassis() const { return chassis; }
    int GetFirmware() const { return firmware; }
};