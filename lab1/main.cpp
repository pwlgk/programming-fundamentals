#include <iostream>
#include <clocale>
#include "Calculator.h"

using namespace std;

int main() {
    // Включаем поддержку русского языка в консоли
    setlocale(LC_ALL, "");

    // V - Скорость поезда
    // t - Время
    double V, t;

    cout << "Программа для вычисления пройденного пути поезда метро\n\n";

    // Цикл для корректного ввода скорости
    while (true) {
        cout << "Введите скорость поезда V (V >= 0): ";
        cin >> V;
        
        // Проверка: скорость должна быть числом и больше либо равна 0
        if (cin.fail() || V < 0) {
            cout << "Ошибка! Скорость должна быть числом и не может быть отрицательной.\n";
            cin.clear();             
            cin.ignore(10000, '\n'); 
        } else {
            break; 
        }
    }

    // Цикл для корректного ввода времени
    while (true) {
        cout << "Введите время t (t > 0): ";
        cin >> t;
        
        // Проверка: время должно быть числом и больше 0
        if (cin.fail() || t <= 0) {
            cout << "Ошибка! Время должно быть положительным числом.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        } else {
            break; 
        }
    }

    // Создаем экземпляр калькулятора и вычисляем результат
    Calculator calc;
    calc.calculateAndPrint(V, t);

    return 0;
}