#include "Robot.h"
#include "IntegratorRobot.h"
#include "KeeperRobot.h"
#include "LocalCalculatorRobot.h"
#include <random>

Robot::Robot(std::string n) : name(n), chassis(100), firmware(100), age(0), efficiencyModifier(1.0) {}
Robot::~Robot() {}

void Robot::TakeDamage(int chassisDmg, int firmwareDmg) {
    chassis -= chassisDmg;
    firmware -= firmwareDmg;
    if (chassis < 0) chassis = 0;
    if (firmware < 0) firmware = 0;
}

void Robot::Repair(int eAmount, int dAmount) {
    chassis += eAmount / 2;
    firmware += dAmount / 2;
    if (chassis > 100) chassis = 100;
    if (firmware > 100) firmware = 100;
}

bool Robot::IsDead() const { return (chassis <= 0 || firmware <= 0); }
std::string Robot::GetName() const { return name; }
int Robot::GetChassis() const { return chassis; }
int Robot::GetFirmware() const { return firmware; }
int Robot::GetAge() const { return age; }
double Robot::GetEfficiencyModifier() const { return efficiencyModifier; }

void Robot::SetChassis(int val) { chassis = val; }
void Robot::SetFirmware(int val) { firmware = val; }
void Robot::SetAge(int val) { age = val; }
void Robot::SetEfficiencyModifier(double val) { efficiencyModifier = val; }

Robot& Robot::operator--() {
    TakeDamage(10, 10);
    return *this;
}

Robot& Robot::operator++() {
    chassis = 100;
    firmware = 100;
    return *this;
}

bool Robot::operator==(const Robot& other) const {
    auto res1 = ProduceResources();
    auto res2 = other.ProduceResources();
    int eff1 = res1.first + res1.second;
    int eff2 = res2.first + res2.second;
    return (GetFactionName() == other.GetFactionName() && 
            eff1 == eff2 && 
            (chassis + firmware) == (other.chassis + other.firmware));
}

std::ostream& operator<<(std::ostream& os, const Robot& robot) {
    auto res = robot.ProduceResources();
    int eff = res.first + res.second;
    os << "[" << robot.GetName() << " | " << robot.GetFactionName() 
       << "] HP: " << (robot.GetChassis() + robot.GetFirmware())/2 
       << "% | Эфф: " << eff << " (x" << std::fixed << std::setprecision(2) << robot.GetEfficiencyModifier() << ")"
       << " | Pwr: " << robot.GetPowerContribution()
       << " | Возраст: " << robot.GetAge() << " дн.";
    return os;
}

Robot* Robot::operator+(const Robot& other) const {
    double mutation = 0.8 + static_cast<double>(rand()) / (RAND_MAX / (1.2 - 0.8));
    
    int childChassis = ((chassis + other.chassis) / 2) * mutation;
    int childFirmware = ((firmware + other.firmware) / 2) * mutation;
    double childEffMod = ((efficiencyModifier + other.efficiencyModifier) / 2.0) * mutation;
    
    if (childChassis > 100) childChassis = 100;
    if (childFirmware > 100) childFirmware = 100;
    
    std::string newName = "Synth-" + name.substr(0,2) + other.name.substr(0,2);
    
    int powerA = chassis + firmware;
    int powerB = other.chassis + other.firmware;
    
    Robot* newBorn = nullptr;
    if (powerA >= powerB) {
        if (GetFactionName() == "Интегратор") newBorn = new IntegratorRobot(newName);
        else if (GetFactionName() == "Хранитель") newBorn = new KeeperRobot(newName);
        else newBorn = new LocalCalculatorRobot(newName);
    } else {
        if (other.GetFactionName() == "Интегратор") newBorn = new IntegratorRobot(newName);
        else if (other.GetFactionName() == "Хранитель") newBorn = new KeeperRobot(newName);
        else newBorn = new LocalCalculatorRobot(newName);
    }
    
    newBorn->SetChassis(childChassis);
    newBorn->SetFirmware(childFirmware);
    newBorn->SetEfficiencyModifier(childEffMod);
    newBorn->SetAge(0);
    
    return newBorn;
}
