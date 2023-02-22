
#include "monome.h"
#include <list>
#include <string>
#include <iostream>
using namespace std;

// Класс стандартного полинома
class Polynome {

    list<Monome> core; // Список из мономов этого полинома

    // Конструктор полинома по строке ввода

    explicit Polynome(list<Monome> monomes); // Конструктор полинома из списка мономов

    float value_at(float x,float y,float z); // Значение в точке (x,y,z)

    Polynome& operator*(float constant); // Умножение на константу
    Polynome& differentiate(short index); // Дифференцирование по переменной, соответствующей индексу:
    // 0 - x; 1 - y; 2 - z;
    Polynome& integrate(short index,float from,float to); // Интегрирование по переменной, соответствующей индексу:
    // 0 - x; 1 - y; 2 - z;
    // На отрезке [from;to]

    Polynome& operator+(Polynome p); // Сложение полиномов
    Polynome& operator-(Polynome p); // Вычитание полиномов
    Polynome& operator*(Polynome p); // Умножение полиномов
    Polynome& operator/(Polynome p); // Деление полиномов

public:
    explicit Polynome(string s);
    void print();
};

// Конечный автомат для обработки ввода полинома
class StateMachine{
    // Векторы перехода
    int v1[9] = {0,5,-1,3,5,-1,6,-1,8}; // ц
    int v2[9] = {0,-1,0,-1,-1,0,0,0,0}; // +
    int v3[9] = {1,-1,4,4,-1,7,7,-1,-1}; // *
    int v4[9] = {-1,-1,3,-1,-1,6,-1,8,-1}; // ^
    int v5[9] = {-1,2,-1,-1,-1,-1,-1,-1,-1}; // x
    int v6[9] = {-1,5,-1,-1,5,-1,-1,-1,-1}; // y
    int v7[9] = {-1,7,-1,-1,7,-1,-1,7,-1}; // z
    // Конструктор с начальным положением

public:
    int current_state; // Текущее положение
    explicit StateMachine(int start_state = 0);
    void Move(char c); // Передвижение машины по символам
};


