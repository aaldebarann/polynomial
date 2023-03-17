#include "Table.h"
class UnorderedTB : public Abstract
{
private:
	Node* row;
	int marker;
public:
	UnorderedTB();
	void Insert(Node) override;
	void Del(string) override;
	int Search(string) override;
	Polynome Take_elem(string) override;
	void Print() override;
	~UnorderedTB();

};