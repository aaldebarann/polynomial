#pragma once
#include <iostream>
#include <string.h>
#include <list>
#include <stdlib.h>
#include"polynomial.h"
using namespace std;

int Take_line(char z, string s) {  // "вырезка " части строки до конкретного символа "z"
	unsigned int i = 0;
	char cur;
	cur = s[i];
	while (cur != z || i != sizeof(s)) {
		cur = s[i++];
	}
	return i;
}

const char* Tochar(string s) { // переводит строку в const char *
	char* c[sizeof(s)];
	int i = -1;
	while (i < (sizeof(s) - 1)) {
		c[++i] = &s[i];
	}
	const char* b = *c;
	return b;
}

string ToString(char* c) { // переводит char * в строку
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

struct Node // структура которая отвечает за строки таблицы
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
class Abstract //абстрактный класс таблицы, от которого наследуются остальные таблицы
{
	virtual void Put(Node val) = 0; // добавить новый элемент в таблицу
	virtual void Del(string name) = 0; // удалить элемент по имени
	virtual void Del(int id) = 0; // удалить элемент по id
	virtual int Search(string name) = 0; // найти элемент по имени так же можно использовать что бы получить id элемента типо take только для id 
	virtual int Search(int id) = 0; // найти элемент по id
	virtual Polynome Take_elem(string name) = 0; // получить элемент по имени
	virtual Polynome Take_elem(int id) = 0; // получить элемент по id
	virtual void Print() = 0;// печать таблицы 
};

