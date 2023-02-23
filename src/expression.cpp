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
    State t = null; // тип текущей лексемы
    int b = 0; //  индекс начала текущей лексемы
    int allBracketsAreClosed = 0;
    for(int i = 0; i < text.size(); i++) {;
        char c = text[i];
        if(c == ' ')
            continue;
        switch(t) {
            case (sNumber):
                if(isPoint(c) || isDigit(c))
                    continue;
                // считывание числа окончено
                infix.emplace_back(number, text.substr(b, i - b));
                b = i;
                if(isEnd(c)) {
                    t = sEnd;
                } else if(isOperation(c)) {
                    t = sOperation;
                } else {
                    throw invalid_argument("Invalid expression");
                }
                break;
            case (sVariable):
                if(isLetter(c) || isDigit(c))
                    continue;
                if(isBegin(c)) {
                    // считывается не переменная, а функция
                    t = sFunction;
                } else {
                    // считывание переменной окончено
                    infix.emplace_back(variable, text.substr(b, i - b));
                    operands.insert({text.substr(b, i - b), 0.0});
                    b = i;
                    if (isEnd(c)) {
                        t = sEnd;
                    } else if (isOperation(c)) {
                        t = sOperation;
                    } else {
                        throw invalid_argument("Invalid expression");
                    }
                }
                break;
            case (sOperation):
                // считывание операции окончено
                infix.emplace_back(operation, text.substr(b, i - b));
                b = i;
                if(isBegin(c)) {
                    t = sBegin;
                } else if(isDigit(c) || isPoint(c) || isMinus(c)) {
                    t = sNumber;
                } else if(isLetter(c)) {
                    t = sVariable;
                } else {
                    throw invalid_argument("Invalid expression");
                }
                break;
            case (sBegin):
                // считывание открывающей скобки окончено
                allBracketsAreClosed++;
                infix.emplace_back(begin, text.substr(b, i - b));
                b = i;
                if(isBegin(c)) {
                    t = sBegin;
                } else if(isDigit(c) || isPoint(c) || isMinus(c)) {
                    t = sNumber;
                } else if(isLetter(c)) {
                    t = sVariable;
                } else {
                    throw invalid_argument("Invalid expression");
                }
                break;
            case (sEnd):
                // считывание закрывающей скобки окончено
                allBracketsAreClosed--;
                infix.emplace_back(end, text.substr(b, i - b));
                b = i;
                if(isEnd(c)) {
                    t = sEnd;
                } else if(isOperation(c)) {
                    t = sOperation;
                } else {
                    throw invalid_argument("Invalid expression");
                }
                break;
            case(sFunction):
                if(isLetter(c) || isDigit(c) || isMinus(c) || isPoint(c) || isComma(c) || isEnd(c))
                    continue;
                else {
                    // считывание функции будет окончено на следующем шаге
                    if (isEnd(c)) {
                        t = sFend;
                    } else {
                        throw invalid_argument("Invalid expression");
                    }
                }
                break;
            case (sFend):
                // считывание функции окончено
                infix.emplace_back(function, text.substr(b, i - b));
                b = i;
                if (isEnd(c)) {
                    t = sEnd;
                } else if (isOperation(c)) {
                    t = sOperation;
                } else {
                    throw invalid_argument("Invalid expression");
                }
                break;
            case (null):
                // начало выражения
                b = i;
                if(isBegin(c)) {
                    t = sBegin;
                } else if(isDigit(c) || isPoint(c) || isMinus(c)) {
                    t = sNumber;
                } else if(isLetter(c)) {
                    t = sVariable;
                } else {
                    throw invalid_argument("Invalid expression");
                }
                break;
        }
    }
    switch (t) {
        case sVariable:
            infix.emplace_back(variable, text.substr(b, text.size() - b));
            operands.insert({text.substr(b,text.size() - b), 0.0});
            break;
        case sEnd:
            infix.emplace_back(end, text.substr(b, text.size() - b));
            allBracketsAreClosed--;
            break;
        case sNumber:
            infix.emplace_back(number, text.substr(b, text.size() - b));
            break;
        default:
            throw invalid_argument("Invalid expression: invalid ending");
    }
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
    case sBegin:
      st.push(lexem);
      break;
    case sEnd:
      stackItem = st.top();
      st.pop();
      while (stackItem.first != sBegin) {
        postfix.emplace_back(stackItem);
        stackItem = st.top();
        st.pop();
      }
      break;
    case sOperation:
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

double ArithmeticExpression::calculate(istream& input, ostream& output)
{
    readOperands(input, output);
    double left, right; // операнды
    stack<double> st;
    for(auto& lexem: postfix) {
        switch (lexem.second[0]) {
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
                if(lexem.first == sVariable)
                    st.push(operands[lexem.second]);
                else
                    st.push(stod(lexem.second));
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
