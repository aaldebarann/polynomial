#include "List_TB.h"
List_TB::List_TB() {
}
void List_TB::Insert(Node val) {
    rows.push_back(val);
}
int List_TB::Search(string name) {
    list <Node>::iterator Iter;
    int i = 0;

    for (Iter = rows.begin(); Iter != rows.end(); Iter++) {
        if ((*Iter).name == name) {
            return i;
        }
        i++;
    }




}


Polynome List_TB::Take_elem(string name) {
    list <Node>::iterator Iter;
    int i = 0;
    for (Iter = rows.begin(); Iter != rows.end(); Iter++) {
        if ((*Iter).name == name) {
            return (*Iter).data;
        }
        i++;
    }
    string message("variable was not found: "+name);
    throw invalid_argument(message);

};
void List_TB::Del(string name) {
    list <Node>::iterator Iter;
    int i = 0;
    bool k = false;
    try
    {
        for (Iter = rows.begin(); Iter != rows.end(); Iter++) {
            if ((*Iter).name == name) {
                rows.erase(Iter);
                k = true;
                break;
            }
            i++;
        }
        if (k == false) {
            throw invalid_argument("ERROR");
        }
    }
    catch (const std::exception&)
    {
        cout << "id not found" << endl;
    }
};
void List_TB::Print() {
    list <Node>::iterator Iter;
    for (Iter = rows.begin(); Iter != rows.end(); Iter++) {
        cout << "------------------------------------" << endl;
        cout <<(*Iter).name << " | ";
        (*Iter).data.print();
        cout << endl;
    }
};
List_TB ::~List_TB() {
    rows.clear();
};