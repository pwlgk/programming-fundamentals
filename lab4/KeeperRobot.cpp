#include "KeeperRobot.h"

KeeperRobot::KeeperRobot(std::string n) : Robot(n) {}
std::pair<int, int> KeeperRobot::ProduceResources() const { 
    return {static_cast<int>(5 * GetEfficiencyModifier()), static_cast<int>(25 * GetEfficiencyModifier())}; 
}
int KeeperRobot::GetHousingNeed() const { return 2; }
std::string KeeperRobot::GetFactionName() const { return "Хранитель"; }
int KeeperRobot::GetPowerContribution() const { return 10; }
