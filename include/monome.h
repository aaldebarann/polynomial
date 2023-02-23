
#ifndef POLYGUI_MONOME_H
#define POLYGUI_MONOME_H

// Класс стандартного монома вида K * x^a * y^b * z^c
class Monome {
    float K; // Коэффициент при мономе
    int a,b,c; // Показатели степеней монома в том же порядке
public:
    // Конструктор монома K_ * x^a_ * y^b_ * z^c_
    explicit Monome(float K_ = 1,int a_ = 0,int b_ = 0,int c_ = 0);
    Monome(Monome const & m);// Конструктор копирования
    void print() const; // Вывод монома

    Monome differentiate(short index) const; // Дифференцировать моном
    // Индекс показывает, по какой переменной идёт дифференцирование: 0 - x; 1 - y; 2 - z;

    Monome integrate(short index) const; // Интегрировать моном. Находит первообразную
    // Индекс показывает, по какой переменной идёт интегрирование: 0 - x; 1 - y; 2 - z;
    // Интегрирование происходит на отрезке [from;to]

    float value_at(float x,float y,float z); // Значение монома в точке (x,y,z)

    Monome operator * (Monome& M) const; // Умножение на моном

    Monome operator * (float constant) const; // Умножение на константу
};




#endif
