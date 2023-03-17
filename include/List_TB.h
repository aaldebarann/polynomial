#include "Table.h"
class List_TB : public Abstract
{
private:
	list <Node> rows;
public:
	List_TB();
	void Insert(Node) override;
	void Del(string) override;
	int Search(string) override;
	Polynome Take_elem(string) override;
	void Print() override;
	~List_TB();
};
