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
