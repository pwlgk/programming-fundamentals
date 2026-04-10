#include "Station.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <ctime>

Station::Station() : day(1), energy(500), maxEnergy(1000), bits(100) {}

Station::~Station() {
    ClearMemory();
}

void Station::ClearMemory() {
    for (auto m : modules) delete m;
    modules.clear();
    for (auto r : robots) delete r;
    robots.clear();
}

void Station::Init(std::string name) {
    stationName = name;
    ClearMemory();

    modules.push_back(new ArchiveModule());
    modules.push_back(new ControlCenterModule());
    modules.push_back(new HousingModule());
    modules.push_back(new GeneratorModule());

    robots.push_back(new IntegratorRobot("R-01"));
    robots.push_back(new IntegratorRobot("R-02"));
    robots.push_back(new KeeperRobot("Ева"));
    robots.push_back(new KeeperRobot("Адам"));

    logs.push_back("Система инициализирована. Архитектура 2.0 (Полиморфная) активна.");
}

void Station::ProcessDay() {
    logs.clear();
    
    ProcessProduction();    // 1. Добыча
    ProcessHousing();       // 2. Жилье и износ
    ProcessSignal();        // 3. Связь
    ProcessTaxes();         // 4. Налоги 
    ProcessCleanup();       // 5. Очистка погибших

    day++;
}

void Station::ProcessProduction() {
    int totalE = 0, totalD = 0;

    // Магия полиморфизма для модулей
    for (auto m : modules) {
        if (m->IsActive()) {
            totalE += m->GetEnergyDelta();
            totalD += m->GetDataDelta();
        }
    }

    // Магия полиморфизма для роботов
    for (auto r : robots) {
        auto res = r->ProduceResources();
        totalE += res.first;
        totalD += res.second;
        r->TakeDamage(5, 5); 
    }

    energy += totalE;
    bits += totalD;

    if (energy > maxEnergy) energy = maxEnergy;
    if (energy < 0) energy = 0;
    if (bits < 0) bits = 0;

    logs.push_back("Баланс дня: Энергия " + std::to_string(totalE) + ", Данные " + std::to_string(totalD));
}

void Station::ProcessHousing() {
    int capacity = 0;
    for (auto m : modules) capacity += m->GetHousingCapacity();

    int occupancy = 0;
    for (auto r : robots) occupancy += r->GetHousingNeed();

    if (occupancy > capacity) {
        int penalty = 15; 
        logs.push_back("КРИТИЧЕСКОЕ ПЕРЕНАСЕЛЕНИЕ! Износ шасси увеличен.");
        for (auto r : robots) {
            r->TakeDamage(penalty, 0);
        }
    }
}

void Station::ProcessSignal() {
    double totalPower = 0;
    for (auto r : robots) totalPower += r->GetPowerContribution();

    double interference = robots.size() * 10.0;
    double chance = 0;
    if (totalPower + interference > 0) {
        chance = (totalPower / (totalPower + interference)) * 100.0;
    }

    if ((rand() % 100) < (int)chance) {
        int bonus = 150;
        bits += bonus;
        logs.push_back("СИГНАЛ: Поймана передача! Получено " + std::to_string(bonus) + " бит данных.");
    } else {
        logs.push_back("СИГНАЛ: Шум (Шанс был " + std::to_string((int)chance) + "%). Мощность сети: " + std::to_string((int)totalPower));
    }
}

void Station::ProcessTaxes() {
    if (day % 5 == 0) {
        int tax = 0;
        if (energy > 0) {
            tax = energy * 0.10;
            energy -= tax;
            logs.push_back("КОРПОРАЦИЯ: Налог " + std::to_string(tax) + " энергии.");
        } else {
            tax = bits * 0.20;
            bits -= tax;
            logs.push_back("КОРПОРАЦИЯ: Энергии нет! Изъято " + std::to_string(tax) + " данных.");
        }
    }
}

void Station::ProcessCleanup() {
    size_t initialCount = robots.size();
    
    for (auto it = robots.begin(); it != robots.end(); ) {
        if ((*it)->IsDead()) {
            delete *it;
            it = robots.erase(it);
        } else {
            ++it;
        }
    }

    if (robots.size() < initialCount) {
        logs.push_back("ВНИМАНИЕ: " + std::to_string(initialCount - robots.size()) + " юнитов отключено.");
    }
}

void Station::SynthesizeRobot(int choice) {
    logs.clear();
    int costE = 150, costB = 150;

    if (energy >= costE && bits >= costB) {
        energy -= costE;
        bits -= costB;
        std::string n = "Unit-" + std::to_string(robots.size() + 1);
        
        if (choice == 1) {
            robots.push_back(new IntegratorRobot(n));
            logs.push_back("АРХИВ: Синтезирован новый Интегратор.");
        } else if (choice == 2) {
            robots.push_back(new KeeperRobot(n));
            logs.push_back("АРХИВ: Восстановлен Хранитель.");
        } else {
            robots.push_back(new LocalCalculatorRobot(n));
            logs.push_back("АРХИВ: Создан Локальный вычислитель .");
        }
    } else {
        logs.push_back("ОШИБКА: Мало ресурсов (нужно 150 Э / 150 Б).");
    }
}

void Station::BuildModule(int choice) {
    logs.clear();
    int costE = 0, costB = 0;
    Module* newMod = nullptr;

    if (choice == 1) { newMod = new ArchiveModule(); costE = 100; costB = 100; }
    else if (choice == 2) { newMod = new ControlCenterModule(); costE = 200; costB = 100; }
    else if (choice == 3) { newMod = new HousingModule(); costE = 150; costB = 50; }
    else if (choice == 4) { newMod = new GeneratorModule(); costE = 300; costB = 200; }

    if (newMod) {
        if (energy >= costE && bits >= costB) {
            energy -= costE;
            bits -= costB;
            modules.push_back(newMod);
            logs.push_back("СТРОЙКА: Возведен новый " + newMod->GetTypeName());
        } else {
            delete newMod;
            logs.push_back("СТРОЙКА: Недостаточно ресурсов!");
        }
    }
}

void Station::UpgradeModule(int index) {
    logs.clear();
    if (index >= 0 && index < (int)modules.size()) {
        Module* m = modules[index];
        
        if (m->GetLevel() >= 10) {
            logs.push_back("АПГРЕЙД: Максимальный уровень (10) достигнут!");
            return;
        }

        int cost = m->GetLevel() * 100;
        
        if (energy >= cost && bits >= cost) {
            energy -= cost;
            bits -= cost;
            m->Upgrade();
            logs.push_back("АПГРЕЙД: " + m->GetTypeName() + " улучшен до уровня " + std::to_string(m->GetLevel()));
        } else {
            logs.push_back("АПГРЕЙД: Недостаточно ресурсов (нужно по " + std::to_string(cost) + ").");
        }
    }
}

void Station::PrintStatus() const {
    std::cout << "\n========================================================\n";
    std::cout << " СТАНЦИЯ: " << stationName << " | ЦИКЛ: " << day << "\n";
    std::cout << " Энергия: [" << energy << "/" << maxEnergy << "] | Данные: " << bits << "\n";
    std::cout << " Роботы: " << robots.size() << " | Модули: " << modules.size() << "\n";
    std::cout << "========================================================\n";
    if (!logs.empty()) {
        std::cout << " СОБЫТИЯ:\n";
        for (const auto& log : logs) std::cout << " > " << log << "\n";
        std::cout << "========================================================\n";
    }
}

void Station::PrintModules() const {
    std::cout << "\n--- СПИСОК МОДУЛЕЙ ---\n";
    for (size_t i = 0; i < modules.size(); ++i) {
        std::cout << i << ". " << modules[i]->GetTypeName() << " (Ур. " << modules[i]->GetLevel() << ")\n";
    }
}

bool Station::IsGameOver() const {
    if (robots.empty() && day > 1) return true;
    if (energy <= 0 && bits <= 0 && day > 1) return true;
    return false;
}