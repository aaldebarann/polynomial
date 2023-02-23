#include <iostream>
#include "polynomial.h"
using namespace std;
int main(){
    Polynome p("32*y^276*z^2870+1*x^2*z^20");
    auto p1 = p.differentiate(1);
    p1.print();
    return 0;
}

