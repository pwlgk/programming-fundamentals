#include <iostream>

using namespace std;

int main() {
    double V, t;

    cout << "Программа для вычисления пройденного пути поезда метро\n\n";

    while (true) {
        cout << "Введите скорость поезда V (V >= 0): ";
        cin >> V;
        
        if (cin.fail() || V < 0) {
            cout << "Ошибка! Скорость должна быть числом и не может быть отрицательной.\n";
            cin.clear();             
            cin.ignore(10000, '\n'); 
        } else {
            break; 
        }
    }

    while (true) {
        cout << "Введите время t (t > 0): ";
        cin >> t;
        
        if (cin.fail() || t <= 0) {
            cout << "Ошибка! Время должно быть положительным числом.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        } else {
            break; 
        }
    }

    double S1 = V * t;                // Путь при равномерном движении
    double a = V / t;                 // Ускорение (замедление)
    double S2 = (a * t * t) / 2.0;    // Путь при торможении
    double S = S1 + S2;               // Общий путь

    double S_compare = (3.0 * V * t) / 2.0;

    cout << "\n=== Результаты расчетов ===\n";
    cout << "Путь равномерного движения (S1): " << S1 << "\n";
    cout << "Ускорение при торможении (a): " << a << "\n";
    cout << "Путь при торможении (S2): " << S2 << "\n";
    cout << "Общий вычисленный путь (S = S1 + S2): " << S << "\n";
    cout << "Путь по формуле для сравнения (S = 3Vt/2): " << S_compare << "\n";

    return 0;
}