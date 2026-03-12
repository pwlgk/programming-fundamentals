#pragma once
#include <string>

enum class ModuleType { ARCHIVE, CONTROL_CENTER, HOUSING, GENERATOR };

class Module {
private:
    ModuleType type;
    int level;
    bool isActive;

public:
    Module(ModuleType t);
    
    int GetEnergyOutput() const;  // Положительное - вырабатывает, отрицательное - тратит
    int GetDataOutput() const;
    int GetHousingCapacity() const;
    std::string GetTypeName() const;
    
    bool IsActive() const { return isActive; }
    void SetActive(bool status) { isActive = status; }
};