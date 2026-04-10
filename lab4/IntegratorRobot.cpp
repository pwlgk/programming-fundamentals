#include "IntegratorRobot.h"

IntegratorRobot::IntegratorRobot(std::string n) : Robot(n) {}
std::pair<int, int> IntegratorRobot::ProduceResources() const { 
    return {static_cast<int>(25 * GetEfficiencyModifier()), static_cast<int>(5 * GetEfficiencyModifier())}; 
}
int IntegratorRobot::GetHousingNeed() const { return 1; }
std::string IntegratorRobot::GetFactionName() const { return "Интегратор"; }
int IntegratorRobot::GetPowerContribution() const { return 10; }
