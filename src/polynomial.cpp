#include "polynomial.h"
#include "monome.h"


using namespace std;
Monome::Monome(float K_, int a_, int b_, int c_) {
    K = K_;
    a = a_;
    b = b_;
    c = c_;
}

void Monome::print() const {
    cout << K <<"*x^"<<a<<"*y^"<<b<<"*z^"<<c<<'+';
}

Polynome::Polynome(string s) {
    // Создадим конечный автомат
    auto sm = StateMachine(0);
    s.push_back(' ');
    // Параметры текущего монома, который будет добавлен к полиному
    int constant = 0;
    int i1 = 0; // Степень x
    int i2 = 0; // Степень y
    int i3 = 0; // Степень z
    int last_state; // Введено для облегчения обработки ввода цифр
    for(char& c:s){
        if((c == '+')||(c == ' ')){
            core.emplace_back(constant,i1,i2,i3);
            cout << "Placing monome: "<< constant << "*x^"<<i1<<"*y^"<<i2<<"*z^"<<i3<<endl;
            constant = 0;
            i1 = 0;
            i2 = 0;
            i3 = 0;
            sm.current_state = 0;
        }


        last_state = sm.current_state;
        sm.Move(c);
        cout << "Current symbol is "<<c<<" and the state is "<< sm.current_state<<endl;
//        if(c == '*')
//            ;
        if((c != '+')&&(c!=' ')){
            if(sm.current_state==0){

                int r = c-'0'; // Числовое значение
                constant = constant*10 + r; // Набираем число
                cout << constant << endl;
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
