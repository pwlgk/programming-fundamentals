#include "Module.h"

// Конструктор: уровень по умолчанию 1, модуль активен сразу
Module::Module(ModuleType t) : type(t), level(1), isActive(true) {}

int Module::GetEnergyOutput() const {
    if (!isActive) return 0;

    switch (type) {
        case ModuleType::ARCHIVE:
            // По ТЗ: не тратит на поддержание, но тратит немного на выработку данных
            return -10; 
        case ModuleType::CONTROL_CENTER:
            // "Сердце" станции, потребляет энергию на работу всей системы
            return -100;
        case ModuleType::HOUSING:
            // Базовое потребление жилого отсека (свет, фильтрация воздуха)
            return -20;
        case ModuleType::GENERATOR:
            // Основной источник энергии (солнечные панели/реакторы)
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
            // По ТЗ: ровно 8 ячеек для размещения роботов
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