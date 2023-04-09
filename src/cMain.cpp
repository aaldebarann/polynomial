#include "cMain.h"
#include "List_TB.h"
#include"calculator.h"
#include"polynomial.h"
#include"monome.h"
#include "OrderedTB.h"
#include "UnorderedTB.h"
#include "Table.h"
wxBEGIN_EVENT_TABLE(cMain, wxFrame)
EVT_BUTTON(10001, OnButtonClicked)
wxEND_EVENT_TABLE()

unsigned int flag = 1;
List_TB* tb = new List_TB();
Calculator* clc = new Calculator();



cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Lab work about poli!", wxPoint(40, 40), wxSize(1080, 750)) {
	btn1 = new wxButton(this, 10001, "Send a message", wxPoint(450, 200), wxSize(150, 50));
	txt1 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(450, 300), wxSize(500, 30));
	list1 = new wxListBox(this, wxID_ANY, wxPoint(40, 40), wxSize(300, 600));
	help = new wxTextCtrl(this, wxID_ANY, "������� ����� ���������\n �������� ������� �������� ��- � ��������� ����������.�������� x*y*z, �����, � x*y*z*d ������ \n � �������� ���������� ����� ������������ ������ ������� x,y,z \n ������� ������� �� �������.������ ����� ����� ��� K*x^a1*y^a2*z^a3, ��� K - ��������� ������������ ����� a1,a2,a3-����������� ��� ������� �����\n��� ����� ������ ����� �������� ������� � ��������� �������, � ����� ��������� �\n ���������� ������ �������� � ������� ����� ������� x->y->z � ����� �����.��������,y*x -������������ ����, ������ ��� x ������ ������ �� y.���������� ����� x*y\n ����� �������� ����� ���������� ��������.\n ����������� ����������� ����������� ������  ��������� *.��������, x*y ���������, � xy- ����������� \n ������� ����� �������������� ��������� � ���������� :\n ���������� �������� :\n ��������(+), ���������(-), ���������(*) ��������� � ��������\n ���������� ����������� ����� �� ���������(sqrt(...)) \n 	������ �������� �������� � ����� x = 1, y = 2, z = 3 : AT(f, 1, 2, 3) \n ������ ������� ����������� �������� �� ���������� x(/ y / z) : D(f, x)\n ������ ������������� �������� �� ���������� x(/ y / z) : I(f, x)\n", wxPoint(450, 340), wxSize(500, 300),wxTE_MULTILINE);
	wxMenu* menuFile = new wxMenu;
	menuFile->Append(1, "&List",
		"Help string shown in status bar for this menu item");
	menuFile->AppendSeparator();
	menuFile->Append(2, "&Un_tb");
	menuFile->AppendSeparator();
	menuFile->Append(3, "&Ord_tb");
	menuFile->AppendSeparator();
	menuFile->Append(4, "&Tree");


	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");

	SetMenuBar(menuBar);


	Bind(wxEVT_MENU, &cMain::List_tb, this, 1);
	Bind(wxEVT_MENU, &cMain::Un_tb, this, 2);
	Bind(wxEVT_MENU, &cMain::Ord_tb, this, 3);
	Bind(wxEVT_MENU, &cMain::Tree, this, 4);
}

cMain::~cMain() {
	
}
string str;
void cMain::OnButtonClicked(wxCommandEvent& evt) {
	str = txt1->GetValue().c_str();
	txt1->Clear();
	txt1->AppendText(clc->interpret(str));
	list1->Clear();
	Table* table = clc->activeTable();
	str =table->Print_();
	char h;
	string s = "";
	string::iterator i = str.begin();
	while (i != str.end()) {
		h = *i;
		if (h == '|') {
			list1->AppendString(s);
			s = "";
			i++;
		}
		else {
			s += h;
			i++;
		}

	}
	evt.Skip();

}


void cMain :: List_tb(wxCommandEvent& event) {
	flag = 1;
	list1->Clear();
	clc.setActive(flag);
	Table* table = clc->activeTable();
	str = table->Print_();
	char h;
	string s = "";
	string::iterator i = str.begin();
	while (i != str.end()) {
		h = *i;
		if (h == '|') {
			list1->AppendString(s);
			s = "";
			i++;
		}
		else {
			s += h;
			i++;
		}

	}
}
void cMain ::Un_tb(wxCommandEvent& event) {
	flag = 0;
	list1->Clear();
	clc.setActive(flag);
	Table* table = clc->activeTable();
	str = table->Print_();
	char h;
	string s = "";
	string::iterator i = str.begin();
	while (i != str.end()) {
		h = *i;
		if (h == '|') {
			list1->AppendString(s);
			s = "";
			i++;
		}
		else {
			s += h;
			i++;
		}

	}

}
void cMain::Ord_tb(wxCommandEvent& event) {
	flag = 2;
	list1->Clear();
	clc.setActive(flag);
	Table* table = clc->activeTable();
	str = table->Print_();
	char h;
	string s = "";
	string::iterator i = str.begin();
	while (i != str.end()) {
		h = *i;
		if (h == '|') {
			list1->AppendString(s);
			s = "";
			i++;
		}
		else {
			s += h;
			i++;
		}

	}
}
void cMain::Tree(wxCommandEvent& event) {
	flag = 3;
	list1->Clear();
	clc.setActive(flag);
	Table* table = clc->activeTable();
	str = table->Print_();
	char h;
	string s = "";
	string::iterator i = str.begin();
	while (i != str.end()) {
		h = *i;
		if (h == '|') {
			list1->AppendString(s);
			s = "";
			i++;
		}
		else {
			s += h;
			i++;
		}

	}
}