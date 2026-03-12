#include "Calculator.h"
#include <iostream>

void Calculator::calculateAndPrint(double V, double t) {
    // S1 - Путь при равномерном движении
    double S1 = V * t;
    // a - Ускорение (замедление)
    double a = V / t;
    // S2 - Путь при торможении
    double S2 = (a * t * t) / 2.0;
    // S - Общий путь
    double S = S1 + S2;

    // S_compare - Путь по формуле для сравнения (3Vt/2)
    double S_compare = (3.0 * V * t) / 2.0;

    std::cout << "\n=== Результаты расчетов ===\n";
    std::cout << "Путь равномерного движения (S1): " << S1 << "\n";
    std::cout << "Ускорение при торможении (a): " << a << "\n";
    std::cout << "Путь при торможении (S2): " << S2 << "\n";
    std::cout << "Общий вычисленный путь (S = S1 + S2): " << S << "\n";
    std::cout << "Путь по формуле для сравнения (S = 3Vt/2): " << S_compare << "\n";
}