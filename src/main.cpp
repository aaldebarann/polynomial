#include <iostream>
//#include <algorithm>
#include "polynomial.h"
using namespace std;
int tats(){
    Polynome p1("x * y - 6");
    Polynome p2("x^2 * z - y");
    //auto p1 = p.differentiate(1);
    auto t = p1*p2;
    t.print();
//    Monome m1(1,1,2,3);
//    Monome m2(1,1,1,3);
//    list<Monome> l1 = {m1,m2};
//    for (auto& el:l1) {
//        el.print();
//    }
//    cout << endl;
//    l1.sort(Monome::compare);
//    //l1.sort(Monome::compare);
//    //std::sort(l1.begin(),l1.end(),Monome::compare);
//    for (auto& el:l1) {
//        el.print();
//    }
    return 0;
}

