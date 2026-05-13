#include "HousingModule.h"

int HousingModule::GetEnergyDelta() const { return -20 * GetLevel(); }
int HousingModule::GetDataDelta() const { return 0; }
int HousingModule::GetHousingCapacity() const { return 8 * GetLevel(); }
std::string HousingModule::GetTypeName() const { return "Жилой отсек"; }

std::shared_ptr<Module> HousingModule::CloneWithLevel(int newLevel) const {
    auto m = std::make_shared<HousingModule>();
    while (m->GetLevel() < newLevel) m->Upgrade();
    return m;
}
