#pragma once
#include "Robot.h"

class LocalCalculatorRobot : public Robot {
public:
    LocalCalculatorRobot(std::string n);
    std::pair<int, int> ProduceResources() const override;
    int GetHousingNeed() const override;
    std::string GetFactionName() const override;
    int GetPowerContribution() const override;
};
