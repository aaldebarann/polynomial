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
    if(K>=0){
        cout <<"+";
    }
    cout << K ;
    if(a!=0)
        cout<<"*x^"<<a;
    if(b!=0)
        cout<<"*y^"<<b;
    if(c!=0)
        cout <<"*z^"<<c;
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

float Monome::value_at(float x, float y, float z) const {
    return K* pow(x,a)* pow(y,b)* pow(z,c);
}

bool Monome::compare(const Monome& m1, const Monome& m2) {
    return (100*m1.a+10*m1.b+m1.c)<(100*m2.a+10*m2.b+m2.c); // Хитрый хак
}

bool Monome::operator<(const Monome &m2) const {
    return (100*a+10*b+c)<(100*m2.a+10*m2.b+m2.c); // Хитрый хак
}

bool operator<(std::list<Monome>::iterator it1, std::list<Monome>::iterator it2) {
    return (100*it1->a+10*it1->b+it1->c)<(100*it2->a+10*it2->b+it2->c); // Хитрый хак
}

bool operator>(std::list<Monome>::iterator it1, std::list<Monome>::iterator it2) {
    return (100*it1->a+10*it1->b+it1->c)>(100*it2->a+10*it2->b+it2->c); // Хитрый хак
}

//bool operator==(std::list<Monome>::iterator it1, std::list<Monome>::iterator it2) {
//    return (it1->a == it2->a)&&(it1->b == it2->b)&&(it1->c == it2->c);
//}

bool Monome::equal_iterators(std::list<Monome>::iterator it1, std::list<Monome>::iterator it2) {
    return (it1->a == it2->a)&&(it1->b == it2->b)&&(it1->c == it2->c);
}

string Monome::to_string() const {
    string s;
    if(K>=0){
        s.push_back('+');
    }
    s.append(std::to_string(K));
    if(a!=0){
        s.append("*x^");
        s.append(std::to_string(a));
    }
    if(b!=0){
        s.append("*y^");
        s.append(std::to_string(b));
    }

    if(c!=0){
        s.append("*z^");
        s.append(std::to_string(c));
    }
    return s;
}

