#pragma once
#include "Abstract.h"
class OderedMas : public Abstract
{
private:
	Node* DataMas;
	int* KeyMas;
	int marker;
	void repack();
	int pr(string one, string tow);

public:
	OderedMas();
	void Put(Node val) override;
	void Del(string name) override;
	void Del(int id) override;
	int Search(string name) override;
	int Search(int id) override;
	Polynome Take_elem(string name) override;
	Polynome Take_elem(int id) override;
	void Print() override;
	~OderedMas();
};

