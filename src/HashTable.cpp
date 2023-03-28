#include "HashTable.h"
HashTable::HashTable(int size) {
    for (int i = 0; i < size; ++i) {
        rows.emplace_back();
    }
    num_nonzero = 0;
}
void HashTable::rehash() {
    int new_size = num_nonzero * REHASH_CONST;
    int s = rows.size();
    // Увеличиваем размер
    for (int i = 0; i < new_size-s; ++i) {
        rows.emplace_back();
    }
    // Теперь происходит перехэширование
    for (auto& elem:rows)
        if(!elem.is_zero()){
            int new_index = hash(elem.name);
            auto& t = rows[new_index];
            std::swap(elem,t);
        }
}
void HashTable::Insert(Node val) {
    int index = hash(val.name);
    while((index < rows.size())&&(!(rows[index].is_zero())))
        index++;
    if(index < rows.size()){
        num_nonzero++;
        rows.insert(rows.begin()+index,val);

        if(num_nonzero > (rows.size()/REHASH_CONST))
            rehash();
    }
    else{
        rehash();
    }
}
int HashTable::hash(string name) {
    int hashCode = 0;
    for (int i = 0; i < name.length(); i++) {
        hashCode += name[i] * pow(PRIME_CONST, i);
    }
    return (hashCode*hashCode + 1) % rows.size();
}


Polynome HashTable::Take_elem(string name) {
    int index = hash(name);
    return rows[index].data;
}
void HashTable::Del(string name) {
    int index = hash(name);
    auto& t = rows[index];
    t.name = " ";
    t.data = Polynome("0");
}

HashTable ::~HashTable() {
    rows.clear();
}

HashTable::HashTable() {
num_nonzero = 0;
}

int HashTable::Search(string) {
    return 0;
}

void HashTable::Print() {

}
