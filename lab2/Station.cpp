#include "Station.h"
#include <iostream>
#include <algorithm>
#include <cmath>

Station::Station() : day(1), energy(500), maxEnergy(1000), bits(100) {}

void Station::Init(std::string name) {
    stationName = name;
    modules.push_back(Module(ModuleType::ARCHIVE));
    modules.push_back(Module(ModuleType::CONTROL_CENTER));
    modules.push_back(Module(ModuleType::HOUSING));
    modules.push_back(Module(ModuleType::GENERATOR));

    robots.push_back(Robot("R-01", Faction::INTEGRATOR));
    robots.push_back(Robot("R-02", Faction::INTEGRATOR));
    robots.push_back(Robot("Ева", Faction::KEEPER));
    robots.push_back(Robot("Адам", Faction::KEEPER));
}

void Station::ProcessDay() {
    logs.clear();
    ProcessProduction();
    ProcessHousing();
    ProcessSignal();
    ProcessTaxes();
    ProcessCleanup();
    day++;
}

void Station::ProcessProduction() {
    int totalE = 0, totalD = 0;
    for (auto& m : modules) {
        totalE += m.GetEnergyOutput();
        totalD += m.GetDataOutput();
    }
    for (auto& r : robots) {
        auto res = r.ProduceResources();
        totalE += res.first;
        totalD += res.second;
        r.TakeDamage(5, 5); // Базовое старение
    }
    energy += totalE;
    bits += totalD;
    if (energy > maxEnergy) energy = maxEnergy;
    logs.push_back("Ресурсы: Энергия " + std::to_string(totalE) + ", Данные " + std::to_string(totalD));
}

void Station::ProcessHousing() {
    int capacity = 0;
    for (auto& m : modules) capacity += m.GetHousingCapacity();
    
    int need = 0;
    for (auto& r : robots) need += r.GetHousingNeed();
    
    if (need > capacity) {
        logs.push_back("ВНИМАНИЕ: Перенаселение! Роботы повреждают шасси.");
        for (auto& r : robots) r.TakeDamage(15, 0); // 5-кратный урон (5 база + 15 штраф)
    }
}

void Station::ProcessSignal() {
    // Шанс = Power / (Power + Robots * 10)
    double power = std::abs(modules[1].GetEnergyOutput()); // Мощность ЦУ
    double interference = robots.size() * 10.0;
    double chance = (power / (power + interference)) * 100.0;
    
    if ((rand() % 100) < chance) {
        bits += 100;
        logs.push_back("УСПЕХ: Пойман сигнал выживших! Получено +100 бит.");
    }
}

void Station::ProcessTaxes() {
    if (day % 5 == 0) {
        int tax = energy * 0.1;
        if (energy > 0) {
            energy -= tax;
            logs.push_back("НАЛОГ: Корпорация изъяла " + std::to_string(tax) + " энергии.");
        } else {
            int bitTax = bits * 0.2;
            bits -= bitTax;
            logs.push_back("НАЛОГ: Энергии нет. Корпорация изъяла " + std::to_string(bitTax) + " бит (двойная цена).");
        }
    }
}

void Station::ProcessCleanup() {
    auto it = std::remove_if(robots.begin(), robots.end(), [](const Robot& r) {
        return r.IsDead();
    });
    if (it != robots.end()) {
        logs.push_back("СИСТЕМА: Некоторые оболочки вышли из строя.");
        robots.erase(it, robots.end());
    }
}

void Station::PrintStatus() const {
    std::cout << "\n--- СТАНЦИЯ: " << stationName << " | ДЕНЬ " << day << " ---\n";
    std::cout << "Энергия: [" << energy << "/" << maxEnergy << "] | Данные: " << bits << "\n";
    std::cout << "Роботов в сети: " << robots.size() << "\n";
    std::cout << "--- СОБЫТИЯ ---\n";
    for (const auto& log : logs) std::cout << "- " << log << "\n";
    std::cout << "-------------------------------\n";
}

bool Station::IsGameOver() const {
    return (robots.empty() || (energy <= 0 && bits <= 0));
}