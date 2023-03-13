#pragma once
#include <algorithm>
#include "OderedMas.h"






void OderedMas::repack() {
	int i = 0;
	while (i < marker) {
		int p = pr(DataMas[KeyMas[i]].name, DataMas[KeyMas[i+1]].name);
		switch (p)
		{
		case 0:
			cout << KeyMas[i] << endl;
			i++;
			continue;
		case 1:

			swap(KeyMas[i], KeyMas[i+1]);
			cout << KeyMas[i] << endl;
			i++;
			continue;
		case -1:
			cout << KeyMas[i] << endl;
			i++;
			continue;
		default:
			continue;
		}
	}

}

OderedMas::OderedMas() {

	marker = -1;
	DataMas = new Node[1];
	KeyMas = new int[1];
}
OderedMas ::~OderedMas() {
	delete[]DataMas;
	DataMas = nullptr;
	delete[] KeyMas;
	KeyMas = nullptr;
}

void OderedMas::Put(Node val) {
	if (marker == -1) {
		marker = 0;
		DataMas[marker] = val;
		KeyMas[marker] = marker;
	}
	else {
		if ((marker == int(sizeof(DataMas)) / 4) || marker == 0) {
			Node* tmp = new Node[int(sizeof(DataMas)) * 2];
			int* tm = new int[int(sizeof(KeyMas)) * 2];
			for (int i = 0; i <= marker; i++) {
				tmp[i] = DataMas[i];
				tm[i] = KeyMas[i];
			}
			delete[]DataMas;
			DataMas	= tmp;
			delete[]KeyMas;
			KeyMas = tm;
		}
		DataMas[++marker] = val;
		KeyMas[marker] = marker;
		repack();
	}

}
int OderedMas :: pr(string one, string tow) {
	const char* s = &one[0];
	const char* f = &tow[0];

	if (strcmp(s, f) == 0) {
		return 0;
	}
	if (strcmp(s, f) > 0) {//str1 ������, ��� str2
		return 1;
	}
	if (strcmp(s, f) < 0) { //str1 ������, ��� str2
		return -1;
	}
}
void OderedMas::Del(string name) {
	int i = Search(name);
	if (i == marker) {
		marker--;
	}
	else {
		while (i < marker) {
			DataMas[KeyMas[i]] = DataMas[KeyMas[i + 1]];
			KeyMas[i] = KeyMas[i + 1];
			i++;
		}
		marker--;
	}

}

	
void OderedMas::Del(int id) {}

int OderedMas::Search(string name) { 
	int l = 0;
	int r = marker;
	int mid;
	try
	{
		while (l <= r) {
			mid = (l + r) / 2;
			if (pr(DataMas[KeyMas[mid]].name, name) == 0) return mid;
			if (pr(DataMas[KeyMas[mid]].name, name) == 1) r = mid;
			else l = mid + 1;
		}
		throw invalid_argument("ERROR");
	}
	catch (const std::exception&)
	{
		cout << "Sorry elem not in TB" << endl;
		return -1;
	}
	
	
}
int OderedMas::Search(int id) { return 0; }
Polynome OderedMas::Take_elem(string name) { return Polynome(DataMas[KeyMas[Search(name)]].data); }
Polynome OderedMas::Take_elem(int id) { return Polynome("n"); }
void OderedMas::Print() {
	int i = 0;
	cout << "Line mas table" << endl;
	int j = 0;
	while (j <= marker) {
		cout << KeyMas[j++] << endl;
	}
	while (i <= marker) {
		cout << "------------------------------------" << endl;
		
		cout << DataMas[KeyMas[i]].id << " | " << DataMas[KeyMas[i]].name << " | ";
		DataMas[KeyMas[i]].data.print();
		cout << endl;
		i++;
	}
}