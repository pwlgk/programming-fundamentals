#pragma once
#include <string>
#include <utility>

class Robot {
protected:
    std::string name;
    int chassis;  // 0-100
    int firmware; // 0-100

public:
    Robot(std::string n) : name(n), chassis(100), firmware(100) {}
    virtual ~Robot() {}

    virtual std::pair<int, int> ProduceResources() const = 0;
    virtual int GetHousingNeed() const = 0;
    virtual std::string GetFactionName() const = 0;
    virtual int GetPowerContribution() const = 0; // Для варианта 8
    
    void TakeDamage(int chassisDmg, int firmwareDmg) {
        chassis -= chassisDmg;
        firmware -= firmwareDmg;
        if (chassis < 0) chassis = 0;
        if (firmware < 0) firmware = 0;
    }
    
    void Repair(int eAmount, int dAmount) {
        chassis += eAmount / 2;
        firmware += dAmount / 2;
        if (chassis > 100) chassis = 100;
        if (firmware > 100) firmware = 100;
    }
    
    bool IsDead() const { return (chassis <= 0 || firmware <= 0); }
    std::string GetName() const { return name; }
    int GetChassis() const { return chassis; }
    int GetFirmware() const { return firmware; }
};

class IntegratorRobot : public Robot {
public:
    IntegratorRobot(std::string n) : Robot(n) {}
    std::pair<int, int> ProduceResources() const override { return {25, 5}; }
    int GetHousingNeed() const override { return 1; }
    std::string GetFactionName() const override { return "Интегратор"; }
    int GetPowerContribution() const override { return 10; }
};

class KeeperRobot : public Robot {
public:
    KeeperRobot(std::string n) : Robot(n) {}
    std::pair<int, int> ProduceResources() const override { return {5, 25}; }
    int GetHousingNeed() const override { return 2; }
    std::string GetFactionName() const override { return "Хранитель"; }
    int GetPowerContribution() const override { return 10; }
};

class LocalCalculatorRobot : public Robot {
public:
    LocalCalculatorRobot(std::string n) : Robot(n) {}
    std::pair<int, int> ProduceResources() const override { return {10, 10}; }
    int GetHousingNeed() const override { return 1; }
    std::string GetFactionName() const override { return "Локальный вычислитель"; }
    int GetPowerContribution() const override { return 0; } // Не увеличивает мощность сети
};


