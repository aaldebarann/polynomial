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

Polynome ArithmeticExpression::calcSqrt(int& i) {
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
    return Polynome(result); // TODO: fix narrowing conversion from 'double' to 'float'
}
Polynome ArithmeticExpression::calcDifferentiate(int& i, Table* table) {
    // i -> function
    i++;
    // i -> fbegin
    i++;
    // i -> polynomial name (strArg)
    auto& name = postfix[i];
    if(name.first != strArg )
        throw invalid_argument("D() must have polynomial name as a first argument");
    Polynome p = table->Take_elem(name.second);
    i++;
    // i -> comma
    i++;
    // i -> variable (strArg)
    auto& var = postfix[i];
    if(var.first != strArg ||
    (var.second != "x" && var.second != "y" && var.second != "z") )
        throw invalid_argument(R"(D() must have 'x', 'y' or 'z' as a second argument)");
    Polynome result = p.differentiate((short)(var.second[0] - 'x'));
    i++;
    // i -> fend
    auto& arg = postfix[i];
    if(arg.first != fend) {
        throw invalid_argument("D() must have only two argument");
    }
    return result;
}
Polynome ArithmeticExpression::calcIntegrate(int& i, Table* table) {
    // i -> function
    i++;
    // i -> fbegin
    i++;
    // i -> polynomial name (strArg)
    auto& name = postfix[i];
    if(name.first != strArg )
        throw invalid_argument("I() must have polynomial name as a first argument");
    Polynome p = table->Take_elem(name.second);
    i++;
    // i -> comma
    i++;
    // i -> variable (strArg)
    auto& var = postfix[i];
    if(var.first != strArg ||
       (var.second != "x" && var.second != "y" && var.second != "z") )
        throw invalid_argument(R"(I() must have 'x', 'y' or 'z' as a second argument)");
    Polynome result = p.integrate((short)(var.second[0] - 'x'));
    i++;
    // i -> fend
    auto& arg = postfix[i];
    if(arg.first != fend) {
        throw invalid_argument("I() must have only two argument");
    }
    return result;
}
Polynome ArithmeticExpression::calcValueAt(int& i, Table* table) {
    // i -> function
    i++;
    // i -> fbegin
    i++;
    // i -> polynomial name (strArg)
    auto& name = postfix[i];
    if(name.first != strArg )
        throw invalid_argument("AT() must have polynomial name as a first argument");
    Polynome p = table->Take_elem(name.second);
    i++;
    // i -> comma
    i++;
    // i -> x value (numArg)
    auto& x = postfix[i];
    if(x.first != numArg)
        throw invalid_argument(R"(AT() must have a number as a second argument)");
    i++;
    // i -> comma
    i++;
    // i -> y value (numArg)
    auto& y = postfix[i];
    if(y.first != numArg)
        throw invalid_argument(R"(AT() must have a number as a third argument)");
    i++;
    // i -> comma
    i++;
    // i -> z value (numArg)
    auto& z = postfix[i];
    if(z.first != numArg)
        throw invalid_argument(R"(AT() must have a number as a fourth argument)");
    i++;
    // i -> fend
    auto& arg = postfix[i];
    if(arg.first != fend) {
        throw invalid_argument("D() must have only two argument");
    }
    Polynome result {p.value_at((float)stod(x.second), (float)stod(y.second), (float)stod(z.second))};
    return result;
}
Polynome ArithmeticExpression::calcFunction(int& i, Table* table) {
    // i is first lexem of function in postfix
    string& name = postfix[i].second;
    if (name == "sqrt")
        return calcSqrt(i);
    else if (name == "D")
        return calcDifferentiate(i, table);
    else if (name == "I")
        return calcIntegrate(i, table);
    else if (name == "AT")
        return calcValueAt(i, table);
    else
        throw invalid_argument("Unknown function \""+name+"\"");
}

Polynome ArithmeticExpression::getPolynome(const string& name, Table *table) {
    // TODO: убедиться, что Table выкинет исключение
    return table->Take_elem(name);
}

Polynome ArithmeticExpression::calculate(Table *table)
{
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
                throw invalid_argument("Division is not implemented yet");
                /*
                right = st.top();
                st.pop();
                left = st.top();
                st.pop();
                st.push(left / right);
                */
                break;
            default:
                if(lexem.first == variable)
                    // in case of numeric operands
                    // st.push(operands[lexem.second]);
                    // in case of Polynome operands
                    try {
                        Polynome pol = getPolynome(lexem.second, table);
                        st.push(pol);
                    } catch (exception& e) {
                        string message = "Unknown variable \'"+lexem.second+"\'";
                        throw invalid_argument(message);
                    }
                else if(lexem.first == number)
                    st.push(Polynome(lexem.second));
                else  {
                    // lexem is function
                    st.push(calcFunction(i, table)); // i will be changed
                }
        }
    }
    return st.top();
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
