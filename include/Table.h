<<<<<<< .merge_file_a13464
#pragma once
#include <iostream>
#include <string.h>
#include <list>
#include <stdlib.h>
#include"polynomial.h"
using namespace std;


struct Node // ��������� ������� �������� �� ������ �������
{
	unsigned int id;
	string name;
	Polynome data;
	Node() {
		id = rand();
		name = " ";
	}
};
class Table //����������� ����� �������, �� �������� ����������� ��������� �������
{
	virtual void Put(Node val) = 0; // �������� ����� ������� � �������
	virtual void Del(string name) = 0; // ������� ������� �� �����
	virtual void Del(int id) = 0; // ������� ������� �� id
	virtual int Search(string name) = 0; // ����� ������� �� ����� ��� �� ����� ������������ ��� �� �������� id �������� ���� take ������ ��� id 
	virtual int Search(int id) = 0; // ����� ������� �� id
	virtual Polynome Take_elem(string name) = 0; // �������� ������� �� �����
	virtual Polynome Take_elem(int id) = 0; // �������� ������� �� id
	virtual void Print() = 0;// ������ ������� 
};
=======
#pragma once
#include <iostream>
#include <string.h>
#include <list>
#include <stdlib.h>
#include"polynomial.h"
using namespace std;


struct Node // ��������� ������� �������� �� ������ �������
{
	string name;
	Polynome data;
	Node() {
		name = " ";
		data = Polynome("0");
	}
};
class Abstract //����������� ����� �������, �� �������� ����������� ��������� �������
{
	virtual void Insert(Node val) = 0; // �������� ����� ������� � �������
	virtual void Del(string name) = 0; // ������� ������� �� �����
	virtual int Search(string name) = 0; // ����� ������� �� ����� ��� �� ����� ������������ ��� �� �������� id �������� ���� take ������ ��� id 
	virtual Polynome Take_elem(string name) = 0; // �������� ������� �� �����
	virtual void Print() = 0;// ������ ������� 
};
>>>>>>> .merge_file_a14612
