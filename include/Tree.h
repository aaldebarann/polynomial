#pragma once
#include "Table.h"
struct Obj
{
	Node DataCase;
	int height; // ��� �� �������
	Obj* right;
	Obj* left;
};
typedef struct Obj* nodeptr;

class Tree
{
private:
	int bsheight(nodeptr); // ������(�������) �� ����������� ������� (�����) � ������
	nodeptr srl(nodeptr&);
	nodeptr drl(nodeptr&);// ����� �������
	nodeptr srr(nodeptr&);
	nodeptr drr(nodeptr&); //������ �������		   
	int max(int, int); // ������������ �� ���� ���� 
	int comparison(string, string); // ��������� ����
	Polynome deletemin(nodeptr&);
	nodeptr nodecopy(nodeptr&);
	void copy(nodeptr&, nodeptr&);
public:
	Polynome find(string, nodeptr&);
	void insert(Node, nodeptr&);
	void del(string, nodeptr&);
	void clear(nodeptr&); // ������� ������
	// ��� �������� ������� 
	void preorder(nodeptr);
	void inorder(nodeptr);
	void postorder(nodeptr);

	

};

