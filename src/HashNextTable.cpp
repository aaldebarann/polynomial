
#include "HashNextTable.h"
HashNextTable::HashNextTable(int size) {
    for (int i = 0; i < size; ++i) {
        rows.emplace_back();
    }
    num_nonzero = 0;
}
void HashNextTable::rehash() {
    // Увеличиваем размер
    int new_size = num_nonzero * REHASH_CONST;
    // С целью избежать многократного хэширования одних и тех же элементов
    // Я создаю второй массив
    vector<Node> new_rows;
    new_rows.reserve(new_size);

    for (int i = 0; i < new_size; ++i)
        new_rows.emplace_back();

    for(auto& node:rows){
        // Новый индекс
        int new_index = hash(node.name,new_size);
        while ((new_index < new_rows.size()) && (!(new_rows[new_index].is_zero()))) {
            new_index++;
            new_index %= new_size;
        }
            
        new_rows[new_index]=node;
    }
    rows = new_rows;
    new_rows.clear();
//    int new_size = num_nonzero * REHASH_CONST;
//    // Увеличиваем размер
//    rows.resize(new_size);
//    // Теперь происходит перехэширование
//    for (auto& elem:rows)
//        if(!elem.is_zero()){
//            int new_index = hash(elem.name);
//            auto& t = rows[new_index];
//            std::swap(elem,t);
//        }
}
void HashNextTable::Insert(Node val) {
    if (rows.empty()) {
        rows.push_back(val);
        num_nonzero++;
        return;
    }
    int index = hash(val.name,rows.size());
    while((index < rows.size())&&(!(rows[index].is_zero())))
        index++;
    if(index < rows.size()){
        num_nonzero++;
        rows[index] = val;
        //rows.insert(rows.begin()+index,val);

        if(num_nonzero > (rows.size()/REHASH_CONST))
            rehash();
    }
    else{
        rows.push_back(val);
        num_nonzero++;
        rehash();
    }
}
int HashNextTable::hash(const string& name,int modulus) {
    std::hash<string> hasher;
    std::size_t hashCode = hasher(name);
    return hashCode % modulus;
}


Polynome HashNextTable::Take_elem(string name) {
    int index = hash(name,rows.size());
    
    int s = 0;
    while (s < rows.size()) {
        
        auto& t = rows[index];
        if (t.name == name) {
            return t.data;
        }
        index++;
        index %= rows.size();
        s++;
    }
  
    throw std::invalid_argument("The element wasn't found!");
    
}
void HashNextTable::Del(string name) {
    int index = hash(name,rows.size());
    auto& t = rows[index];
    t.name = " ";
    t.data = Polynome("0");
}

HashNextTable ::~HashNextTable() {
    rows.clear();
}

HashNextTable::HashNextTable() {
    num_nonzero = 0;
}

int HashNextTable::Search(string) {
    return 0;
}

void HashNextTable::Print() {
    for (auto& r : rows)
        cout << r.name << " -> " << hash(r.name,rows.size()) << endl;
}
