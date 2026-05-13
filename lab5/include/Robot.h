#pragma once
#include <string>
#include <utility>
#include <iostream>
#include <iomanip>
#include <memory>

class Robot {
private:
    std::string name;
    int chassis;  // 0-100
    int firmware; // 0-100
    int age;
    double efficiencyModifier;

public:
    Robot(std::string n);
    virtual ~Robot();

    virtual std::pair<int, int> ProduceResources() const = 0;
    virtual int GetHousingNeed() const = 0;
    virtual std::string GetFactionName() const = 0;
    virtual int GetPowerContribution() const = 0;

    void TakeDamage(int chassisDmg, int firmwareDmg);
    void Repair(int eAmount, int dAmount);
    bool IsDead() const;

    std::string GetName() const;
    int GetChassis() const;
    int GetFirmware() const;
    int GetAge() const;
    double GetEfficiencyModifier() const;

    void SetChassis(int val);
    void SetFirmware(int val);
    void SetAge(int val);
    void SetEfficiencyModifier(double val);

    // Lab 4: Унарные операторы старения
    Robot& operator--(); 
    Robot& operator++(); 

    // Lab 4: Синтез сознания
    std::unique_ptr<Robot> operator+(const Robot& other) const;

    // Lab 4: Детектор клонов 
    bool operator==(const Robot& other) const;

    // Lab 4: Перегрузка вывода
    friend std::ostream& operator<<(std::ostream& os, const Robot& robot);
};
