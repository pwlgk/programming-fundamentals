#pragma once
#include <string>
#include <iostream>
#include <memory>

class Module {
private:
    int level;
    bool isActive;

public:
    Module();
    virtual ~Module();

    virtual int GetEnergyDelta() const = 0;
    virtual int GetDataDelta() const = 0;
    virtual int GetHousingCapacity() const = 0;
    virtual std::string GetTypeName() const = 0;
    
    virtual std::shared_ptr<Module> CloneWithLevel(int newLevel) const = 0;

    int GetLevel() const;
    void Upgrade();
    bool IsActive() const;
    void SetActive(bool status);

    // Lab 4: Модульная Сборка
    std::shared_ptr<Module> operator+(const Module& other) const;

    // Lab 4: Перегрузка вывода
    friend std::ostream& operator<<(std::ostream& os, const Module& module);
};
