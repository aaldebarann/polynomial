#include "polynomial.h"
#include "StateMachine.h"
#include "monome.h"

#include <utility>
#include <cmath>

using namespace std;


void deleteAll(string& str, char toDelete) {
    int spaces = 0;
    for(int i = 0; i < str.size(); i++) {
        str[i - spaces] = str[i];
        if(str[i] == toDelete)
            spaces++;
    }
    str.erase(str.size() - spaces, spaces);
}


Polynome::Polynome(string s) {
    // Создадим конечный автомат
    auto sm = StateMachine(0);
    deleteAll(s,' ');
    s.push_back(' ');
    // Параметры текущего монома, который будет добавлен к полиному
    float constant_integer_part = 0.0; // Целая часть константы
    float constant_floating_part = 0.0; // Вещественная часть константы

    float constant; // Сумма целой и вещественной частей

    int i1 = 0; // Степень x
    int i2 = 0; // Степень y
    int i3 = 0; // Степень z
    int last_state; // Введено для облегчения обработки ввода цифр

    bool is_negative = false; // Является ли константа отрицательным числом

    bool is_first = true; // Является ли символ первым (нужно для знака минуса, чтобы не положился нулевой моном)

    bool was_a_dot = false; // Встретилась ли  , или . при вводе константы

    float multiplier = 10.0; // Мультипликатор для ввода вещественной части числа

    for(char& c:s){
        if((c == '+')||(c == ' ')||( (c=='-')&&(!is_first)  )){
            // Возможность не вводить единичную степень последнего элемента
            // Для x
            if(sm.current_state == 2)
                i1 = 1;
            // Для y
            if(sm.current_state == 5)
                i2 = 1;
            // Для z
            if(sm.current_state == 7)
                i3 = 1;

            constant = constant_integer_part + constant_floating_part;
            //cout << constant_floating_part << endl;
            if(is_negative)
                constant = -constant;
            core.emplace_back(constant,i1,i2,i3);
            //cout << "Placing monome: "<< constant << "*x^"<<i1<<"*y^"<<i2<<"*z^"<<i3<<endl;
            // Всё зануляем
            constant = 0.0;
            constant_integer_part = 0.0;
            constant_floating_part = 0.0;
            i1 = 0;
            i2 = 0;
            i3 = 0;
            is_negative = false;
            was_a_dot = false;
            sm.current_state = 0;
            multiplier = 10.0;
        }

        is_first = false;

        if(c=='-')
            is_negative = true;

        if(sm.current_state == 9)
            was_a_dot = true;
        last_state = sm.current_state;
        sm.Move(c);
        if(sm.current_state == -1)
            throw std::invalid_argument("Incorrect input!");

        // Возможность не вводить единичную степень элемента внутри
        // Для x
        if((sm.current_state==4)&&(last_state == 2)){
            i1 = 1;
            //cout << "IT'S HERE!!"<<endl;
        }
        // Для y
        if((sm.current_state==7)&&(last_state == 5)){
            i2 = 1;
            //cout << "IT'S HERE!!"<<endl;
        }
        // Для z не нужно, поскольку z всегда является последним

        // Возможность не вводить единичную константу
        if((last_state == 0)&&( (sm.current_state == 2)||(sm.current_state == 5)||(sm.current_state == 7)  ))
            constant_integer_part = 1.0;

        //cout << "Current symbol is "<<c<<" and the state is "<< sm.current_state<<" and the last state is "<<last_state<<endl;



        if((c != '+')&&(c!='-')&&(c!=' ')){
            if(sm.current_state==0){

                int r = c-'0'; // Числовое значение
                if(!was_a_dot){
                    constant_integer_part = constant_integer_part*10 + r; // Набираем целое число
                }
                else{
                    constant_floating_part = constant_floating_part + r/multiplier; // Набираем вещественную часть
                    multiplier *= 10.0;
                }
                //cout << constant << endl;
            }
            if(last_state == sm.current_state){
                if(sm.current_state==3){
                    int t = c-'0'; // Числовое значение
                    i1 = i1*10 + t; // Набираем число

                }
                if(sm.current_state==6){
                    int m = c-'0'; // Числовое значение
                    i2 = i2*10 + m; // Набираем число
                    //cout << i2 << "< --"<<c << endl;
                }
                if(sm.current_state==8){
                    int k = c-'0'; // Числовое значение
                    i3 = i3*10 + k; // Набираем число
                }
            }
        }
    }
    // После окончания ввода полином сортируется по возврастанию
    core.sort(Monome::compare);
}

void Polynome::print() {
    for (Monome& M:core) {
        M.print();
    }

}

Polynome::Polynome(list<Monome> monomes) {
    core = std::move(monomes);
    core.sort(Monome::compare);
}

Polynome::Polynome(const Polynome &p) {
    core = p.core;
}

float Polynome::value_at(float x, float y, float z) {
    float res = 0.0;
    for(Monome& m:core){

//        m.print();cout << endl;
//        cout << m.value_at(x,y,z) << endl;

        res += m.value_at(x,y,z);
    }

    return res;
}

Polynome Polynome::operator*(float constant) {
    Polynome p(core);
    for(Monome& m:p.core)
        m = m*constant;
    return p;
}

Polynome Polynome::differentiate(short index) {
    list<Monome> add_core;
    for(Monome& m:core){
        auto t = m.differentiate(index);
        if(t.K != 0.0)
            add_core.push_back(t);
    }
    return Polynome(add_core);
}

Polynome Polynome::integrate(short index) {
    Polynome p(core);
    for(Monome& m:p.core)
        m = m.integrate(index);
    return p;
}

Polynome Polynome::operator+(Polynome p) {
    // Предполагается, что мы складываем 2 ОТСОРТИРОВАННЫХ по возрастанию степеней мономов полинома
    list<Monome> add_list;// Пока что пустой список, на основе которого будет сформирован новый полином

    //Идея такая: создаём вспомогательный список и в него делаем merge с сохранением порядка
    // После этого проходим по вспомогательному списку и собираем одинаковые (с одинаковыми наборами степеней)
    list<Monome> tmp = core; // Вспомогательный список
    tmp.merge(p.core,Monome::compare); // Происходит merge
    // ----------------------------------------------------
    // Добавлено для тестирования, не является частью проги
//    Polynome n_p(tmp);
//    n_p.print();
    // ----------------------------------------------------
    // Теперь по tmp надо пройтись и собрать одинаковые
    list<Monome>::iterator it;// Итератор для получения лёгкого доступа к элементам
    // Нам нужно идти парами
    // Длина должна быть хотя бы 2
    std::list<Monome>::iterator iter = tmp.end();
    --iter;
    if(tmp.begin()!=iter){
        // Сразу начинаем добавлять моном
        it = tmp.begin();
        //it->print();
        //cout << endl;
        float K_ = it->K;
        int a_ = it->a;
        int b_ = it->b;
        int c_ = it->c;
        auto nxt = std::next(it); // Следующий за ним элемент
        /*nxt->print();
        cout << endl;*/
        while (true){
            //it->print(); cout << "||"; nxt->print(); cout <<" "<< Monome::equal_iterators(it, nxt) <<endl;
            if(Monome::equal_iterators(it,nxt)){
                K_ += nxt->K;
            } else{
                if(K_!=0.0)
                    add_list.emplace_back(K_,a_,b_,c_);
                K_ = nxt->K;
                a_ = nxt->a;
                b_ = nxt->b;
                c_ = nxt->c;
            }
            /*it->print();
            cout << endl;*/
            if (nxt == iter) {
                if(K_!=0.0)
                    add_list.emplace_back(K_, a_, b_, c_);
                break;
            }
                
            it++;
            nxt++;
            
            /*nxt->print();
            cout << endl;*/
        }
    }
    else{
        add_list = tmp;
    }

    return Polynome(add_list);
}

Polynome Polynome::operator-(Polynome p) {
    return *this+p.operator*(-1);
}

Polynome Polynome::operator*(const Polynome& p) {
    // Очевидная реализация за O(n^2), n - длина полинома
    Polynome res;
    for(auto& m:p.core)
        res=res + ((*this) *m);
    return res;
}

Polynome::Polynome() {
    core.emplace_back(0,0,0,0);
}

Polynome Polynome::operator*(const Monome &m) {
    auto temp = core;
    for (auto& t:temp) {
        t.K *= m.K;
        t.a += m.a;
        t.b += m.b;
        t.c += m.c;
    }
    return Polynome(temp);
}

Polynome::Polynome(float C) {
    core.emplace_back(C,0,0,0);
}

bool Polynome::operator==(Polynome &p) {
    if(core.size()!=p.core.size())
        return false;
    auto it1 = core.begin();
    auto it2 = p.core.begin();
    while (it1!=core.end()){
        if(!(Monome::equal_iterators(it1,it2)))
            return false;
        it1 ++;
        it2 ++;
    }
    return true;
}

string Polynome::to_string() {
    string s;
    for(auto& m:core)
        s.append(m.to_string());
    return s;
}


