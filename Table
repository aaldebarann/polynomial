#pragma once
#pragma once
#include <iostream>
#include <string.h>
#include <list>
#include <stdlib.h>
#include"polynomial.h"
using namespace std;

int Take_line(char z, string s) {
	unsigned int i = 0;
	char cur;
	cur = s[i];
	while (cur != z || i != sizeof(s)) {
		cur = s[i++];
	}
	return i;
}

const char* Tochar(string s) {
	char* c[sizeof(s)];
	int i = -1;
	while (i < (sizeof(s) - 1)) {
		c[++i] = &s[i];
	}
	const char* b = *c;
	return b;
}

string ToString(char* c) {
	char cur;
	string res;
	int i = -1;
	while (i < (sizeof(c) - 1))
	{
		cur = c[++i];
		res += cur;
	}
	return res;
}

struct Node
{
	unsigned int id;
	string name;
	Polynome data;
public:
	Node() {
		id = rand();
		name = " ";
	}
	/*Node(string s) {
		id = 0;
		char c[100] ;
		name = ToString(strncpy(c,Tochar(s), Take_line(' ', s)));
		data = ToString(strncpy(c,&s[Take_line(' ', s) + 2], sizeof(s) - Take_line(' ', s) - 1));
	}*/
};
class Table //абстрактный класс
{
public:

	virtual void Put(Node val) = 0; // добавить новый элемент в таблицу
	virtual void Del(string name) = 0; // удалить элемент по имени
	virtual void Del(int id) = 0; // удалить элемент по id
	virtual int Search(string name) = 0; // найти элемент по имени так же можно использовать что бы получить id элемента типо take только для id 
	virtual int Search(int id) = 0; // найти элемент по id
	virtual Polynome Take_elem(string name) = 0; // получить элемент по имени
	virtual Polynome Take_elem(int id) = 0; // получить элемент по id
	virtual void Print() = 0;// печать таблицы 
};

class Lmas : public Table
{
private:
	Node* row;
	int marker; // отмечает индекс последнего записанного элемента
public:
	Lmas() {
		row = new Node[1];
		marker = -1;
	}
	void Put(Node val) {
		if (marker == -1) {
			marker = 0;
			row[marker] = val;
		}
		else {
			if ((marker == sizeof(row) / 4) || marker == 0) {
				Node* tmp = new Node[sizeof(row) *2];
				for (int i = 0; i < (sizeof(row) / 4); i++) {
					tmp[i] = row[i];
				}
				delete[]row;

				row = tmp;
			}
			row[++marker] = val;
		}
	}
	void Del(string name) {
		int i = Search(name);
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
	void Del(int id) {
		int i = Search(id);
		if (i == marker) {
			marker--;
		}
		else{
		while (i < marker) {
			row[i] = row[i + 1];
			i++;
		}
		marker--;
		}
	}
	int Search(string name) {
		int i = 0;
		try
		{
			while (i <= marker) {
				if (name == row[i].name) {
					return i;
				}
				i++;
			}
			throw"ERROR";
		}
		catch (const std::exception&)
		{
			cout << "name not found" << endl;
		}

	}
	int Search(int id) {
		int i = 0;
		try
		{
			while (i <= marker) {
				if (id == row[i].id) {
					return i;
				}
				i++;
			}
			throw"ERROR";
		}
		catch (const std::exception&)
		{
			cout << "id not found" << endl;
		}

	}
	Polynome Take_elem(string name) {
		return row[Search(name)].data;
	}
	Polynome Take_elem(int id) {
		return row[Search(id)].data;
	}
	void Print() {
		int i = 0;
		cout << "Line mas table" << endl;
		while (i <= marker) {
			cout << "------------------------------------" << endl;
			cout << row[i].id << " | " << row[i].name << " | ";
			row[i].data.print();
			cout << endl;
			i++;
		}
	}
	~Lmas() {
		delete[]row;
		row = nullptr;
	}


};

class List : public Table
{
private:
	list <Node> rows;
public:
	List() {
	};
	void Put(Node val) {
		rows.push_back(val);
	}
	int Search(string name) {
		list <Node>::iterator Iter;
		int i = 0;
		try
		{
			for (Iter = rows.begin(); Iter != rows.end(); Iter++) {
				if ((*Iter).name == name) {
					return i;
				}
				i++;
			}
			throw"ERROR";

		}
		catch (const std::exception&)
		{
			cout << "name not found" << endl;
		}


	}
	int Search(int id) {
		list <Node>::iterator Iter;
		int i = 0;
		try
		{
			for (Iter = rows.begin(); Iter != rows.end(); Iter++) {
				if ((*Iter).id == id) {
					return i;
				}
				i++;
			}
			throw"ERROR";

		}
		catch (const std::exception&)
		{
			cout << "id not found" << endl;
		}


	}

	Polynome Take_elem(string name) {
		list <Node>::iterator Iter;
		int i = 0;
		try
		{
			for (Iter = rows.begin(); Iter != rows.end(); Iter++) {
				if ((*Iter).name == name) {
					return (*Iter).data;
				}
				i++;
			}
			throw"ERROR";
		}
		catch (const std::exception&)
		{
			cout << "name not found" << endl;
		}

	}
	Polynome Take_elem(int id) {
		list <Node>::iterator Iter;
		int i = 0;
		try
		{
			for (Iter = rows.begin(); Iter != rows.end(); Iter++) {
				if ((*Iter).id == id) {
					return (*Iter).data;
				}
				i++;
			}
			throw"ERROR";
		}
		catch (const std::exception&)
		{
			cout << "id not found" << endl;
		}

	}
	void Del(string name) {
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
				throw"ERROR";
			}
		}
		catch (const std::exception&)
		{
			cout << "id not found" << endl;
		}
	}
	void Del(int id) {
		list <Node>::iterator Iter;
		int i = 0;
		bool k = false;
		try
		{
			for (Iter = rows.begin(); Iter != rows.end(); Iter++) {
				if ((*Iter).id == id) {
					rows.erase(Iter);
					k = true;
					break;
				}
				i++;
			}
			if(k == false){
			throw"ERROR";
			}
		}
		catch (const std::exception&)
		{
			cout << "id not found" << endl;
		}
	}
	void Print() {
		list <Node>::iterator Iter;
		for (Iter = rows.begin(); Iter != rows.end(); Iter++) {
			cout << "------------------------------------" << endl;
			cout << (*Iter).id << " | " << (*Iter).name << " | ";
			(*Iter).data.print();
			cout << endl;
		}
	}
	~List() {
		rows.clear();
	};



};

class Cmas
{
public:
	Cmas() {}
	void Put(string val) {}
	void Del(string name) {}
	void Del(int id) {}
	int Search(string name) {}
	string Take_elem(string name) {}
	void Print() {}
	~Cmas() {}

private:

};
