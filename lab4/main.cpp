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
        std::cout << "2. Терминал Синтеза (Новый робот)\n";
        std::cout << "3. Синтез сознания (Скрестить роботов) [Lab 4]\n";
        std::cout << "4. Терминал Строительства (Новый модуль)\n";
        std::cout << "5. Протоколы Модернизации (Улучшение/Сборка модуля) [Lab 4]\n";
        std::cout << "6. Принудительный ремонт робота (++) [Lab 4]\n";
        std::cout << "7. Детектор Клонов (Сравнить роботов ==) [Вариант 2]\n";
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
            std::cout << "1. Интегратор\n";
            std::cout << "2. Хранитель\n";
            std::cout << "3. Локальный вычислитель\n";
            std::cout << "Выбор: ";
            int rChoice;
            if (!(std::cin >> rChoice)) ClearInput();
            else ark.SynthesizeRobot(rChoice);
        } 
        else if (choice == 3) {
            ark.PrintRobots();
            std::cout << "Введите индексы двух роботов для синтеза сознания (через пробел): ";
            int a, b;
            if (!(std::cin >> a >> b)) {
                ClearInput();
            } else {
                Robot* rA = ark.GetRobot(a);
                Robot* rB = ark.GetRobot(b);
                if (rA && rB && a != b) {
                    std::cout << "\n--- ПРОГНОЗ СИНТЕЗА ---\n";
                    std::cout << "Родитель А: " << *rA << "\n";
                    std::cout << "Родитель Б: " << *rB << "\n";
                    int predEff = ((rA->ProduceResources().first + rA->ProduceResources().second) + 
                                   (rB->ProduceResources().first + rB->ProduceResources().second)) / 2;
                    std::cout << "Ожидаемая эффективность: ~" << predEff << " (+/- 20% мутация)\n";
                    std::cout << "Стоимость: 100 Энергии\n";
                    std::cout << "Подтвердить протокол синтеза? (y/n): ";
                    char confirm;
                    std::cin >> confirm;
                    if (confirm == 'y' || confirm == 'Y') ark.SynthesizeConsciousness(a, b);
                    else std::cout << "Операция отменена.\n";
                } else {
                    std::cout << "[!] Некорректные индексы.\n";
                }
            }
        }
        else if (choice == 4) {
            std::cout << "\n--- СТРОИТЕЛЬСТВО ---\n";
            std::cout << "1. Архив | 2. Центр управления | 3. Жилье | 4. Генератор\n";
            std::cout << "Выбор: ";
            int mChoice;
            if (!(std::cin >> mChoice)) ClearInput();
            else ark.BuildModule(mChoice);
        }
        else if (choice == 5) {
            ark.PrintModules();
            std::cout << "1. Улучшить модуль за ресурсы\n";
            std::cout << "2. Скрестить два одинаковых модуля (+)\n";
            std::cout << "Выбор: ";
            int mChoice;
            if (!(std::cin >> mChoice)) ClearInput();
            else {
                if (mChoice == 1) {
                    std::cout << "Введите индекс модуля: ";
                    int idx;
                    if (!(std::cin >> idx)) ClearInput();
                    else ark.UpgradeModule(idx);
                } else if (mChoice == 2) {
                    std::cout << "Введите индексы двух модулей (через пробел): ";
                    int a, b;
                    if (!(std::cin >> a >> b)) {
                        ClearInput();
                    } else {
                        Module* mA = ark.GetModule(a);
                        Module* mB = ark.GetModule(b);
                        if (mA && mB && a != b && mA->GetTypeName() == mB->GetTypeName() && mA->GetLevel() == mB->GetLevel()) {
                            std::cout << "\n--- ПРОГНОЗ СБОРКИ ---\n";
                            std::cout << "Исходный уровень: " << mA->GetLevel() << "\n";
                            std::cout << "Результат: " << mA->GetTypeName() << " УРОВНЯ " << mA->GetLevel() + 1 << "\n";
                            std::cout << "Подтвердить слияние? (y/n): ";
                            char confirm;
                            std::cin >> confirm;
                            if (confirm == 'y' || confirm == 'Y') ark.CombineModules(a, b);
                            else std::cout << "Операция отменена.\n";
                        } else {
                            std::cout << "[!] Модули несовместимы или не найдены.\n";
                        }
                    }
                }
            }
        }
        else if (choice == 6) {
            ark.PrintRobots();
            std::cout << "Введите индекс робота для ремонта: ";
            int idx;
            if (!(std::cin >> idx)) ClearInput();
            else ark.RepairRobot(idx);
        }
        else if (choice == 7) {
            ark.PrintRobots();
            std::cout << "Введите индексы двух роботов для проверки: ";
            int a, b;
            if (!(std::cin >> a >> b)) ClearInput();
            else ark.CheckClones(a, b);
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
        std::cout << " КРИТИЧЕСКАЯ ОШИБКА: Станция пала.\n";
        std::cout << " Связь потеряна.\n";
        std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
    }

    return 0;
}