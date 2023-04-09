#ifndef POLYNOMIAL_HASHNEXTTABLE_H
#define POLYNOMIAL_HASHNEXTTABLE_H

#include "Table.h"
#include <cmath>
#include <vector>
#include <unordered_map>
#include <string>
class HashNextTable: public Table {
private:
    vector<Node> rows;

    int hash(const string& name,int modulus); // Хэш-функция

    const short REHASH_CONST = 4; // Константа перехэширования. Оно происходит при числе непустых > размер/REHASH_CONST
    int num_nonzero{}; // Это число добавленных элементов. Учитывается для перехэширования
    void rehash(); // Для перехэширования, когда таблицы не хватает
public:
    HashNextTable(); // Пустой конструктор
    explicit HashNextTable(int size); // Конструктор по размеру
    void Insert(Node) override;
    void Del(string) override;
    int Search(string) override;
    Polynome Take_elem(string) override;
    void Print() override;
    ~HashNextTable() override;
};


#endif //POLYNOMIAL_HASHNEXTTABLE_H
