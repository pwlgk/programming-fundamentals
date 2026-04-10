#include "Module.h"

Module::Module(ModuleType t) : type(t), level(1), isActive(true) {}

int Module::GetEnergyOutput() const {
    if (!isActive) return 0;

    switch (type) {
        case ModuleType::ARCHIVE:
            return -10; 
        case ModuleType::CONTROL_CENTER:
            return -100;
        case ModuleType::HOUSING:
            return -20;
        case ModuleType::GENERATOR:
            return 250;
        default:
            return 0;
    }
}

int Module::GetDataOutput() const {
    if (!isActive) return 0;

    switch (type) {
        case ModuleType::ARCHIVE:
            return 30;
        default:
            return 0;
    }
}

int Module::GetHousingCapacity() const {
    if (!isActive) return 0;

    switch (type) {
        case ModuleType::HOUSING:
            return 8;
        default:
            return 0;
    }
}

std::string Module::GetTypeName() const {
    switch (type) {
        case ModuleType::ARCHIVE:        return "Архив";
        case ModuleType::CONTROL_CENTER: return "Центр управления";
        case ModuleType::HOUSING:        return "Жилой отсек";
        case ModuleType::GENERATOR:      return "Генераторный модуль";
        default:                         return "Неизвестный модуль";
    }
}