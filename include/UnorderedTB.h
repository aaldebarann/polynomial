#include "Table.h"
class UnorderedTB : public Table
{
private:
	Node* row;
	int marker;
public:
	UnorderedTB();
	void Put(Node val) override;
	void Del(string name) override;
	void Del(int id) override;
	int Search(string name) override;
	int Search(int id) override;
	Polynome Take_elem(string name) override;
	Polynome Take_elem(int id) override;
	void Print() override;
	~UnorderedTB();

};