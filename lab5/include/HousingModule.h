#pragma once
#include "Module.h"

class HousingModule : public Module {
public:
    int GetEnergyDelta() const override;
    int GetDataDelta() const override;
    int GetHousingCapacity() const override;
    std::string GetTypeName() const override;
    std::shared_ptr<Module> CloneWithLevel(int newLevel) const override;
};
