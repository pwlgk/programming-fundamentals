#include "Station.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <ctime>

Station::Station() : day(1), energy(500), maxEnergy(1000), bits(100) {}

void Station::Init(std::string name) {
    stationName = name;

    // Стартовый набор модулей по ТЗ
    modules.push_back(Module(ModuleType::ARCHIVE));
    modules.push_back(Module(ModuleType::CONTROL_CENTER));
    modules.push_back(Module(ModuleType::HOUSING));
    modules.push_back(Module(ModuleType::GENERATOR));

    // Стартовый набор роботов: 2 Интегратора, 2 Хранителя
    robots.push_back(Robot("R-01", Faction::INTEGRATOR));
    robots.push_back(Robot("R-02", Faction::INTEGRATOR));
    robots.push_back(Robot("Ева", Faction::KEEPER));
    robots.push_back(Robot("Адам", Faction::KEEPER));

    logs.push_back("Система инициализирована. Добро пожаловать, Администратор.");
}

void Station::ProcessDay() {
    logs.clear();
    
    ProcessProduction();    // 1. Добыча
    ProcessHousing();       // 2. Жилье и износ
    ProcessSignal();        // 3. Связь
    ProcessTaxes();         // 4. Налоги (Вариант 7)
    ProcessCleanup();       // 5. Очистка погибших

    day++;
}

void Station::ProcessProduction() {
    int totalE = 0, totalD = 0;

    // Ресурсы от модулей
    for (auto& m : modules) {
        totalE += m.GetEnergyOutput();
        totalD += m.GetDataOutput();
    }

    // Ресурсы от роботов и их старение
    for (auto& r : robots) {
        auto res = r.ProduceResources();
        totalE += res.first;
        totalD += res.second;
        r.TakeDamage(5, 5); // Базовое старение каждый день
    }

    energy += totalE;
    bits += totalD;

    // Ограничение по максимуму энергии
    if (energy > maxEnergy) energy = maxEnergy;
    if (energy < 0) energy = 0;

    logs.push_back("Баланс дня: Энергия " + std::to_string(totalE) + ", Данные " + std::to_string(totalD));
}

void Station::ProcessHousing() {
    int capacity = 0;
    for (auto& m : modules) capacity += m.GetHousingCapacity();

    int occupancy = 0;
    for (auto& r : robots) occupancy += r.GetHousingNeed();

    if (occupancy > capacity) {
        int penalty = 15; // Пятикратный урон (база 5 + штраф 15)
        logs.push_back("КРИТИЧЕСКОЕ ПЕРЕНАСЕЛЕНИЕ! Износ шасси увеличен.");
        for (auto& r : robots) {
            r.TakeDamage(penalty, 0);
        }
    }
}

void Station::ProcessSignal() {
    // Математическая модель: Шанс = МощностьЦУ / (МощностьЦУ + Роботы * 10)
    // Мощность ЦУ возьмем как 100 (модуль 1 в векторе - Control Center)
    double power = 100.0;
    double interference = robots.size() * 10.0;
    double chance = (power / (power + interference)) * 100.0;

    if ((rand() % 100) < (int)chance) {
        int bonus = 150;
        bits += bonus;
        logs.push_back("СИГНАЛ: Поймана передача! Получено " + std::to_string(bonus) + " бит данных.");
    } else {
        logs.push_back("СИГНАЛ: В эфире только цифровой шум (Шанс был " + std::to_string((int)chance) + "%).");
    }
}

void Station::ProcessTaxes() {
    // Вариант 7: Налог каждые 5 дней
    if (day % 5 == 0) {
        if (energy > 0) {
            int tax = energy * 0.10; // 10% энергии
            energy -= tax;
            logs.push_back("КОРПОРАЦИЯ: Списан налог " + std::to_string(tax) + " энергии.");
        } else {
            int tax = bits * 0.20; // 20% данных (двойная цена)
            bits -= tax;
            logs.push_back("КОРПОРАЦИЯ: Энергии нет! Изъято " + std::to_string(tax) + " бит данных.");
        }
    }
}

void Station::ProcessCleanup() {
    size_t initialCount = robots.size();
    
    // Идиома Erase-Remove для безопасного удаления из вектора
    robots.erase(std::remove_if(robots.begin(), robots.end(), [](const Robot& r) {
        return r.IsDead();
    }), robots.end());

    if (robots.size() < initialCount) {
        logs.push_back("ВНИМАНИЕ: " + std::to_string(initialCount - robots.size()) + " оболочек отключено (смерть).");
    }
}

void Station::SynthesizeRobot(int factionChoice) {
    int costE = 150;
    int costB = 150;

    if (energy >= costE && bits >= costB) {
        energy -= costE;
        bits -= costB;
        if (factionChoice == 1) {
            robots.push_back(Robot("Системный-" + std::to_string(robots.size() + 1), Faction::INTEGRATOR));
            logs.push_back("АРХИВ: Синтезирован новый Интегратор.");
        } else {
            robots.push_back(Robot("Хранитель-" + std::to_string(robots.size() + 1), Faction::KEEPER));
            logs.push_back("АРХИВ: Восстановлено сознание Хранителя.");
        }
    } else {
        logs.push_back("ОШИБКА: Недостаточно ресурсов для синтеза (нужно 150 Э / 150 Б).");
    }
}

void Station::PrintStatus() const {
    std::cout << "\n========================================================\n";
    std::cout << " СТАНЦИЯ: " << stationName << " | СИСТЕМНЫЙ ЦИКЛ (ДЕНЬ): " << day << "\n";
    std::cout << " Энергия: [" << energy << "/" << maxEnergy << "] | Данные (Биты): " << bits << "\n";
    std::cout << " Жители: " << robots.size() << " оболочек в сети\n";
    std::cout << "========================================================\n";
    std::cout << " ПОСЛЕДНИЕ СОБЫТИЯ:\n";
    for (const auto& log : logs) {
        std::cout << " > " << log << "\n";
    }
    std::cout << "========================================================\n";
}

bool Station::IsGameOver() const {
    // Проигрыш: нет роботов ИЛИ оба ресурса на нуле
    if (robots.empty()) return true;
    if (energy <= 0 && bits <= 0) return true;
    return false;
}