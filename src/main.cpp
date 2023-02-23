#include <iostream>
#include "polynomial.h"
using namespace std;
int main(){
    Polynome p("32*y^2*z^3+76*x^1-975*y^798*z^560");
    //auto p1 = p.differentiate(1);
    p.print();
    return 0;
}

