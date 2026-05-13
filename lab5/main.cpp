#include <iostream>
#include <string>
#include <ctime>
#include <limits>
#include "Station.h"
#include "Exceptions.h"

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
        std::cout << "3. Синтез сознания (Скрестить роботов)\n";
        std::cout << "4. Терминал Строительства (Новый модуль)\n";
        std::cout << "5. Протоколы Модернизации (Улучшение/Сборка модуля)\n";
        std::cout << "6. Принудительный ремонт робота (++)\n";
        std::cout << "7. Детектор Клонов (Сравнить роботов ==)\n";
        std::cout << "8. ТЕРМИНАЛ АНАЛИТИКИ (STL)\n";
        std::cout << "0. Аварийный выход\n";
        std::cout << "Ваш выбор: ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cout << "\n[!] Ошибка протокола ввода.\n";
            ClearInput();
            continue;
        }

        if (choice == 1) {
            try {
                ark.ProcessDay();
            } catch (const PowerSurgeException& e) {
                std::cout << "\n[!] КРИТИЧЕСКИЙ СБОЙ: " << e.what() << "\n";
                ark.ApplyPowerSurgePenalty();
                ark.AdvanceDayOnException();
            } catch (const FirmwareGlitchException& e) {
                std::cout << "\n[!] КРИТИЧЕСКИЙ СБОЙ: " << e.what() << "\n";
                ark.ApplyFirmwareGlitchPenalty();
                ark.AdvanceDayOnException();
            } catch (const MeteorStrikeException& e) {
                std::cout << "\n[!] КРИТИЧЕСКИЙ СБОЙ: " << e.what() << "\n";
                ark.ApplyMeteorStrikePenalty();
                ark.AdvanceDayOnException();
            } catch (const CoolantLeakException& e) {
                std::cout << "\n[!] КРИТИЧЕСКИЙ СБОЙ: " << e.what() << "\n";
                ark.ApplyCoolantLeakPenalty();
                ark.AdvanceDayOnException();
            } catch (const StationException& e) {
                std::cout << "\n[!] КРИТИЧЕСКИЙ СБОЙ: " << e.what() << "\n";
                ark.AdvanceDayOnException();
            } catch (const std::exception& e) {
                std::cout << "\n[!] СИСТЕМНАЯ ОШИБКА: " << e.what() << "\n";
            }
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
            bool inUpgradeMenu = true;
            while (inUpgradeMenu) {
                ark.PrintModules();
                std::cout << "--- ПРОТОКОЛЫ МОДЕРНИЗАЦИИ ---\n";
                std::cout << "1. Улучшить модуль (Энергия + Данные)\n";
                std::cout << "2. Скрестить два одинаковых модуля (+)\n";
                std::cout << "0. Назад в командный центр\n";
                std::cout << "Выбор: ";
                int mChoice;
                if (!(std::cin >> mChoice)) {
                    ClearInput();
                    break;
                }
                
                if (mChoice == 1) {
                    std::cout << "Введите индекс модуля для улучшения: ";
                    int idx;
                    if (!(std::cin >> idx)) ClearInput();
                    else ark.UpgradeModule(idx);
                } else if (mChoice == 2) {
                    std::cout << "Введите индексы двух модулей через пробел: ";
                    int a, b;
                    if (!(std::cin >> a >> b)) {
                        ClearInput();
                    } else {
                        Module* mA = ark.GetModule(a);
                        Module* mB = ark.GetModule(b);
                        if (mA && mB && a != b && mA->GetTypeName() == mB->GetTypeName() && mA->GetLevel() == mB->GetLevel()) {
                            std::cout << "\n--- ПРОГНОЗ СБОРКИ ---\n";
                            std::cout << "Тип: " << mA->GetTypeName() << "\n";
                            std::cout << "Результат: Уровень " << mA->GetLevel() + 1 << "\n";
                            std::cout << "Подтвердить слияние? (y/n): ";
                            char confirm;
                            std::cin >> confirm;
                            if (confirm == 'y' || confirm == 'Y') ark.CombineModules(a, b);
                        } else {
                            std::cout << "[!] Модули несовместимы или не найдены.\n";
                        }
                    }
                } else if (mChoice == 0) {
                    inUpgradeMenu = false;
                } else {
                    std::cout << "[!] Неизвестная команда.\n";
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
        else if (choice == 8) {
            ark.PrintAnalytics();
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