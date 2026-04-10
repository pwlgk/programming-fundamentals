#include "ControlCenterModule.h"

int ControlCenterModule::GetEnergyDelta() const { return -100 * GetLevel(); }
int ControlCenterModule::GetDataDelta() const { return 0; }
int ControlCenterModule::GetHousingCapacity() const { return 0; }
std::string ControlCenterModule::GetTypeName() const { return "Центр управления"; }

Module* ControlCenterModule::CloneWithLevel(int newLevel) const {
    ControlCenterModule* m = new ControlCenterModule();
    while (m->GetLevel() < newLevel) m->Upgrade();
    return m;
}
