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
    
    // Дадим им возраст, чтобы сразу тестить синтез
    for (auto r : robots) r->SetAge(6);

    logs.push_back("Система инициализирована. Архитектура 2.0 (Полиморфная) + Lab4 активны.");
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

    for (auto m : modules) {
        if (m->IsActive()) {
            totalE += m->GetEnergyDelta();
            totalD += m->GetDataDelta();
        }
    }

    for (auto r : robots) {
        auto res = r->ProduceResources();
        totalE += res.first;
        totalD += res.second;
        
        r->SetAge(r->GetAge() + 1);
        --(*r); // Ежедневный износ
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
        logs.push_back("КРИТИЧЕСКОЕ ПЕРЕНАСЕЛЕНИЕ! Штраф к шасси.");
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
        logs.push_back("СИГНАЛ: Поймана передача! +" + std::to_string(bonus) + " бит.");
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
            logs.push_back("АРХИВ: Создан Локальный вычислитель.");
        }
    } else {
        logs.push_back("ОШИБКА: Мало ресурсов (нужно 150 Э / 150 Б).");
    }
}

void Station::SynthesizeConsciousness(int idxA, int idxB) {
    logs.clear();
    if (idxA >= 0 && idxA < (int)robots.size() && idxB >= 0 && idxB < (int)robots.size() && idxA != idxB) {
        Robot* rA = robots[idxA];
        Robot* rB = robots[idxB];
        if (rA->GetAge() > 5 && rB->GetAge() > 5) {
            int cost = 100; // Только шасси (Энергия)
            if (energy >= cost) {
                energy -= cost;
                Robot* child = *rA + *rB;
                robots.push_back(child);
                logs.push_back("СИНТЕЗ: Успешно создан новый робот: " + child->GetName());
            } else {
                logs.push_back("СИНТЕЗ: Недостаточно энергии (нужно " + std::to_string(cost) + ")");
            }
        } else {
            logs.push_back("СИНТЕЗ: Оба родителя должны быть старше 5 дней!");
        }
    } else {
        logs.push_back("СИНТЕЗ: Некорректные индексы!");
    }
}

void Station::CheckClones(int idxA, int idxB) {
    logs.clear();
    if (idxA >= 0 && idxA < (int)robots.size() && idxB >= 0 && idxB < (int)robots.size() && idxA != idxB) {
        Robot* rA = robots[idxA];
        Robot* rB = robots[idxB];
        if (*rA == *rB) {
            logs.push_back("ДЕТЕКТОР: ОБНАРУЖЕНЫ КЛОНЫ! " + rA->GetName() + " и " + rB->GetName() + " идентичны.");
        } else {
            logs.push_back("ДЕТЕКТОР: Ошибок дефрагментации нет. Роботы уникальны.");
        }
    } else {
        logs.push_back("ДЕТЕКТОР: Некорректные индексы!");
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
            logs.push_back("АПГРЕЙД: Недостаточно ресурсов.");
        }
    }
}

void Station::CombineModules(int idxA, int idxB) {
    logs.clear();
    if (idxA >= 0 && idxA < (int)modules.size() && idxB >= 0 && idxB < (int)modules.size() && idxA != idxB) {
        Module* mA = modules[idxA];
        Module* mB = modules[idxB];
        Module* newMod = *mA + *mB;
        if (newMod) {
            logs.push_back("СБОРКА: Модули объединены! Создан " + newMod->GetTypeName() + " ур." + std::to_string(newMod->GetLevel()));
            int maxIdx = std::max(idxA, idxB);
            int minIdx = std::min(idxA, idxB);
            delete modules[maxIdx];
            modules.erase(modules.begin() + maxIdx);
            delete modules[minIdx];
            modules.erase(modules.begin() + minIdx);
            modules.push_back(newMod);
        } else {
            logs.push_back("СБОРКА: Модули несовместимы (разные типы или уровни).");
        }
    } else {
        logs.push_back("СБОРКА: Некорректные индексы!");
    }
}

void Station::RepairRobot(int index) {
    logs.clear();
    if (index >= 0 && index < (int)robots.size()) {
        int costE = 50;
        int costB = 50;
        if (energy >= costE && bits >= costB) {
            energy -= costE;
            bits -= costB;
            ++(*robots[index]);
            logs.push_back("РЕМОНТ: Робот " + robots[index]->GetName() + " полностью восстановлен.");
        } else {
            logs.push_back("РЕМОНТ: Недостаточно ресурсов (50 Э / 50 Д).");
        }
    }
}

void Station::PrintStatus() const {
    int totalPower = 0;
    for (auto r : robots) totalPower += r->GetPowerContribution();

    std::cout << "\n========================================================\n";
    std::cout << " СТАНЦИЯ: " << stationName << " | ЦИКЛ: " << day << "\n";
    std::cout << " Энергия: [" << energy << "/" << maxEnergy << "] | Данные: " << bits << "\n";
    std::cout << " Роботы: " << robots.size() << " | Модули: " << modules.size() << "\n";
    std::cout << " МОЩНОСТЬ СЕТИ: " << totalPower << " единиц\n";
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
        std::cout << i << ". " << *modules[i] << "\n";
    }
}

void Station::PrintRobots() const {
    std::cout << "\n--- СПИСОК РОБОТОВ ---\n";
    for (size_t i = 0; i < robots.size(); ++i) {
        std::cout << i << ". " << *robots[i] << "\n";
    }
}

bool Station::IsGameOver() const {
    if (robots.empty() && day > 1) return true;
    if (energy <= 0 && bits <= 0 && day > 1) return true;
    return false;
}