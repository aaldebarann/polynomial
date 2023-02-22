
#ifndef POLYGUI_MONOME_H
#define POLYGUI_MONOME_H

// Класс стандартного монома вида K * x^a * y^b * z^c
class Monome {
    float K; // Коэффициент при мономе
    int a,b,c; // Показатели степеней монома в том же порядке

    // Дефолтные значения добавлены для удобства

    Monome& differentiate(short index); // Дифференцировать моном
    // Индекс показывает, по какой переменной идёт дифференцирование: 0 - x; 1 - y; 2 - z;
    // Сомневаюсь: надо дифференцировать сам моном или его копию?

    Monome& integrate(short index,float from,float to); // Интегрировать моном
    // Индекс показывает, по какой переменной идёт интегрирование: 0 - x; 1 - y; 2 - z;
    // Интегрирование происходит на отрезке [from;to]
    // Сомневаюсь: надо интегрировать сам моном или его копию?

    float value_at(float x,float y,float z); // Значение монома в точке (x,y,z)

    Monome& operator * (Monome M); // Умножение на моном

    Monome& operator * (float constant); // Умножение на константу
public:
    // Конструктор монома K_ * x^a_ * y^b_ * z^c_
    Monome(float K_ = 1,int a_ = 0,int b_ = 0,int c_ = 0);
    void print() const; // Вывод монома
};




#endif
