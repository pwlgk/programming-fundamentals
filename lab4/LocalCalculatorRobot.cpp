#include "LocalCalculatorRobot.h"

LocalCalculatorRobot::LocalCalculatorRobot(std::string n) : Robot(n) {}
std::pair<int, int> LocalCalculatorRobot::ProduceResources() const { 
    return {static_cast<int>(10 * GetEfficiencyModifier()), static_cast<int>(10 * GetEfficiencyModifier())}; 
}
int LocalCalculatorRobot::GetHousingNeed() const { return 1; }
std::string LocalCalculatorRobot::GetFactionName() const { return "Локальный вычислитель"; }
int LocalCalculatorRobot::GetPowerContribution() const { return 0; }
