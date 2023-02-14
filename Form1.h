#pragma once

namespace CppCLRWinformsProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::GroupBox^ groupBox1;
	protected:
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
	private: System::Windows::Forms::TextBox^ pl2_3;

	private: System::Windows::Forms::TextBox^ pl1_3;
	private: System::Windows::Forms::TextBox^ pl2_2;

	private: System::Windows::Forms::TextBox^ pl1_2;
	private: System::Windows::Forms::TextBox^ pl2_1;

	private: System::Windows::Forms::TextBox^ pl1_1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ But_input;
	private: System::Windows::Forms::Button^ div;

	private: System::Windows::Forms::Button^ mult;

	private: System::Windows::Forms::Button^ def;

	private: System::Windows::Forms::Button^ sum;
	private: System::Windows::Forms::TextBox^ res;


























	protected:

	protected:


	protected:

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>

#pragma endregion

	private: System::Void InitializeComponent() {
		this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
		this->res = (gcnew System::Windows::Forms::TextBox());
		this->div = (gcnew System::Windows::Forms::Button());
		this->mult = (gcnew System::Windows::Forms::Button());
		this->def = (gcnew System::Windows::Forms::Button());
		this->sum = (gcnew System::Windows::Forms::Button());
		this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
		this->pl2_3 = (gcnew System::Windows::Forms::TextBox());
		this->pl1_3 = (gcnew System::Windows::Forms::TextBox());
		this->pl2_2 = (gcnew System::Windows::Forms::TextBox());
		this->pl1_2 = (gcnew System::Windows::Forms::TextBox());
		this->pl2_1 = (gcnew System::Windows::Forms::TextBox());
		this->pl1_1 = (gcnew System::Windows::Forms::TextBox());
		this->label1 = (gcnew System::Windows::Forms::Label());
		this->label2 = (gcnew System::Windows::Forms::Label());
		this->But_input = (gcnew System::Windows::Forms::Button());
		this->groupBox1->SuspendLayout();
		this->tableLayoutPanel1->SuspendLayout();
		this->SuspendLayout();
		// 
		// groupBox1
		// 
		this->groupBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
			| System::Windows::Forms::AnchorStyles::Left)
			| System::Windows::Forms::AnchorStyles::Right));
		this->groupBox1->Controls->Add(this->res);
		this->groupBox1->Controls->Add(this->div);
		this->groupBox1->Controls->Add(this->mult);
		this->groupBox1->Controls->Add(this->def);
		this->groupBox1->Controls->Add(this->sum);
		this->groupBox1->Controls->Add(this->tableLayoutPanel1);
		this->groupBox1->Controls->Add(this->But_input);
		this->groupBox1->Location = System::Drawing::Point(195, 176);
		this->groupBox1->Name = L"groupBox1";
		this->groupBox1->Size = System::Drawing::Size(1142, 640);
		this->groupBox1->TabIndex = 6;
		this->groupBox1->TabStop = false;
		// 
		// res
		// 
		this->res->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
			System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
		this->res->Location = System::Drawing::Point(449, 467);
		this->res->Name = L"res";
		this->res->Size = System::Drawing::Size(270, 30);
		this->res->TabIndex = 7;
		this->res->Visible = false;
		this->res->TextChanged += gcnew System::EventHandler(this, &Form1::textBox1_TextChanged_2);
		// 
		// div
		// 
		this->div->FlatAppearance->BorderColor = System::Drawing::Color::Blue;
		this->div->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)),
			static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
		this->div->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->div->Location = System::Drawing::Point(862, 267);
		this->div->Name = L"div";
		this->div->Size = System::Drawing::Size(64, 58);
		this->div->TabIndex = 5;
		this->div->Text = L"/";
		this->div->UseVisualStyleBackColor = true;
		this->div->Click += gcnew System::EventHandler(this, &Form1::button4_Click);
		// 
		// mult
		// 
		this->mult->FlatAppearance->BorderColor = System::Drawing::Color::Blue;
		this->mult->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)),
			static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
		this->mult->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->mult->Location = System::Drawing::Point(655, 267);
		this->mult->Name = L"mult";
		this->mult->Size = System::Drawing::Size(64, 58);
		this->mult->TabIndex = 4;
		this->mult->Text = L"*";
		this->mult->UseVisualStyleBackColor = true;
		this->mult->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
		// 
		// def
		// 
		this->def->FlatAppearance->BorderColor = System::Drawing::Color::Blue;
		this->def->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)),
			static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
		this->def->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->def->Location = System::Drawing::Point(449, 267);
		this->def->Name = L"def";
		this->def->Size = System::Drawing::Size(64, 58);
		this->def->TabIndex = 3;
		this->def->Text = L"-";
		this->def->UseVisualStyleBackColor = true;
		this->def->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
		// 
		// sum
		// 
		this->sum->FlatAppearance->BorderColor = System::Drawing::Color::Blue;
		this->sum->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)),
			static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
		this->sum->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->sum->Location = System::Drawing::Point(230, 267);
		this->sum->Name = L"sum";
		this->sum->Size = System::Drawing::Size(64, 58);
		this->sum->TabIndex = 2;
		this->sum->Text = L"+";
		this->sum->UseVisualStyleBackColor = true;
		this->sum->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
		// 
		// tableLayoutPanel1
		// 
		this->tableLayoutPanel1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
		this->tableLayoutPanel1->ColumnCount = 4;
		this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
			100)));
		this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
			200)));
		this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
			200)));
		this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
			200)));
		this->tableLayoutPanel1->Controls->Add(this->pl2_3, 3, 1);
		this->tableLayoutPanel1->Controls->Add(this->pl1_3, 3, 0);
		this->tableLayoutPanel1->Controls->Add(this->pl2_2, 2, 1);
		this->tableLayoutPanel1->Controls->Add(this->pl1_2, 2, 0);
		this->tableLayoutPanel1->Controls->Add(this->pl2_1, 1, 1);
		this->tableLayoutPanel1->Controls->Add(this->pl1_1, 1, 0);
		this->tableLayoutPanel1->Controls->Add(this->label1, 0, 0);
		this->tableLayoutPanel1->Controls->Add(this->label2, 0, 1);
		this->tableLayoutPanel1->Location = System::Drawing::Point(3, 16);
		this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
		this->tableLayoutPanel1->RowCount = 2;
		this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
		this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
		this->tableLayoutPanel1->Size = System::Drawing::Size(1136, 147);
		this->tableLayoutPanel1->TabIndex = 1;
		this->tableLayoutPanel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::tableLayoutPanel1_Paint_1);
		// 
		// pl2_3
		// 
		this->pl2_3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->pl2_3->Location = System::Drawing::Point(939, 76);
		this->pl2_3->Name = L"pl2_3";
		this->pl2_3->Size = System::Drawing::Size(130, 30);
		this->pl2_3->TabIndex = 6;
		this->pl2_3->TextChanged += gcnew System::EventHandler(this, &Form1::pl2_3_TextChanged);
		// 
		// pl1_3
		// 
		this->pl1_3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->pl1_3->Location = System::Drawing::Point(939, 3);
		this->pl1_3->Name = L"pl1_3";
		this->pl1_3->Size = System::Drawing::Size(130, 30);
		this->pl1_3->TabIndex = 3;
		this->pl1_3->TextChanged += gcnew System::EventHandler(this, &Form1::pl1_3_TextChanged);
		// 
		// pl2_2
		// 
		this->pl2_2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->pl2_2->Location = System::Drawing::Point(739, 76);
		this->pl2_2->Name = L"pl2_2";
		this->pl2_2->Size = System::Drawing::Size(130, 30);
		this->pl2_2->TabIndex = 5;
		this->pl2_2->TextChanged += gcnew System::EventHandler(this, &Form1::pl2_2_TextChanged);
		// 
		// pl1_2
		// 
		this->pl1_2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->pl1_2->Location = System::Drawing::Point(739, 3);
		this->pl1_2->Name = L"pl1_2";
		this->pl1_2->Size = System::Drawing::Size(130, 30);
		this->pl1_2->TabIndex = 2;
		this->pl1_2->TextChanged += gcnew System::EventHandler(this, &Form1::pl1_2_TextChanged);
		// 
		// pl2_1
		// 
		this->pl2_1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->pl2_1->Location = System::Drawing::Point(539, 76);
		this->pl2_1->Name = L"pl2_1";
		this->pl2_1->Size = System::Drawing::Size(130, 30);
		this->pl2_1->TabIndex = 4;
		this->pl2_1->TextChanged += gcnew System::EventHandler(this, &Form1::textBox1_TextChanged_1);
		// 
		// pl1_1
		// 
		this->pl1_1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->pl1_1->Location = System::Drawing::Point(539, 3);
		this->pl1_1->Name = L"pl1_1";
		this->pl1_1->Size = System::Drawing::Size(130, 30);
		this->pl1_1->TabIndex = 1;
		this->pl1_1->TextChanged += gcnew System::EventHandler(this, &Form1::pl1_1_TextChanged);
		// 
		// label1
		// 
		this->label1->AutoSize = true;
		this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->label1->Location = System::Drawing::Point(3, 0);
		this->label1->Name = L"label1";
		this->label1->Size = System::Drawing::Size(334, 31);
		this->label1->TabIndex = 3;
		this->label1->Text = L"Ââåëèòå ïåðâûé ïîëèíîì";
		this->label1->Click += gcnew System::EventHandler(this, &Form1::label1_Click_1);
		// 
		// label2
		// 
		this->label2->AutoSize = true;
		this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->label2->Location = System::Drawing::Point(3, 73);
		this->label2->Name = L"label2";
		this->label2->Size = System::Drawing::Size(328, 31);
		this->label2->TabIndex = 4;
		this->label2->Text = L"Ââåäèòå âòîðîé ïîëèíîì";
		this->label2->Click += gcnew System::EventHandler(this, &Form1::label2_Click);
		// 
		// But_input
		// 
		this->But_input->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
		this->But_input->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)),
			static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
		this->But_input->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
			static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
		this->But_input->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
			static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
		this->But_input->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->But_input->Location = System::Drawing::Point(449, 382);
		this->But_input->MaximumSize = System::Drawing::Size(270, 43);
		this->But_input->Name = L"But_input";
		this->But_input->Padding = System::Windows::Forms::Padding(1);
		this->But_input->Size = System::Drawing::Size(270, 43);
		this->But_input->TabIndex = 0;
		this->But_input->Text = L"Ïîñ÷èòàòü";
		this->But_input->UseVisualStyleBackColor = true;
		this->But_input->Click += gcnew System::EventHandler(this, &Form1::But_input_Click);
		// 
		// Form1
		// 
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Inherit;
		this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
		this->ClientSize = System::Drawing::Size(1568, 816);
		this->Controls->Add(this->groupBox1);
		this->Name = L"Form1";
		this->ShowIcon = false;
		this->Text = L"Ëàáîðàòîðíàÿ ðàáîòà";
		this->groupBox1->ResumeLayout(false);
		this->groupBox1->PerformLayout();
		this->tableLayoutPanel1->ResumeLayout(false);
		this->tableLayoutPanel1->PerformLayout();
		this->ResumeLayout(false);

	}
	int val;
private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void tableLayoutPanel1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
}
private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void But_input_Click(System::Object^ sender, System::EventArgs^ e) {
	double a1, a2, b1, b2, c1, c2;
	a1 = System::Convert::ToDouble(pl1_1->Text);
	a2 = System::Convert::ToDouble(pl2_1->Text);
	b1 = System::Convert::ToDouble(pl1_2->Text);
	b2 = System::Convert::ToDouble(pl2_2->Text);
	c1 = System::Convert::ToDouble(pl1_3->Text);
	c2 = System::Convert::ToDouble(pl2_3->Text);
	switch (val)
	{
		case 1:
			res->Text ="opr '+' "+ System::Convert::ToString((a1 + a2)) + " | " + System::Convert::ToString((b1 + b2)) + " | " + System::Convert::ToString((c1 + c2));
			this->res->Visible = true;
			break;
		case 2:
			res->Text ="opr '-' "+ System::Convert::ToString((a1 - a2)) + " | " + System::Convert::ToString((b1 - b2)) + " | " + System::Convert::ToString((c1 - c2));
			this->res->Visible = true;
			break;
		case 3:
			res->Text ="opr '*' "+ System::Convert::ToString((a1 * a2)) + " | " + System::Convert::ToString((b1 * b2)) + " | " + System::Convert::ToString((c1 * c2));
			this->res->Visible = true;
			break;
		case 4:
			res->Text ="opr '/' " + System::Convert::ToString(((a1 / a2) * 10) / 10) + " | " + System::Convert::ToString(((b1 / b2) * 10) / 10) + " | " + System::Convert::ToString(((c1 / c2) * 10) / 10);
			this->res->Visible = true;
			break;
	default:
		break;
	}
	
}
private: System::Void label1_Click_1(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void tableLayoutPanel1_Paint_1(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
}
private: System::Void textBox1_TextChanged_1(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	val = 2;
}
private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
	val = 3;
}
private: System::Void pl1_1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void pl1_2_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void pl1_3_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void pl2_2_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void pl2_3_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	val = 1;
}
private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
	val = 4;
}
private: System::Void textBox1_TextChanged_2(System::Object^ sender, System::EventArgs^ e) {
	
}
};
}