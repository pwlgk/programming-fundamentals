#include <iostream>
#include <string>
#include <ctime>
#include <limits>
#include "Station.h"

void ClearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    setlocale(LC_ALL, "");

    std::cout << "2942 год. Станция 'Ковчег' переходит на новую систему управления...\n";
    std::cout << "Главный Администратор, введите идентификатор: ";
    
    std::string name;
    std::getline(std::cin, name);

    Station ark;
    ark.Init(name);

    while (!ark.IsGameOver()) {
        ark.PrintStatus();

        std::cout << "--- КОМАНДНЫЙ ЦЕНТР ---\n";
        std::cout << "1. Запустить цикл (День)\n";
        std::cout << "2. Терминал Синтеза (Роботы)\n";
        std::cout << "3. Терминал Строительства (Модули)\n";
        std::cout << "4. Протоколы Модернизации (Улучшение)\n";
        std::cout << "0. Аварийный выход\n";
        std::cout << "Ваш выбор: ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cout << "\n[!] Ошибка протокола ввода.\n";
            ClearInput();
            continue;
        }

        if (choice == 1) {
            ark.ProcessDay();
        } 
        else if (choice == 2) {
            std::cout << "\n--- ВЫБОР ПРОТОТИПА ---\n";
            std::cout << "1. Интегратор (Энергия++)\n";
            std::cout << "2. Хранитель (Данные++)\n";
            std::cout << "3. ЛОКАЛЬНЫЙ ВЫЧИСЛИТЕЛЬ \n";
            std::cout << "Выбор: ";
            int rChoice;
            if (!(std::cin >> rChoice)) ClearInput();
            else ark.SynthesizeRobot(rChoice);
        } 
        else if (choice == 3) {
            std::cout << "\n--- СТРОИТЕЛЬСТВО ---\n";
            std::cout << "1. Архив | 2. Центр управления | 3. Жилье | 4. Генератор\n";
            std::cout << "Выбор: ";
            int mChoice;
            if (!(std::cin >> mChoice)) ClearInput();
            else ark.BuildModule(mChoice);
        }
        else if (choice == 4) {
            ark.PrintModules();
            std::cout << "Введите индекс модуля для улучшения: ";
            int idx;
            if (!(std::cin >> idx)) ClearInput();
            else ark.UpgradeModule(idx);
        }
        else if (choice == 0) {
            std::cout << "Сессия завершена.\n";
            break;
        } 
        else {
            std::cout << "\n[!] Неизвестная команда.\n";
        }
    }

    if (ark.IsGameOver()) {
        std::cout << "\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
        std::cout << " КРИТИЧЕСКАЯ ОШИБКА: Станция " << name << " пала.\n";
        std::cout << " Связь потеряна. Сигнал угас во тьме.\n";
        std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
    }

    return 0;
}