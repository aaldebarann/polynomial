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
