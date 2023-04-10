#include "HashListTable.h"
HashListTable::HashListTable(int size) {
    for (int i = 0; i < size; ++i) {
        rows.emplace_back();
    }
    num_nonzero = 0;
}
void HashListTable::rehash() {
    // Увеличиваем размер
    int new_size = num_nonzero * REHASH_CONST;

    // С целью избежать многократного хэширования одних и тех же элементов
    // Я создаю второй массив
    vector<vector<Node>> new_rows;
    new_rows.reserve(new_size);
for (int i = 0; i < new_size; ++i) {
        new_rows.emplace_back();
    }
    bool inserted; // Вставлен ли элемент на место нулевого
    for(auto& v:rows)
        for(auto& node:v){
            // Новый индекс
            int new_index = hash(node.name,new_size);
            auto& new_v = new_rows[new_index];

            inserted = false;
            for(auto& t : new_v)
                if(t.is_zero()){
                    t = node;
                    inserted = true;
                }
            if(!inserted)
                new_v.push_back(node);
        }
    rows = new_rows;
    new_rows.clear();
}
void HashListTable::Insert(Node val) {
    if (rows.empty()) {
        vector<Node> v;
        v.push_back(val);
        rows.push_back(v);
        num_nonzero++;
        return;
    }
    /*cout << "Here" << endl;
    cout << val.name << endl;*/
    int index = HashListTable::hash(val.name,rows.size());
    auto& v = rows[index];

    bool inserted = false;

    for (auto& t : v)
        if (t.name == val.name) {
            t = val;
            inserted = true;
            break;
        }
    if(!inserted)
        for(auto& t : v)
            if(t.is_zero()){
                t = val;
                inserted = true;
                break;
            }
    if(!inserted)
        rows[index].push_back(val);
    num_nonzero++;
    if(num_nonzero > (rows.size()/REHASH_CONST))
        rehash();
}
int HashListTable::hash(const string& name, int modulus) {
    /*if (rows.empty()) {
        return 0;
    }*/
    std::hash<string> hasher;
    std::size_t hashCode = hasher(name);
    size_t r = hashCode; 
    r %= modulus;
    return r;
}


Polynome HashListTable::Take_elem(string name) {
    int index =hash(name,rows.size());
    auto& v = rows[index];
    for(auto& t : v)
        if(t.name == name)
            return t.data;

    throw std::invalid_argument("The element wasn't found!");

}
void HashListTable::Del(string name) {
    int index = hash(name,rows.size());

    auto& v = rows[index];

    for(auto& t : v)
        if(t.name == name){
            t.name = " ";
            t.data = Polynome("0");
        }

}

HashListTable ::~HashListTable() {
    rows.clear();
}

HashListTable::HashListTable() {
    num_nonzero = 0;
}

int HashListTable::Search(string) {
    return 0;
}

void HashListTable::Print() {
    cout << "This hash table is:" << endl;
    for (auto& row : rows) {
        for (auto& node : row) {
            cout << "<"<<node.name<<"->"<< hash(node.name,rows.size()) << "> ";
        }
        cout << endl;
    }
}

string HashListTable::to_string() {
    string res;
    for (auto& row : rows) {
        for (auto& node : row) {
            if(!node.is_zero())
                res+= node.name + " " + node.data.to_string() + " | ";
        }
    }
    return res;
}
