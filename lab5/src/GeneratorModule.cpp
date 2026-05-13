#include "GeneratorModule.h"

int GeneratorModule::GetEnergyDelta() const { return 250 * GetLevel(); }
int GeneratorModule::GetDataDelta() const { return 0; }
int GeneratorModule::GetHousingCapacity() const { return 0; }
std::string GeneratorModule::GetTypeName() const { return "Генераторный модуль"; }

std::shared_ptr<Module> GeneratorModule::CloneWithLevel(int newLevel) const {
    auto m = std::make_shared<GeneratorModule>();
    while (m->GetLevel() < newLevel) m->Upgrade();
    return m;
}
