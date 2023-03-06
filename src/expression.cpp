#include "expression.h"

map<char, int> ArithmeticExpression::priority = { {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2} };

ArithmeticExpression::ArithmeticExpression(const string& text)
{
    if(text.empty())
        throw invalid_argument("Creating arithmetic expression from an empty string");
    this->text = text;
    deleteAll(this->text, ' ');
    parse();
    toPostfix();
}

void ArithmeticExpression::parse() 
{
    LType t = null; // тип текущей лексемы
    int b = 0; //  индекс начала текущей лексемы
    int allBracketsAreClosed = 0;
    for(int i = 0; i < text.size(); i++) {;
        char c = text[i];
        if(c == ' ')
            continue;
        switch(t) {
            case (number):
                if(isPoint(c) || isDigit(c))
                    continue;
                // считывание числа окончено
                infix.emplace_back(number, text.substr(b, i - b));
                b = i;
                if(isEnd(c)) {
                    t = end;
                } else if(isOperation(c)) {
                    t = operation;
                } else {
                    throw invalid_argument("Invalid expression: smth after number");
                }
                break;
            case (variable):
                if(isLetter(c) || isDigit(c))
                    continue;
                if(isBegin(c)) {
                    // считывается не переменная, а функция
                    infix.emplace_back(function, text.substr(b, i - b));
                    b = i;
                    t = fbegin;
                } else {
                    // считывание переменной окончено
                    infix.emplace_back(variable, text.substr(b, i - b));
                    operands.insert({text.substr(b, i - b), 0.0});
                    b = i;
                    if (isEnd(c)) {
                        t = end;
                    } else if (isOperation(c)) {
                        t = operation;
                    } else {
                        throw invalid_argument("Invalid expression:  smth after variable");
                    }
                }
                break;
            case (operation):
                // считывание операции окончено
                infix.emplace_back(operation, text.substr(b, i - b));
                b = i;
                if(isBegin(c)) {
                    t = begin;
                } else if(isDigit(c) || isPoint(c) || isMinus(c)) {
                    t = number;
                } else if(isLetter(c)) {
                    t = variable;
                } else {
                    throw invalid_argument("Invalid expression:  smth after operator");
                }
                break;
            case (begin):
                // считывание открывающей скобки окончено
                allBracketsAreClosed++;
                infix.emplace_back(begin, text.substr(b, i - b));
                b = i;
                if(isBegin(c)) {
                    t = begin;
                } else if(isDigit(c) || isPoint(c) || isMinus(c)) {
                    t = number;
                } else if(isLetter(c)) {
                    t = variable;
                } else {
                    throw invalid_argument("Invalid expression:  smth after begin");
                }
                break;
            case (end):
                // считывание закрывающей скобки окончено
                allBracketsAreClosed--;
                infix.emplace_back(end, text.substr(b, i - b));
                b = i;
                if(isEnd(c)) {
                    t = end;
                } else if(isOperation(c)) {
                    t = operation;
                } else {
                    throw invalid_argument("Invalid expression:  smth after end");
                }
                break;
            case(fbegin):
                infix.emplace_back(fbegin, text.substr(b, i - b));
                b = i;
                if(isDigit(c) || isPoint(c) || isMinus(c)) {
                    t = numArg;
                } else if(isLetter(c)) {
                    t = strArg;
                } else {
                    throw invalid_argument("Invalid expression:  smth after fbegin");
                }
                break;
            case (fend):
                // считывание функции окончено
                infix.emplace_back(fend, text.substr(b, i - b));
                b = i;
                if (isEnd(c)) {
                    t = end;
                } else if (isOperation(c)) {
                    t = operation;
                } else {
                    throw invalid_argument("Invalid expression:  smth after fend");
                }
                break;
            case (numArg):
                if(isPoint(c) || isDigit(c))
                    continue;
                // считывание числового аргумента окончено
                infix.emplace_back(numArg, text.substr(b, i - b));
                b = i;
                if(isEnd(c)) {
                    t = fend;
                } else if(isComma(c)) {
                    t = comma;
                } else {
                    throw invalid_argument("Invalid expression:  smth after numArg");
                }
                break;
            case (strArg):
                if(isLetter(c) || isDigit(c))
                    continue;
                // считывание строкового аргумента окончено
                infix.emplace_back(strArg, text.substr(b, i - b));
                b = i;
                if(isEnd(c)) {
                    t = fend;
                } else if(isComma(c)) {
                    t = comma;
                } else {
                    throw invalid_argument("Invalid expression:  smth after strArg");
                }
                break;
            case (comma):
                // считывание числа окончено
                infix.emplace_back(comma, text.substr(b, i - b));
                b = i;
                if(isMinus(c) || isDigit(c)) {
                    t = numArg;
                } else if(isLetter(c)) {
                    t = strArg;
                } else {
                    throw invalid_argument("Invalid expression:  smth after comma");
                }
                break;
            case (null):
                // начало выражения
                b = i;
                if(isBegin(c)) {
                    t = begin;
                } else if(isDigit(c) || isPoint(c) || isMinus(c)) {
                    t = number;
                } else if(isLetter(c)) {
                    t = variable;
                } else {
                    throw invalid_argument("Invalid expression: invalid start");
                }
                break;
        }
    }
    infix.emplace_back(t, text.substr(b, text.size() - b));
    if(t == variable)
        operands.insert({text.substr(b,text.size() - b), 0.0});
    else if(t == end)
        allBracketsAreClosed--;
    else if(t != number && t != fend)
        throw invalid_argument("Invalid expression: invalid ending");

    if(allBracketsAreClosed != 0) {
        throw invalid_argument("Invalid expression: troubles with brackets");
    }
} // текст -> набор лексем

void ArithmeticExpression::toPostfix()
{
  stack<pair<LType, string>> st;
  pair<LType, string> stackItem;
  for (auto& lexem : infix) {
    switch (lexem.first) {
    case begin:
      st.push(lexem);
      break;
    case end:
      stackItem = st.top();
      st.pop();
      while (stackItem.first != begin) {
        postfix.emplace_back(stackItem);
        stackItem = st.top();
        st.pop();
      }
      break;
    case operation:
      while (!st.empty()) {
        stackItem = st.top();
        st.pop();
        if (priority[lexem.second[0]] <= priority[stackItem.second[0]])
            postfix.emplace_back(stackItem);
        else {
          st.push(stackItem);
          break;
        }
      }
      st.push(lexem);
      break;
    default:
        postfix.emplace_back(lexem);
    }
  }
  while (!st.empty()) {
      stackItem = st.top();
      st.pop();
      postfix.emplace_back(stackItem);
  }
}

double ArithmeticExpression::calcSqrt(int& i) {
    // i -> function
    i++;
    // i -> fbegin
    i++;
    // i -> argument
    auto& arg = postfix[i];
    if(arg.first != numArg )
        throw invalid_argument("sqrt() must have a number as an argument");
    double result = sqrt(stod(arg.second));
    i++;
    // i -> fend
    arg = postfix[i];
    if(arg.first != fend) {
        throw invalid_argument("sqrt() must have only one argument");
    }
    return result;
}
double ArithmeticExpression::calcFunction(int& i) {
    // i is first lexem of function in postfix
    string& name = postfix[i].second;
    if (name == "sqrt")
        return calcSqrt(i);
    else
        throw invalid_argument("Unknown function \""+name+"\"");
}

double ArithmeticExpression::calculate(istream& input, ostream& output)
{
    readOperands(input, output);
    Polynome left, right; // операнды
    stack<Polynome> st;
    for(int i = 0; i < postfix.size(); i++) {
        auto& lexem  = postfix[i];
        switch (lexem.second[0]) {
            // с символов + - * / могут начинаться ТОЛЬКО операции
            case '+':
                right = st.top();
                st.pop();
                left = st.top();
                st.pop();
                st.push(left + right);
                break;
            case '-':
                right = st.top();
                st.pop();
                left = st.top();
                st.pop();
                st.push(left - right);
                break;
            case '*':
                right = st.top();
                st.pop();
                left = st.top();
                st.pop();
                st.push(left * right);
                break;
            case '/':
                right = st.top();
                st.pop();
                left = st.top();
                st.pop();
                st.push(left / right);
                break;
            default:
                if(lexem.first == variable)
                    st.push(Polynome(operands[lexem.second]));
                else if(lexem.first == number)
                    st.push(Polynome(stod(lexem.second)));
                else  {
                    // lexem is function
                    st.push(calcFunction(i)); // i will be changed
                }
        }
    }
    return st.top();
}

void ArithmeticExpression::readOperands(istream& input, ostream& output) {
    output << "Enter values:"<< endl;
    for(auto& o: operands) {
        output << o.first << " = ";
        input >> o.second;
    }
}

bool ArithmeticExpression::isDigit(char c) {
    return '0' <= c && c <= '9';
}
bool ArithmeticExpression::isLetter(char c) {
    return 'a' <= c && c <= 'z' || 'A' <= c && c <= 'Z' || c == '_';
}
bool ArithmeticExpression::isOperation(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}
bool ArithmeticExpression::isMinus(char c) {
    return c == '-';
}
bool ArithmeticExpression::isBegin(char c) {
    return c == '(';
}
bool ArithmeticExpression::isEnd(char c) {
    return c == ')';
}
bool ArithmeticExpression::isPoint(char c) {
    return c == '.';
}
bool ArithmeticExpression::isComma(char c) {
    return c == ',';
}
