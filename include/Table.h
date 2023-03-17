#pragma once
#include <iostream>
#include <string.h>
#include <list>
#include <stdlib.h>
#include"polynomial.h"
using namespace std;


struct Node // структура которая отвечает за строки таблицы
{
	string name;
	Polynome data;
	Node() {
		name = " ";
		data = Polynome("0");
	}
};
class Abstract //абстрактный класс таблицы, от которого наследуются остальные таблицы
{
	virtual void Insert(Node val) = 0; // добавить новый элемент в таблицу
	virtual void Del(string name) = 0; // удалить элемент по имени
	virtual int Search(string name) = 0; // найти элемент по имени так же можно использовать что бы получить id элемента типо take только для id 
	virtual Polynome Take_elem(string name) = 0; // получить элемент по имени
	virtual void Print() = 0;// печать таблицы 
};
