#pragma once
#include "Module.h"

class GeneratorModule : public Module {
public:
    int GetEnergyDelta() const override;
    int GetDataDelta() const override;
    int GetHousingCapacity() const override;
    std::string GetTypeName() const override;
    Module* CloneWithLevel(int newLevel) const override;
};
