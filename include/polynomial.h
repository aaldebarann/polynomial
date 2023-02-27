
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
};
    static void deleteAll(string& str, char toDelete); // Для удаления пробелов в строке
// Конечный автомат для обработки ввода полинома
class StateMachine{
    // Векторы перехода
    int v1[10] = {0,5,-1,3,5,-1,6,-1,8,0}; // ц
    int v2[10] = {0,-1,0,-1,-1,0,0,0,0,-1}; // + или -
    int v3[10] = {1,-1,4,4,-1,7,7,-1,-1,-1}; // *
    int v4[10] = {-1,-1,3,-1,-1,6,-1,8,-1,-1}; // ^
    int v5[10] = {2,2,-1,-1,-1,-1,-1,-1,-1,-1}; // x
    int v6[10] = {5,5,-1,-1,5,-1,-1,-1,-1,-1}; // y
    int v7[10] = {7,7,-1,-1,7,-1,-1,7,-1,-1}; // z
    int v8[10] = {9,-1,-1,-1,-1,-1,-1,-1,-1,-1}; // , или .
    // Конструктор с начальным положением

public:
    int current_state; // Текущее положение
    explicit StateMachine(int start_state = 0);
    void Move(char c); // Передвижение машины по символам
};


