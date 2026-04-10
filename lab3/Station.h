#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Robot.h"
#include "Module.h"

class Station {
private:
    std::string stationName;
    int day;
    int energy;
    int maxEnergy;
    int bits;

    // Списки указателей на объекты станции
    std::vector<Robot*> robots;
    std::vector<Module*> modules;

    std::vector<std::string> logs;

    void ProcessProduction();    // Шаг 1: Производство ресурсов
    void ProcessHousing();       // Шаг 2: Проверка жилых мест и урон
    void ProcessSignal();        // Шаг 3: Попытка поймать сигнал 
    void ProcessTaxes();         // Шаг 4: Налоги корпорации 
    void ProcessCleanup();       // Шаг 5: Удаление мертвых роботов

    void ClearMemory();          // Вспомогательный метод для очистки памяти

public:
    Station();
    ~Station();

    // Инициализация станции
    void Init(std::string name);

    // Запуск одного игрового дня
    void ProcessDay();

    // Создание нового робота (теперь 3 варианта)
    void SynthesizeRobot(int choice);

    // Строительство нового модуля
    void BuildModule(int choice);

    // Улучшение модуля
    void UpgradeModule(int index);

    // Вывод состояния станции в консоль
    void PrintStatus() const;
    void PrintModules() const;

    // Проверка условий проигрыша
    bool IsGameOver() const;

    int GetDay() const { return day; }
    int GetEnergy() const { return energy; }
    int GetBits() const { return bits; }
    size_t GetRobotCount() const { return robots.size(); }
    size_t GetModuleCount() const { return modules.size(); }
};