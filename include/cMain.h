#pragma once
#include"wx/wx.h"
#include<string>
class cMain : public wxFrame
{

public:
	cMain();
	~cMain();

public:
	wxButton* btn1 = nullptr;
	wxTextCtrl* txt1 = nullptr;
	wxListBox* list1 = nullptr;
	wxMenu* menuFile = nullptr;
	wxTextCtrl* help = nullptr;
 	void List_tb(wxCommandEvent& event);
	void Un_tb(wxCommandEvent& event);
	void Ord_tb(wxCommandEvent& event);
	void Tree(wxCommandEvent& event);
	void OnButtonClicked(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();

}; 

