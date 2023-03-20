//
// Created by aleksei on 16.02.23.
//

#include "calculator.h"

void Calculator::insert(const string& name, Polynome p) {
    Node* node = new Node();
    node->name = name;
    node->data = p;
    for(auto t: tables)
        t->Insert(*node);
    delete node;
}
Polynome Calculator::get(const string& name) const {
    // TODO: убедиться, что Table выкинет исключение
    Table* table = tables.front();
    return table->Take_elem(name);
}