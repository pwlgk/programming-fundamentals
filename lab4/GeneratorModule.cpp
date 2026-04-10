#include "GeneratorModule.h"

int GeneratorModule::GetEnergyDelta() const { return 250 * GetLevel(); }
int GeneratorModule::GetDataDelta() const { return 0; }
int GeneratorModule::GetHousingCapacity() const { return 0; }
std::string GeneratorModule::GetTypeName() const { return "Генераторный модуль"; }

Module* GeneratorModule::CloneWithLevel(int newLevel) const {
    GeneratorModule* m = new GeneratorModule();
    while (m->GetLevel() < newLevel) m->Upgrade();
    return m;
}
