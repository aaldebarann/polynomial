//
// Created by aleksei on 16.02.23.
//
#pragma once

#include <iostream>
#include <vector>
#include "expression.h"
#include "UnorderedTB.h"
#include "OrderedTB.h"
#include "List_TB.h"
#include "Tree.h"
#include "HashListTable.h"
#include "HashNextTable.h"

using namespace std;

class Calculator {
    vector<Table *> tables{};
public:
    enum TableType: unsigned {unordered = 0, list = 1, ordered = 2, tree = 3, hashList = 4, hashNext = 5};

    explicit Calculator(bool allTables = true);
    ~Calculator() {
        for(auto t: tables)
            delete t;
    }

    void setActive(TableType);
    void setActive(unsigned int type);
    Polynome get(const string& name); // возвращает полином по имени, кидает исключение, если не найден
    void insert(const string& name, const Polynome& p); // вставляет полином во все используемые таблицы
    Table* activeTable(); // активная таблица
    /* Пояснение:
     * задание требует хранить полиномы во всех шести таблиц одновременно,
     * однако при вычислениях используется одна - актуальная
     */

    string interpret(string); // интерпретировать строку, введенную пользователей
    // результирующая строка должна быть выведена пользователю
    string to_string(); // возвращает строковое представление активной таблицы
private:
    static void deleteAll(string& str, char toDelete);
    static bool onlyConstants(const string& str);
    Table* active;
};

