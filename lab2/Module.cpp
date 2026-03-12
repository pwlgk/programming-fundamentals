#include "Module.h"

Module::Module(ModuleType t) : type(t), level(1), isActive(true) {}

int Module::GetEnergyOutput() const {
    if (!isActive) return 0;
    switch (type) {
        case ModuleType::CONTROL_CENTER: return -50; // Потребляет
        case ModuleType::GENERATOR:      return 150; // Генерирует
        case ModuleType::HOUSING:        return -20; // Потребляет
        case ModuleType::ARCHIVE:        return 0;   // Пассивен
        default: return 0;
    }
}

int Module::GetDataOutput() const {
    if (!isActive) return 0;
    if (type == ModuleType::ARCHIVE) return 10;
    return 0;
}

int Module::GetHousingCapacity() const {
    return (type == ModuleType::HOUSING) ? 8 : 0;
}

std::string Module::GetTypeName() const {
    switch (type) {
        case ModuleType::ARCHIVE: return "Архив";
        case ModuleType::CONTROL_CENTER: return "Центр управления";
        case ModuleType::HOUSING: return "Жилой отсек";
        case ModuleType::GENERATOR: return "Генераторный модуль";
        default: return "Неизвестно";
    }
}