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

    std::cout << "2942 год. Земля мертва. Оцифрованные сознания пробуждаются...\n";
    std::cout << "Главный Администратор, введите идентификатор станции: ";
    
    std::string name;
    std::getline(std::cin, name);

    Station ark;
    ark.Init(name);

    while (!ark.IsGameOver()) {
        ark.PrintStatus();

        std::cout << "ДОСТУПНЫЕ ДЕЙСТВИЯ:\n";
        std::cout << "1. Запустить следующий цикл (День)\n";
        std::cout << "2. Войти в терминал Архива (Синтез робота)\n";
        std::cout << "0. Аварийное завершение работы\n";
        std::cout << "Ваш выбор: ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cout << "\n[!] Ошибка ввода. Используйте только цифры.\n";
            ClearInput();
            continue;
        }

        if (choice == 1) {
            ark.ProcessDay();
        } 
        else if (choice == 2) {
            std::cout << "\n--- ТЕРМИНАЛ СИНТЕЗА ---\n";
            std::cout << "1. Синтезировать Интегратора (1 ячейка, много Энергии)\n";
            std::cout << "2. Восстановить Хранителя (2 ячейки, много Данных)\n";
            std::cout << "Выбор фракции: ";
            int fChoice;
            if (!(std::cin >> fChoice)) {
                ClearInput();
            } else {
                ark.SynthesizeRobot(fChoice);
            }
        } 
        else if (choice == 0) {
            std::cout << "Администратор покинул систему. Станция переходит в автономный режим.\n";
            break;
        } 
        else {
            std::cout << "\n[!] Неизвестная директива.\n";
        }
    }

    if (ark.IsGameOver()) {
        std::cout << "\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
        std::cout << " КРИТИЧЕСКАЯ ОШИБКА: Станция " << name << " пала.\n";
        std::cout << " Причина: Исчерпание ресурсов или гибель персонала.\n";
        std::cout << " Человечество окончательно стерто из памяти Вселенной.\n";
        std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
    }

    return 0;
}