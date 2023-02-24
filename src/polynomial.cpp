#include "polynomial.h"

#include <utility>
#include "monome.h"
#include <cmath>

using namespace std;
Monome::Monome(float K_, int a_, int b_, int c_) {
    K = K_;
    a = a_;
    b = b_;
    c = c_;
}

void Monome::print() const {
    if(K>=0)
        cout <<"+"<< K <<"*x^"<<a<<"*y^"<<b<<"*z^"<<c;
    else
        cout << K <<"*x^"<<a<<"*y^"<<b<<"*z^"<<c;
}

Monome Monome::operator*(float constant) const {
    return Monome(K*constant,a,b,c);
}

Monome::Monome(Monome const &m) {
    K = m.K;
    a = m.a;
    b = m.b;
    c = m.c;
}

Monome Monome::operator*(Monome &M) const {

    return Monome(K*M.K,a+M.a,b+M.b,c+M.c);
}

Monome Monome::integrate(short index) const {
    switch (index) {
        case 0:
            return Monome(K/(a+1),a+1,b,c);
            break;
        case 1:
            return Monome(K/(b+1),a,b+1,c);
            break;
        case 2:
            return Monome(K/(c+1),a,b,c+1);
            break;
        default:
            return Monome(0,0,0,0);
            break;
    }
}

Monome Monome::differentiate(short index) const {
    switch (index) {
        case 0:
            if(a==0)
                return Monome(0,0,0,0);
            return Monome(a*K,a-1,b,c);
            break;
        case 1:
            if(b==0)
                return Monome(0,0,0,0);
            return Monome(b*K,a,b-1,c);
            break;
        case 2:
            if(c==0)
                return Monome(0,0,0,0);
            return Monome(c*K,a,b,c-1);
            break;
        default:
            return Monome(0,0,0,0);
            break;
    }
}

float Monome::value_at(float x, float y, float z) {
    return K* pow(x,a)* pow(y,b)* pow(x,c);
}

Polynome::Polynome(string s) {
    // Создадим конечный автомат
    auto sm = StateMachine(0);
    s.push_back(' ');
    // Параметры текущего монома, который будет добавлен к полиному
    float constant = 0;
    int i1 = 0; // Степень x
    int i2 = 0; // Степень y
    int i3 = 0; // Степень z
    int last_state; // Введено для облегчения обработки ввода цифр

    bool is_negative = false; // Является ли константа отрицательным числом

    bool is_first = true; // является ли символ первым (нужно для знака минуса, чтобы не положился нулевой моном)
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

            if(is_negative)
                constant = -constant;
            core.emplace_back(constant,i1,i2,i3);
            cout << "Placing monome: "<< constant << "*x^"<<i1<<"*y^"<<i2<<"*z^"<<i3<<endl;
            constant = 0;
            i1 = 0;
            i2 = 0;
            i3 = 0;
            is_negative = false;
            sm.current_state = 0;
        }

        is_first = false;

        if(c=='-')
            is_negative = true;
        last_state = sm.current_state;
        sm.Move(c);

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


        cout << "Current symbol is "<<c<<" and the state is "<< sm.current_state<<" and the last state is "<<last_state<<endl;



        if((c != '+')&&(c!='-')&&(c!=' ')){
            if(sm.current_state==0){

                int r = c-'0'; // Числовое значение
                constant = constant*10 + r; // Набираем число
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
}

void Polynome::print() {
    for (Monome& M:core) {
        M.print();
    }

}

Polynome::Polynome(list<Monome> monomes) {
    core = std::move(monomes);
}

Polynome::Polynome(const Polynome &p) {
    core = p.core;
}

float Polynome::value_at(float x, float y, float z) {
    float res = 0.0;
    for(Monome& m:core)
        res += m.value_at(x,y,z);
    return res;
}

Polynome Polynome::operator*(float constant) {
    Polynome p(core);
    for(Monome& m:p.core)
        m = m*constant;
    return p;
}

Polynome Polynome::differentiate(short index) {
    Polynome p(core);
    for(Monome& m:p.core)
        m = m.differentiate(index);
    return p;
}

Polynome Polynome::integrate(short index) {
    Polynome p(core);
    for(Monome& m:p.core)
        m = m.integrate(index);
    return p;
}

StateMachine::StateMachine(int start_state) {
    current_state = start_state;
}

void StateMachine::Move(char c) {
    switch (c) {
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '0':
            current_state = v1[current_state];
            break;
        case '+':
        case '-':
            current_state = v2[current_state];
            break;
        case '*':
            current_state = v3[current_state];
            break;
        case '^':
            current_state = v4[current_state];
            break;
        case 'x':
            current_state = v5[current_state];
            break;
        case 'y':
            current_state = v6[current_state];
            break;
        case 'z':
            current_state = v7[current_state];
            break;
        default:
            break;
    }
}
