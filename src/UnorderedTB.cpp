#include "UnorderedTB.h"
UnorderedTB::UnorderedTB() {
    row = new Node[1];
    marker = -1;
}
void UnorderedTB::Insert(Node val) {
    if (marker == -1) {
        marker = 0;
        row[marker] = val;
    }
    else {
        if(Search(val.name) == marker + 1){
            if ((marker == int(sizeof(row)) / 4) || marker == 0) {
                Node* tmp = new Node[int(sizeof(row)) * 2];
                for (int i = 0; i <= marker; i++) {
                    tmp[i] = row[i];
                }
                delete[]row;

                row = tmp;
            }
            row[++marker] = val;
        }
        else {
            row[Search(val.name)] = val;
        }
    }
}
void UnorderedTB::Del(string name) {
    int i = Search(name);
    if(marker!=-1){
    if (i == marker) {
        marker--;
    }
    else {
        while (i < marker) {
            row[i] = row[i + 1];
            i++;
        }
        marker--;
    }
    }
}

int UnorderedTB::Search(string name) {
    int i = 0;

    while (i <= marker) {
        if (name == row[i].name) {
            return i;
        }
        i++;
    }
    return marker + 1;
}

Polynome UnorderedTB::Take_elem(string name) {
    if (Search(name) == marker +1) {

        string message("variable was not found: "+name);
        throw invalid_argument(message);
    }
    return row[Search(name)].data;
}

void UnorderedTB::Print() {
    int i = 0;
    while (i <= marker) {
        cout << "------------------------------------" << endl;
        cout << row[i].name << " | ";
        row[i].data.print();
        cout << endl;
        i++;
    }
}
string UnorderedTB::Print_() {
    int i = 0;
    string str;
    while (i <= marker) {
        str += (row[i].name + " | " + row[i].data.to_string());
        i++;
    }
    return str;
}


UnorderedTB:: ~UnorderedTB() {
    delete[]row;
    row = nullptr;
}
