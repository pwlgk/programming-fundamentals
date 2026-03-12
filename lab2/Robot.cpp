#include "Robot.h"

Robot::Robot(std::string n, Faction f) : name(n), faction(f), chassis(100), firmware(100) {}

std::pair<int, int> Robot::ProduceResources() const {
    if (faction == Faction::INTEGRATOR) return {25, 5}; // Много энергии
    return {5, 25}; // Много данных
}

void Robot::TakeDamage(int cDmg, int fDmg) {
    chassis -= cDmg;
    firmware -= fDmg;
    if (chassis < 0) chassis = 0;
    if (firmware < 0) firmware = 0;
}

void Robot::Repair(int e, int d) {
    chassis += e / 2;    // Курс ремонта: 2 ед ресурса на 1% прочности
    firmware += d / 2;
    if (chassis > 100) chassis = 100;
    if (firmware > 100) firmware = 100;
}

bool Robot::IsDead() const {
    return (chassis <= 0 || firmware <= 0);
}

int Robot::GetHousingNeed() const {
    return (faction == Faction::KEEPER) ? 2 : 1;
}

std::string Robot::GetFactionName() const {
    return (faction == Faction::INTEGRATOR) ? "Интегратор" : "Хранитель";
}