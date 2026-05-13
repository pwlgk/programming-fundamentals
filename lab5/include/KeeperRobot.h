#pragma once
#include "Robot.h"

class KeeperRobot : public Robot {
public:
    KeeperRobot(std::string n);
    std::pair<int, int> ProduceResources() const override;
    int GetHousingNeed() const override;
    std::string GetFactionName() const override;
    int GetPowerContribution() const override;
};
