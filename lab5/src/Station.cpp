#include "Station.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <numeric>
#include "Exceptions.h"

Station::Station() : day(1), energy(500), maxEnergy(1000), bits(100), stormDuration(0), isCoolantLeaking(false) {}

Station::~Station() {}

void Station::ClearMemory() {
    modules.clear();
    robots.clear();
}

void Station::Init(std::string name) {
    stationName = name;
    ClearMemory();

    modules.push_back(std::make_shared<ArchiveModule>());
    modules.push_back(std::make_shared<ControlCenterModule>());
    modules.push_back(std::make_shared<HousingModule>());
    modules.push_back(std::make_shared<GeneratorModule>());

    robots.push_back(std::make_unique<IntegratorRobot>("R-01"));
    robots.push_back(std::make_unique<IntegratorRobot>("R-02"));
    robots.push_back(std::make_unique<KeeperRobot>("Ева"));
    robots.push_back(std::make_unique<KeeperRobot>("Адам"));
    
    for (auto& r : robots) r->SetAge(6);

    logs.push_back("Система инициализирована. Архитектура 3.0 (Smart RAII) активна.");
}

void Station::ProcessDay() {
    logs.clear();
    isCoolantLeaking = false;
    for (auto& m : modules) m->SetActive(true); // Сброс статуса (для последствий метеорита)

    // Квантовый шторм
    if (stormDuration > 0) {
        stormDuration--;
        logs.push_back("СТАТУС: Внутри квантового шторма! (Осталось " + std::to_string(stormDuration) + " дн.)");
        
        if (rand() % 100 < 50) {
            int event = rand() % 4;
            if (event == 0) throw PowerSurgeException();
            else if (event == 1) throw FirmwareGlitchException();
            else if (event == 2) throw MeteorStrikeException();
            else throw CoolantLeakException();
        }
    } else if (day > 10 && (rand() % 100 < 20)) {
        stormDuration = 2 + (rand() % 4);
        logs.push_back("ТРЕВОГА: Вход в область квантового шторма на " + std::to_string(stormDuration) + " дн.!");
    }
    
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
        if (m->IsActive()) {
            totalE += m->GetEnergyDelta();
            totalD += m->GetDataDelta();
        }
    }

    for (auto& r : robots) {
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
    for (auto& m : modules) capacity += m->GetHousingCapacity();

    int occupancy = 0;
    for (auto& r : robots) occupancy += r->GetHousingNeed();

    if (occupancy > capacity) {
        int penalty = 15; 
        logs.push_back("КРИТИЧЕСКОЕ ПЕРЕНАСЕЛЕНИЕ! Штраф к шасси.");
        for (auto& r : robots) {
            r->TakeDamage(penalty, 0);
        }
    }
}

void Station::ProcessSignal() {
    if (stormDuration > 0) return; // В шторме сигнал не ловится

    double totalPower = 0;
    for (auto& r : robots) totalPower += r->GetPowerContribution();

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
            robots.push_back(std::make_unique<IntegratorRobot>(n));
            logs.push_back("АРХИВ: Синтезирован новый Интегратор.");
        } else if (choice == 2) {
            robots.push_back(std::make_unique<KeeperRobot>(n));
            logs.push_back("АРХИВ: Восстановлен Хранитель.");
        } else {
            robots.push_back(std::make_unique<LocalCalculatorRobot>(n));
            logs.push_back("АРХИВ: Создан Локальный вычислитель.");
        }
    } else {
        logs.push_back("ОШИБКА: Мало ресурсов (нужно 150 Э / 150 Б).");
    }
}

void Station::SynthesizeConsciousness(int idxA, int idxB) {
    logs.clear();
    if (idxA >= 0 && idxA < (int)robots.size() && idxB >= 0 && idxB < (int)robots.size() && idxA != idxB) {
        Robot* rA = robots[idxA].get();
        Robot* rB = robots[idxB].get();
        if (rA->GetAge() > 5 && rB->GetAge() > 5) {
            int cost = 100; // Только шасси (Энергия)
            if (energy >= cost) {
                energy -= cost;
                auto child = *rA + *rB;
                robots.push_back(std::move(child));
                std::string msg = "СИНТЕЗ: Успешно создан новый робот: " + child->GetName();
                logs.push_back(msg);
                std::cout << "\n[!] " << msg << "\n";
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
        Robot* rA = robots[idxA].get();
        Robot* rB = robots[idxB].get();
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
    std::shared_ptr<Module> newMod = nullptr;

    if (isCoolantLeaking) {
        logs.push_back("СТРОЙКА: ОШИБКА! Утечка охладителя блокирует терминал.");
        return;
    }

    if (choice == 1) { newMod = std::make_shared<ArchiveModule>(); costE = 100; costB = 100; }
    else if (choice == 2) { newMod = std::make_shared<ControlCenterModule>(); costE = 200; costB = 100; }
    else if (choice == 3) { newMod = std::make_shared<HousingModule>(); costE = 150; costB = 50; }
    else if (choice == 4) { newMod = std::make_shared<GeneratorModule>(); costE = 300; costB = 200; }

    if (newMod) {
        if (energy >= costE && bits >= costB) {
            energy -= costE;
            bits -= costB;
            modules.push_back(newMod);
            logs.push_back("СТРОЙКА: Возведен новый " + newMod->GetTypeName());
        } else {
            logs.push_back("СТРОЙКА: Недостаточно ресурсов!");
        }
    }
}

void Station::UpgradeModule(int index) {
    logs.clear();
    if (index >= 0 && index < (int)modules.size()) {
        if (isCoolantLeaking) {
            logs.push_back("АПГРЕЙД: ОШИБКА! Системы охлаждения нестабильны.");
            return;
        }

        auto& m = modules[index];
        
        if (m->GetLevel() >= 10) {
            logs.push_back("АПГРЕЙД: Максимальный уровень (10) достигнут!");
            return;
        }

        int cost = m->GetLevel() * 100;
        
        if (energy >= cost && bits >= cost) {
            energy -= cost;
            bits -= cost;
            m->Upgrade();
            std::string msg = "АПГРЕЙД: " + m->GetTypeName() + " улучшен до уровня " + std::to_string(m->GetLevel()) + " (Затрачено: " + std::to_string(cost) + " Э / " + std::to_string(cost) + " Д)";
            logs.push_back(msg);
            std::cout << "\n[!] " << msg << "\n";
        } else {
            std::cout << "\n[!] ОШИБКА: Недостаточно ресурсов для апгрейда (нужно " << cost << " Э / " << cost << " Д)!\n";
            logs.push_back("АПГРЕЙД: Недостаточно ресурсов.");
        }
    }
}

void Station::CombineModules(int idxA, int idxB) {
    logs.clear();
    if (idxA >= 0 && idxA < (int)modules.size() && idxB >= 0 && idxB < (int)modules.size() && idxA != idxB) {
        auto& mA = modules[idxA];
        auto& mB = modules[idxB];
        auto newMod = *mA + *mB;
        if (newMod) {
            std::string msg = "СБОРКА: Модули объединены! Создан " + newMod->GetTypeName() + " ур. " + std::to_string(newMod->GetLevel());
            logs.push_back(msg);
            std::cout << "\n[!] " << msg << "\n";
            int maxIdx = std::max(idxA, idxB);
            int minIdx = std::min(idxA, idxB);
            modules.erase(modules.begin() + maxIdx);
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
    for (auto& r : robots) totalPower += r->GetPowerContribution();

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

void Station::PrintAnalytics() const {
    std::cout << "\n========================================================\n";
    std::cout << "             ТЕРМИНАЛ АНАЛИТИКИ (v3.0)                \n";
    std::cout << "========================================================\n";

    // 1. Перекличка (sort robots by name)
    std::vector<Robot*> sortedRobots;
    std::for_each(robots.begin(), robots.end(), [&](const std::unique_ptr<Robot>& r) {
        sortedRobots.push_back(r.get());
    });
    std::sort(sortedRobots.begin(), sortedRobots.end(), [](Robot* a, Robot* b) {
        return a->GetName() < b->GetName();
    });
    std::cout << "--- [ПЕРЕКЛИЧКА: ПО ИМЕНИ] ---\n";
    std::for_each(sortedRobots.begin(), sortedRobots.end(), [](Robot* r) {
        std::cout << " > " << *r << "\n";
    });

    // 2. Инвентаризация (sort modules by name/type)
    std::vector<std::shared_ptr<Module>> sortedModules = modules;
    std::sort(sortedModules.begin(), sortedModules.end(), [](const std::shared_ptr<Module>& a, const std::shared_ptr<Module>& b) {
        return a->GetTypeName() < b->GetTypeName();
    });
    std::cout << "\n--- [ИНВЕНТАРИЗАЦИЯ: ПО ТИПУ] ---\n";
    std::for_each(sortedModules.begin(), sortedModules.end(), [](const std::shared_ptr<Module>& m) {
        std::cout << " > " << *m << "\n";
    });

    // 3. Оценка потерь (count_if chassis < 50)
    int damagedCount = std::count_if(robots.begin(), robots.end(), [](const std::unique_ptr<Robot>& r) {
        return r->GetChassis() < 50;
    });
    std::cout << "\n--- [ОЦЕНКА ПОТЕРЬ] ---\n";
    std::cout << " Юнитов с критическим износом шасси (<50%): " << damagedCount << "\n";

    // 4. Диагностика (Option 8: for_each diagnostic)
    std::cout << "\n--- [ДИАГНОСТИКА СИСТЕМ (ОПЦИЯ 8)] ---\n";
    std::for_each(modules.begin(), modules.end(), [](const std::shared_ptr<Module>& m) {
        std::cout << " [INFO] " << m->GetTypeName() << " (Ур. " << m->GetLevel() << ")"
                  << " | Ресурс: " << m->GetEnergyDelta() << " E / " << m->GetDataDelta() << " D"
                  << " | Активен: " << (m->IsActive() ? "YES" : "NO") << "\n";
    });

    // Доп: Суммарная мощность (из варианта 7 для примера, но оставим по заданию)
    int totalPower = std::accumulate(robots.begin(), robots.end(), 0, [](int sum, const std::unique_ptr<Robot>& r) {
        return sum + r->GetPowerContribution();
    });
    std::cout << "\n ОБЩАЯ ВЫЧИСЛИТЕЛЬНАЯ МОЩНОСТЬ: " << totalPower << "\n";
    std::cout << "========================================================\n";
}

bool Station::IsGameOver() const {
    if (robots.empty() && day > 1) return true;
    if (energy <= 0 && bits <= 0 && day > 1) return true;
    return false;
}

void Station::ApplyPowerSurgePenalty() {
    energy -= 50;
    if (energy < 0) energy = 0;
    logs.push_back("ШТРАФ: Потеряно 50 Энергии из-за скачка напряжения.");
}

void Station::ApplyFirmwareGlitchPenalty() {
    for (auto& r : robots) {
        int newFw = r->GetFirmware() - 10;
        if (newFw < 0) newFw = 0;
        r->SetFirmware(newFw);
    }
    logs.push_back("ШТРАФ: Прошивка всех роботов упала на 10%.");
}

void Station::ApplyMeteorStrikePenalty() {
    if (!modules.empty()) {
        int idx = rand() % modules.size();
        modules[idx]->SetActive(false);
        logs.push_back("ШТРАФ: Модуль " + modules[idx]->GetTypeName() + " поврежден и отключен на 1 день.");
    }
}

void Station::ApplyCoolantLeakPenalty() {
    isCoolantLeaking = true;
    logs.push_back("ШТРАФ: Утечка охладителя. Строительство и модернизация временно невозможны.");
}

void Station::AdvanceDayOnException() {
    day++;
    logs.push_back("День завершен аварийно из-за критического сбоя.");
}
