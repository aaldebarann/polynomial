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

    Polynome get(const string& name) const; // возвращает полином по имени, кидает исключение, если не найден
    void insert(const string& name, Polynome p); // вставляет полином во все используемые таблицы

};

