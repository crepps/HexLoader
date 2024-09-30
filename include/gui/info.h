#pragma once

namespace HexLoader {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for info
	/// </summary>
	public ref class info : public System::Windows::Forms::Form
	{
	public:
		info(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~info()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label_title;
	protected:

	protected:
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Label^ label_version;
	private: System::Windows::Forms::Label^ label_copyright;
	private: System::Windows::Forms::LinkLabel^ link_license;



	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label_desc1;
	private: System::Windows::Forms::Label^ label_coffee;
	private: System::Windows::Forms::LinkLabel^ link_coffee;
	private: System::Windows::Forms::Label^ label_header1;
	private: System::Windows::Forms::Label^ label_header2;

	private: System::Windows::Forms::Label^ label_desc2;
	private: System::Windows::Forms::Label^ label_desc3;

















	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(info::typeid));
			this->label_title = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label_version = (gcnew System::Windows::Forms::Label());
			this->label_copyright = (gcnew System::Windows::Forms::Label());
			this->link_license = (gcnew System::Windows::Forms::LinkLabel());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label_desc1 = (gcnew System::Windows::Forms::Label());
			this->label_coffee = (gcnew System::Windows::Forms::Label());
			this->link_coffee = (gcnew System::Windows::Forms::LinkLabel());
			this->label_header1 = (gcnew System::Windows::Forms::Label());
			this->label_header2 = (gcnew System::Windows::Forms::Label());
			this->label_desc2 = (gcnew System::Windows::Forms::Label());
			this->label_desc3 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label_title
			// 
			this->label_title->AutoSize = true;
			this->label_title->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label_title->Font = (gcnew System::Drawing::Font(L"Lucida Console", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_title->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->label_title->Location = System::Drawing::Point(72, 88);
			this->label_title->Name = L"label_title";
			this->label_title->Size = System::Drawing::Size(156, 27);
			this->label_title->TabIndex = 0;
			this->label_title->Text = L"HexLoader";
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(20)), static_cast<System::Int32>(static_cast<System::Byte>(20)),
				static_cast<System::Int32>(static_cast<System::Byte>(20)));
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Location = System::Drawing::Point(273, 39);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(130, 130);
			this->button1->TabIndex = 1;
			this->button1->UseVisualStyleBackColor = false;
			// 
			// label_version
			// 
			this->label_version->AutoSize = true;
			this->label_version->Font = (gcnew System::Drawing::Font(L"Lucida Sans", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_version->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->label_version->Location = System::Drawing::Point(489, 70);
			this->label_version->Name = L"label_version";
			this->label_version->Size = System::Drawing::Size(90, 15);
			this->label_version->TabIndex = 2;
			this->label_version->Text = L"v1.0.0-beta.3";
			// 
			// label_copyright
			// 
			this->label_copyright->AutoSize = true;
			this->label_copyright->Font = (gcnew System::Drawing::Font(L"Lucida Sans", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_copyright->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->label_copyright->Location = System::Drawing::Point(430, 100);
			this->label_copyright->Name = L"label_copyright";
			this->label_copyright->Size = System::Drawing::Size(211, 15);
			this->label_copyright->TabIndex = 3;
			this->label_copyright->Text = L"Copyright (c) 2024 Kevin Crepps";
			// 
			// link_license
			// 
			this->link_license->AutoSize = true;
			this->link_license->Font = (gcnew System::Drawing::Font(L"Lucida Sans", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->link_license->LinkColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->link_license->Location = System::Drawing::Point(510, 129);
			this->link_license->Name = L"link_license";
			this->link_license->Size = System::Drawing::Size(50, 15);
			this->link_license->TabIndex = 4;
			this->link_license->TabStop = true;
			this->link_license->Text = L"License";
			// 
			// label4
			// 
			this->label4->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(30)),
				static_cast<System::Int32>(static_cast<System::Byte>(30)));
			this->label4->Location = System::Drawing::Point(33, 189);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(632, 17);
			this->label4->TabIndex = 5;
			this->label4->Text = L"_________________________________________________________________________________"
				L"______________________________";
			// 
			// label_desc1
			// 
			this->label_desc1->AutoSize = true;
			this->label_desc1->Font = (gcnew System::Drawing::Font(L"Lucida Sans", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_desc1->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->label_desc1->Location = System::Drawing::Point(80, 231);
			this->label_desc1->Name = L"label_desc1";
			this->label_desc1->Size = System::Drawing::Size(477, 15);
			this->label_desc1->TabIndex = 6;
			this->label_desc1->Text = L"HexLoader is a utility for packing library files into a standalone executable.";
			// 
			// label_coffee
			// 
			this->label_coffee->AutoSize = true;
			this->label_coffee->Font = (gcnew System::Drawing::Font(L"Lucida Sans", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_coffee->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->label_coffee->Location = System::Drawing::Point(244, 592);
			this->label_coffee->Name = L"label_coffee";
			this->label_coffee->Size = System::Drawing::Size(90, 15);
			this->label_coffee->TabIndex = 11;
			this->label_coffee->Text = L"Like the app\?";
			// 
			// link_coffee
			// 
			this->link_coffee->AutoSize = true;
			this->link_coffee->Font = (gcnew System::Drawing::Font(L"Lucida Sans", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->link_coffee->LinkColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->link_coffee->Location = System::Drawing::Point(360, 592);
			this->link_coffee->Name = L"link_coffee";
			this->link_coffee->Size = System::Drawing::Size(102, 15);
			this->link_coffee->TabIndex = 12;
			this->link_coffee->TabStop = true;
			this->link_coffee->Text = L"Buy me a coffee";
			// 
			// label_header1
			// 
			this->label_header1->AutoSize = true;
			this->label_header1->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label_header1->Font = (gcnew System::Drawing::Font(L"Lucida Console", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_header1->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->label_header1->Location = System::Drawing::Point(79, 285);
			this->label_header1->Name = L"label_header1";
			this->label_header1->Size = System::Drawing::Size(88, 21);
			this->label_header1->TabIndex = 7;
			this->label_header1->Text = L"Loader";
			// 
			// label_header2
			// 
			this->label_header2->AutoSize = true;
			this->label_header2->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label_header2->Font = (gcnew System::Drawing::Font(L"Lucida Console", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_header2->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->label_header2->Location = System::Drawing::Point(78, 434);
			this->label_header2->Name = L"label_header2";
			this->label_header2->Size = System::Drawing::Size(127, 21);
			this->label_header2->TabIndex = 8;
			this->label_header2->Text = L"Installer";
			// 
			// label_desc2
			// 
			this->label_desc2->Font = (gcnew System::Drawing::Font(L"Lucida Sans", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_desc2->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->label_desc2->Location = System::Drawing::Point(80, 321);
			this->label_desc2->Name = L"label_desc2";
			this->label_desc2->Size = System::Drawing::Size(544, 67);
			this->label_desc2->TabIndex = 9;
			this->label_desc2->Text = resources->GetString(L"label_desc2.Text");
			// 
			// label_desc3
			// 
			this->label_desc3->Font = (gcnew System::Drawing::Font(L"Lucida Sans", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_desc3->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->label_desc3->Location = System::Drawing::Point(80, 468);
			this->label_desc3->Name = L"label_desc3";
			this->label_desc3->Size = System::Drawing::Size(550, 84);
			this->label_desc3->TabIndex = 10;
			this->label_desc3->Text = resources->GetString(L"label_desc3.Text");
			// 
			// info
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->ClientSize = System::Drawing::Size(700, 625);
			this->ControlBox = false;
			this->Controls->Add(this->link_coffee);
			this->Controls->Add(this->label_coffee);
			this->Controls->Add(this->label_desc3);
			this->Controls->Add(this->label_desc2);
			this->Controls->Add(this->label_header2);
			this->Controls->Add(this->label_header1);
			this->Controls->Add(this->label_desc1);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->link_license);
			this->Controls->Add(this->label_copyright);
			this->Controls->Add(this->label_version);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label_title);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"info";
			this->Opacity = 0.95;
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	};
}
