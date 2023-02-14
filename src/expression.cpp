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
    lType t = null; // тип текущей лексемы
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
                if(isEnd(c)) {
                    b = i;
                    t = end;
                } else if(isOperation(c)) {
                    b = i;
                    t = operation;
                } else {
                    throw invalid_argument("Invalid expression");
                }
                break;
            case (variable):
                if(isLetter(c) || isDigit(c))
                    continue;
                // считывание переменной окончено
                infix.emplace_back(variable, text.substr(b, i - b));
                operands.insert({text.substr(b,i - b), 0.0});
                if(isEnd(c)) {
                    b = i;
                    t = end;
                } else if(isOperation(c)) {
                    b = i;
                    t = operation;
                } else {
                    throw invalid_argument("Invalid expression");
                }
                break;
            case (operation):
                // считывание операции окончено
                infix.emplace_back(operation, text.substr(b, i - b));
                if(isBegin(c)) {
                    b = i;
                    t = begin;
                } else if(isDigit(c) || isPoint(c) || isMinus(c)) {
                    b = i;
                    t = number;
                } else if(isLetter(c)) {
                    b = i;
                    t = variable;
                } else {
                    throw invalid_argument("Invalid expression");
                }
                break;
            case (begin):
                // считывание открывающей скобки окончено
                allBracketsAreClosed++;
                infix.emplace_back(begin, text.substr(b, i - b));
                if(isBegin(c)) {
                    b = i;
                    t = begin;
                } else if(isDigit(c) || isPoint(c) || isMinus(c)) {
                    b = i;
                    t = number;
                } else if(isLetter(c)) {
                    b = i;
                    t = variable;
                } else {
                    throw invalid_argument("Invalid expression");
                }
                break;
            case (end):
                // считывание закрывающей скобки окончено
                allBracketsAreClosed--;
                infix.emplace_back(end, text.substr(b, i - b));
                if(isEnd(c)) {
                    b = i;
                    t = end;
                } else if(isOperation(c)) {
                    b = i;
                    t = operation;
                } else {
                    throw invalid_argument("Invalid expression");
                }
                break;
            case (null):
                // начало выражения
                if(isBegin(c)) {
                    b = i;
                    t = begin;
                } else if(isDigit(c) || isPoint(c) || isMinus(c)) {
                    b = i;
                    t = number;
                } else if(isLetter(c)) {
                    b = i;
                    t = variable;
                } else {
                    throw invalid_argument("Invalid expression");
                }
                break;
        }
    }
    infix.emplace_back(t, text.substr(b, text.size() - b));
    if(t == variable)
        operands.insert({text.substr(b,text.size() - b), 0.0});
    if(t == end)
        allBracketsAreClosed--;
    if(t == begin)
        allBracketsAreClosed++;

    if(allBracketsAreClosed != 0)
        throw invalid_argument("Invalid expression: troubles with brackets");
    if((t != end && t != variable && t != number)) {
        throw invalid_argument("Invalid expression: invalid ending");
    }
} // текст -> набор лексем

void ArithmeticExpression::toPostfix()
{
  stack<pair<lType, string>> st;
  pair<lType, string> stackItem;
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
                if(lexem.first == variable)
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
