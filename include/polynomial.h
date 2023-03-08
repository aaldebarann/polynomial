
#include "monome.h"
#include <list>
#include <string>
#include <iostream>
using namespace std;

// Класс стандартного полинома
class Polynome {
    list<Monome> core; // Список из мономов этого полинома
public:
    Polynome();// Конструктор по умолчанию
    explicit Polynome(float C); // Константный полином
    explicit Polynome(string s); // Конструктор полинома по строке ввода
    void print();

    explicit Polynome(list<Monome> monomes); // Конструктор полинома из списка мономов

    Polynome(Polynome const &p); // Конструктор копирования

    float value_at(float x,float y,float z); // Значение в точке (x,y,z)

    // Все эти операции СОХРАНЯЮТ отсортированность полинома
    Polynome operator*(float constant); // Умножение на константу
    Polynome differentiate(short index); // Дифференцирование по переменной, соответствующей индексу:
    // 0 - x; 1 - y; 2 - z;
    Polynome integrate(short index); // Интегрирование по переменной, соответствующей индексу:
    // 0 - x; 1 - y; 2 - z;
    // На отрезке [from;to]
    // Операции над двумя полиномами
    Polynome operator+(Polynome p);// Сложение полиномов
    Polynome operator-(Polynome p); // Вычитание полиномов
    Polynome operator*(const Polynome& p); // Умножение полиномов (*)
    Polynome operator*(const Monome& m); // Умножение полинома на моном
    Polynome operator/(Polynome p); // Деление полиномов (*)

    bool operator==(Polynome& p); // Сравнение полиномов
};
    static void deleteAll(string& str, char toDelete); // Для удаления пробелов в строке



