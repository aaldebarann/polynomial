#pragma once
#include <algorithm>
#include "OrderedTB.h"

void OrderedTB::repack() {
	int i = 0;
	while (i < marker) {
		int p = comparison(DataMas[KeyMas[i]].name, DataMas[KeyMas[i + 1]].name);
		switch (p)
		{
		case 0:
			cout << KeyMas[i] << endl;
			i++;
			continue;
		case 1:

			swap(KeyMas[i], KeyMas[i + 1]);
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

OrderedTB::OrderedTB() {

	marker = -1;
	DataMas = new Node[1];
	KeyMas = new int[1];
}
OrderedTB::~OrderedTB() {
	delete[]DataMas;
	DataMas = nullptr;
	delete[] KeyMas;
	KeyMas = nullptr;
}

void OrderedTB::Insert(Node val) {
	if (marker == -1) {
		marker = 0;
		DataMas[marker] = val;
		KeyMas[marker] = marker;
	}
	else {
		if (Search(val.name) != marker + 1) {
			if ((marker == int(sizeof(DataMas)) / 4) || marker == 0) {
				Node* tmp = new Node[int(sizeof(DataMas)) * 2];
				int* tm = new int[int(sizeof(KeyMas)) * 2];
				for (int i = 0; i <= marker; i++) {
					tmp[i] = DataMas[i];
					tm[i] = KeyMas[i];
				}
				delete[]DataMas;
				DataMas = tmp;
				delete[]KeyMas;
				KeyMas = tm;
			}
			DataMas[++marker] = val;
			KeyMas[marker] = marker;
			repack();
		}
		else {
			DataMas[KeyMas[Search(val.name)]] = val;
		}
	}

}
int OrderedTB::comparison(string one, string tow) {
	const char* s = &one[0];
	const char* f = &tow[0];

	if (strcmp(s, f) == 0) {
		return 0;
	}
	if (strcmp(s, f) > 0) {//str1 áîëüøå, ÷åì str2
		return 1;
	}
	if (strcmp(s, f) < 0) { //str1 ìåíüøå, ÷åì str2
		return -1;
	}
}
void OrderedTB::Del(string name) {
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

int OrderedTB::Search(string name) {
	int l = 0;
	int r = marker;
	int mid;
		while (l <= r) {
			mid = (l + r) / 2;
			if (comparison(DataMas[KeyMas[mid]].name, name) == 0) return mid;
			if (comparison(DataMas[KeyMas[mid]].name, name) == 1) r = mid;
			else l = mid + 1;
		}
		return marker + 1;


}
Polynome OrderedTB::Take_elem(string name) { 
	if (Search(name) == marker + 1) {
		// вызвать окно (такого элемента в таблице нет)
		return Polynome("");
	}
	return Polynome(DataMas[KeyMas[Search(name)]].data); }
void OrderedTB::Print() {
	int i = 0;
	while (i <= marker) {
		cout << "------------------------------------" << endl;
		cout << DataMas[KeyMas[i]].name << " | ";
		DataMas[KeyMas[i]].data.print();
		cout << endl;
		i++;
	}
}