//
// Created by aleksei on 16.02.23.
//

#include "calculator.h"
Calculator:: Calculator(bool allTables) {
    tables.push_back(new UnorderedTB());
    if(allTables) {
        tables.push_back(new List_TB());
        tables.push_back(new OrderedTB());
        tables.push_back(new Tree());
        tables.push_back(new HashListTable());
        tables.push_back(new HashNextTable());
    }
    activeType = unordered;
}

void Calculator::setActive(TableType table) {
    activeType = table;
}
void Calculator::setActive(unsigned int type) {
    setActive(TableType(type));
}
void Calculator::insert(const string& name, const Polynome& p) {
    for(auto t: tables) {
      Node node;
      node.name = name;
      node.data = p;
      //t->Del(name);
      t->Insert(node);
    }
}
Polynome Calculator::get(const string& name) {
    // TODO: убедиться, что Table выкинет исключение
    Table* table = activeTable();
    return table->Take_elem(name);
}
Table* Calculator::activeTable() {
    return tables[activeType];
}

string Calculator::interpret(string str) {
    deleteAll(str, ' ');
    size_t i = str.find('=');
    if(i == string::npos) {
        // в строке отсутствует знак равенства
        // это арифметическое выражение, которое надо вычислить
        try {
            ArithmeticExpression expression(str);
            Polynome result = expression.calculate(activeTable());
            return result.to_string();
        } catch (exception& e) {
            return e.what();
        }
    } else {
        // в строке присутствует знак равенства
        // это выражение-присваивание, задающее значение нового полинома
        string name = str.substr(0, i);
        if(name== "x" || name == "y" || name == "z")
            return R"(Invalid variable name: "x", "y", "z" are reserved)";
        string value = str.substr(i + 1);
        try {
            if (!onlyConstants(value)) {
              // справа выражение из полиномов
              // перед инициализацией его надо вычислить
              //return "Assignment of an expression from polynomials is unavailable in current version"; // TODO: implement
              value = interpret(value);
            }
            Polynome pol{value};
            insert(name, pol);
            return "New value \""+name+"\" recorded";
        } catch (exception& e) {
            return e.what();
        }
    }
}
string Calculator::to_string() {
    string s;
    if(activeType == list || activeType == tree) {
        TableType tmp = activeType;
        activeType = unordered;
        s = activeTable()->Print_();
        activeType = tmp;
    } else {
        s = activeTable()->Print_();
    }
    return s;
}
void Calculator::deleteAll(string& str, char toDelete) {
    int spaces = 0;
    for(int i = 0; i < str.size(); i++) {
        str[i - spaces] = str[i];
        if(str[i] == toDelete)
            spaces++;
    }
    str.erase(str.size() - spaces, spaces);
}
bool Calculator::onlyConstants(const string& str) {
    for(char c: str)
        if('a' <= c && c < 'x' || 'A' <= c && c <= 'Z' || c == '_' )
            return false;
    return true;
}