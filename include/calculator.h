//
// Created by aleksei on 16.02.23.
//

#ifndef POLYNOMIAL_CALCULATOR_H
#define POLYNOMIAL_CALCULATOR_H


#include <iostream>
#include "expression.h"
using namespace std;

int m() {
    cout << "Enter arithmetic expression:"<<endl;
    string str;
    cin >> str;
    ArithmeticExpression expr(str);
    expr.calculate();
    return 0;
}

#endif //POLYNOMIAL_CALCULATOR_H
