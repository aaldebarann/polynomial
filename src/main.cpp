#include <iostream>
#include "polynomial.h"
using namespace std;
int main(){
    Polynome p("-x^7*y*z+16.3*y*z^2");
    //auto p1 = p.differentiate(1);
    p.print();
    return 0;
}

