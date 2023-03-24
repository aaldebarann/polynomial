//
// Created by aleksei on 24.03.23.
//
#include <iostream>
#include "calculator.h"
using namespace std;

int main() {
    Calculator calc{};
    setlocale(LC_ALL, "Russian");
    cout << "Введите допустимое выражение."<<
            "Для завершения работы введите \"exit\"" << endl;
    string str;
    cin >> str;
    while (str != "exit") {
        cout << calc.interpret(str) << endl;
    }
    cout << "Завершение работы" << endl;
    return 0;
}