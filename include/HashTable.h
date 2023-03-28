#ifndef POLYNOMIAL_HASHTABLE_H
#define POLYNOMIAL_HASHTABLE_H
#include "Table.h"
#include <cmath>
#include <vector>
class HashTable:Table {
private:
    vector<Node> rows;

    const int PRIME_CONST = 31; // Нужно для хэш-функции
    int hash(string name); // Хэш-функция

    const short REHASH_CONST = 4; // Константа перехэширования. Оно происходит при числе непустых > размер/REHASH_CONST
    int num_nonzero{}; // Это число добавленных элементов. Учитывается для перехэширования
    void rehash(); // Для перехэширования, когда таблицы не хватает
public:
    HashTable(); // Пустой конструктор
    explicit HashTable(int size); // Конструктор по размеру
    void Insert(Node) override;
    void Del(string) override;
    int Search(string) override;
    Polynome Take_elem(string) override;
    void Print() override;
    ~HashTable() override;
};


#endif
