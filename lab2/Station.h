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

    // Списки объектов станции
    std::vector<Robot> robots;
    std::vector<Module> modules;

    std::vector<std::string> logs;

    void ProcessProduction();    // Шаг 1: Производство ресурсов
    void ProcessHousing();       // Шаг 2: Проверка жилых мест и урон
    void ProcessSignal();        // Шаг 3: Попытка поймать сигнал 
    void ProcessTaxes();         // Шаг 4: Налоги корпорации 
    void ProcessCleanup();       // Шаг 5: Удаление мертвых роботов

public:
    Station();

    // Инициализация станции: название, стартовые модули и роботы
    void Init(std::string name);

    // Запуск одного игрового дня (полный цикл событий)
    void ProcessDay();

    // Создание нового робота в Архиве
    void SynthesizeRobot(int factionChoice);

    // Вывод состояния станции в консоль
    void PrintStatus() const;

    // Проверка условий проигрыша
    bool IsGameOver() const;

    int GetDay() const { return day; }
    int GetEnergy() const { return energy; }
    int GetBits() const { return bits; }
    size_t GetRobotCount() const { return robots.size(); }
};