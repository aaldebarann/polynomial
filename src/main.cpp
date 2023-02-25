#include <iostream>
#include "polynomial.h"
using namespace std;
int main(){
    Polynome p("-12,37*y*z");
    //auto p1 = p.differentiate(1);
    p.print();
    return 0;
}

