#pragma once
#include <string>

class Module {
protected:
    int level;
    bool isActive;

public:
    Module() : level(1), isActive(true) {}
    virtual ~Module() {}

    virtual int GetEnergyDelta() const = 0;
    virtual int GetDataDelta() const = 0;
    virtual int GetHousingCapacity() const = 0;
    virtual std::string GetTypeName() const = 0;
    
    int GetLevel() const { return level; }
    void Upgrade() { level++; }
    bool IsActive() const { return isActive; }
    void SetActive(bool status) { isActive = status; }
};

class ArchiveModule : public Module {
public:
    int GetEnergyDelta() const override { return -10 * level; }
    int GetDataDelta() const override { return 30 * level; }
    int GetHousingCapacity() const override { return 0; }
    std::string GetTypeName() const override { return "Архив"; }
};

class ControlCenterModule : public Module {
public:
    int GetEnergyDelta() const override { return -100 * level; }
    int GetDataDelta() const override { return 0; }
    int GetHousingCapacity() const override { return 0; }
    std::string GetTypeName() const override { return "Центр управления"; }
};

class HousingModule : public Module {
public:
    int GetEnergyDelta() const override { return -20 * level; }
    int GetDataDelta() const override { return 0; }
    int GetHousingCapacity() const override { return 8 * level; }
    std::string GetTypeName() const override { return "Жилой отсек"; }
};

class GeneratorModule : public Module {
public:
    int GetEnergyDelta() const override { return 250 * level; }
    int GetDataDelta() const override { return 0; }
    int GetHousingCapacity() const override { return 0; }
    std::string GetTypeName() const override { return "Генераторный модуль"; }
};