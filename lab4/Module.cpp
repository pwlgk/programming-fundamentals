#include "Module.h"

Module::Module() : level(1), isActive(true) {}
Module::~Module() {}

int Module::GetLevel() const { return level; }
void Module::Upgrade() { level++; }
bool Module::IsActive() const { return isActive; }
void Module::SetActive(bool status) { isActive = status; }

Module* Module::operator+(const Module& other) const {
    if (GetTypeName() == other.GetTypeName() && GetLevel() == other.GetLevel()) {
        return CloneWithLevel(GetLevel() + 1);
    }
    return nullptr;
}

std::ostream& operator<<(std::ostream& os, const Module& module) {
    os << "[" << module.GetTypeName() << "] Ур: " << module.GetLevel() 
       << " | Акт: " << (module.IsActive() ? "Да" : "Нет")
       << " | Энергия: " << module.GetEnergyDelta() 
       << " | Данные: " << module.GetDataDelta()
       << " | Мест: " << module.GetHousingCapacity();
    return os;
}
