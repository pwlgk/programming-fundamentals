#include "ArchiveModule.h"

int ArchiveModule::GetEnergyDelta() const { return -10 * GetLevel(); }
int ArchiveModule::GetDataDelta() const { return 30 * GetLevel(); }
int ArchiveModule::GetHousingCapacity() const { return 0; }
std::string ArchiveModule::GetTypeName() const { return "Архив"; }

std::shared_ptr<Module> ArchiveModule::CloneWithLevel(int newLevel) const {
    auto m = std::make_shared<ArchiveModule>();
    while (m->GetLevel() < newLevel) m->Upgrade();
    return m;
}
