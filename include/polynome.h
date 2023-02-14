#ifndef POLYGUI_POLYNOME_H
#define POLYGUI_POLYNOME_H
#include "monome.h"
#include <list>

using namespace std;

// Класс стандартного полинома
class Polynome {

    list<Monome> core; // Список из мономов этого полинома

    Polynome(list<Monome> monomes); // Базовый конструктор полинома

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

};


#endif //POLYGUI_POLYNOME_H
