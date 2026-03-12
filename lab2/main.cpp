#include <iostream>
#include <string>
#include <ctime>
#include <limits> // Для std::numeric_limits
#include "Station.h"

int main() {
    srand(time(0));
    setlocale(LC_ALL, "");

    std::cout << "2942 год. Пробуждение...\n";
    std::cout << "Введите имя станции: ";
    std::string name;
    std::getline(std::cin, name);

    Station station;
    station.Init(name);

    while (!station.IsGameOver()) {
        station.PrintStatus();
        std::cout << "1. Следующий день\n0. Выход\nВыбор: ";
        
        int choice;
        std::cin >> choice;

        // ПРОВЕРКА ВВОДА
        if (std::cin.fail()) {
            std::cin.clear(); // Сбрасываем флаг ошибки
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаем буфер до конца строки
            std::cout << "\n[ОШИБКА]: Введите число (1 или 0)!\n";
            continue; // Возвращаемся в начало цикла
        }

        if (choice == 1) {
            station.ProcessDay();
        } else if (choice == 0) {
            std::cout << "Завершение работы систем...\n";
            break;
        } else {
            std::cout << "\n[ОШИБКА]: Команда не распознана!\n";
        }
    }

    if (station.IsGameOver()) {
        std::cout << "\n======================================\n";
        std::cout << "КРИТИЧЕСКИЙ СБОЙ: Ресурсы исчерпаны или все роботы погибли.\n";
        std::cout << "Станция затихла... Миссия провалена.\n";
        std::cout << "======================================\n";
    }
    
    return 0;
}