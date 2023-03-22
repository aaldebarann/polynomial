//
// Created by aleksei on 16.02.23.
//
#pragma once

#include <iostream>
#include <list>
#include "expression.h"
#include "UnorderedTB.h"
#include "OrderedTB.h"
#include "List_TB.h"
#include "Tree.h"

using namespace std;

class Calculator {
    list<Table *> tables;
public:
    explicit Calculator(bool allTables = true) {
        tables.push_back(new UnorderedTB());
        if(allTables) {
            tables.push_back(new OrderedTB());
            tables.push_back(new List_TB());
        }
    }
    ~Calculator() {
        for(auto t: tables)
            delete t;
    }

    Polynome get(const string& name); // возвращает полином по имени, кидает исключение, если не найден
    void insert(const string& name, Polynome p); // вставляет полином во все используемые таблицы
    Table* activeTable(); // активная таблица
    /* Пояснение:
     * задание требует хранить полиномы во всех шести таблиц одновременно,
     * однако при вычислениях используется одна - актуальная
     * в текущей версии она задается программистом
     * TODO: дать возможность пользователю выбирать активную таблицу
     */

    string interpret(string); // интерпретировать строку, введенную пользователей
    // результирующая строка должна быть выведена пользователю

private:
    static void deleteAll(string& str, char toDelete) {
        int spaces = 0;
        for(int i = 0; i < str.size(); i++) {
            str[i - spaces] = str[i];
            if(str[i] == toDelete)
                spaces++;
        }
        str.erase(str.size() - spaces, spaces);
    }
    static bool onlyConstants(const string& str) {
        for(char c: str)
            if('a' <= c && c < 'x' || 'A' <= c && c <= 'Z' || c == '_' )
                return false;
        return true;
    } // возвращает true, если выражение не содержит имен полиномов
};

