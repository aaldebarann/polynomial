#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stack>
#include <cmath>
#include "polynomial.h"

using namespace std;

class ArithmeticExpression {
public:
    explicit ArithmeticExpression(const string& text);

    /* типы лексем - совпадают с состояниями конечного автомата
     * begin и end - открывающая и закрывающая скобки
     * fbegin, fend - открывающая и закрывающая скобки функции
     * comma - запятая между аргументами функции
     * numArg - числовой аргумент функции
     * strArg - строковый аргумент функции
     */
    enum LType {number, variable, operation, begin, end, function, fbegin, fend, comma, numArg, strArg,  null};


    string getString() const { return text; }
    vector<pair<LType, string>> getInfix() const { return infix; }
    string getPostfix() const {
        string postfixStr;
        for(auto& p: postfix) {
            postfixStr += p.second;
        }
        return postfixStr;
    }

    double calculate(istream& input = cin, ostream& output = cout); // Ввод переменных, вычисление по постфиксной форме

private:
    // приоритет операций
    static map<char, int> priority; // все разрешенные операции односимвольные

    string text;
    vector<pair<LType, string>> infix; // набор пар (тип_лексемы, текст_лексемы)
    vector<pair<LType, string>> postfix; // набор пар (тип_лексемы, текст_лексемы)
    map<string, double> operands;

    // проверка символов
    static bool isDigit(char c); // 0 ... 9
    static bool isLetter(char c); // a ... z, A ... Z, _
    static bool isOperation(char c); // +, -, *, /
    static bool isMinus(char c); // -
    static bool isPoint(char c); // -
    static bool isBegin(char c); // (
    static bool isEnd(char c); // )
    static bool isComma(char c); // ,

    static void deleteAll(string& str, char toDelete) {
        int spaces = 0;
        for(int i = 0; i < str.size(); i++) {
            str[i - spaces] = str[i];
            if(str[i] == toDelete)
                spaces++;
        }
        str.erase(str.size() - spaces, spaces);
    }

    void parse(); // текст -> набор лексем
    void toPostfix();
    void readOperands(istream& input, ostream& output);

    double calcFunction(int& i);
    double calcSqrt(int& i);

};

#endif
