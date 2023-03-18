#pragma once
#include "Table.h"
class OrderedTB : public Table
{
private:
	Node* DataMas;
	int* KeyMas;
	int marker;
	void repack();
	int pr(string one, string tow);

public:
	OrderedTB();
	void Put(Node val) override;
	void Del(string name) override;
	void Del(int id) override;
	int Search(string name) override;
	int Search(int id) override;
	Polynome Take_elem(string name) override;
	Polynome Take_elem(int id) override;
	void Print() override;
	~OrderedTB();
};
=======
#pragma once
#include "Table.h"
class OrderedTB : public Abstract
{
private:
	Node* DataMas;
	int* KeyMas;
	int marker;
	void repack();
	int comparison(string, string);

public:
	OrderedTB();
	void Insert(Node) override;
	void Del(string) override;
	int Search(string) override;
	Polynome Take_elem(string) override;
	void Print() override;
	~OrderedTB();
};
>>>>>>> .merge_file_a06172
