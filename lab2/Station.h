#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Robot.h"
#include "Module.h"

class Station {
private:
    // Ресурсы и состояние
    std::string stationName;
    int day;
    int energy;
    int maxEnergy;
    int bits;

    // Списки объектов станции
    std::vector<Robot> robots;
    std::vector<Module> modules;
    
    // Список событий для вывода в консоль (логи)
    std::vector<std::string> logs;

    // Внутренние методы игрового цикла (инкапсуляция логики)
    void ProcessProduction();    // Шаг 1: Производство ресурсов
    void ProcessHousing();       // Шаг 2: Проверка жилых мест и урон
    void ProcessSignal();        // Шаг 3: Попытка поймать сигнал (мат. модель)
    void ProcessTaxes();         // Шаг 4: Налоги корпорации 
    void ProcessCleanup();       // Шаг 5: Удаление мертвых роботов

public:
    // Конструктор: задает начальные ресурсы
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

    // Геттеры (для использования в main, если нужно)
    int GetDay() const { return day; }
    int GetEnergy() const { return energy; }
    int GetBits() const { return bits; }
    size_t GetRobotCount() const { return robots.size(); }
};