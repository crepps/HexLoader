#pragma once
#include <iostream>
#include <string>
#include <vector>

// Text animation-related
#define NUM_BUTTONS 3
#define NUM_HEADER_FRAMES 16
#define HEADER_TICK_RATE 9

// Mouse-selectable window regions
#define TITLE_BAR_HEIGHT 30
#define TITLE_BAR_WIDTH 751

#define BSB_AREA_L 329	// BUTTON_SELECT_BIN left, right, top, bottom
#define BSB_AREA_R 352
#define BSB_AREA_T 121
#define BSB_AREA_B 136

#define BSL_AREA_L 333	// BUTTON_SELECT_LIB
#define BSL_AREA_R 349
#define BSL_AREA_T 172
#define BSL_AREA_B 188

#define BB_AREA_L 657	// BUTTON_BUILD
#define BB_AREA_R 733
#define BB_AREA_T 270
#define BB_AREA_B 294

void ConvertString(System::String^, std::string&);

enum AREA
{
	BUTTON_SELECT_BIN,
	BUTTON_SELECT_LIB,
	BUTTON_BUILD
};

struct vec2
{
	int x, y;

	vec2(int a_x, int a_y) noexcept
		:x(a_x), y(a_y) {}
};

const std::vector<std::string> headerFrames =
{
	"---           ---",
	"--_           _--",
	"-_             _-",
	"_               _",
	"                 ",
	"                 ",
	"                 ",
	"                 ",
	"                 ",
	"  _           _  ",
	" _-           -_ ",
	"_--           --_",
	"---           ---",
	"---           ---",
	"---           ---",
	"---           ---"
};

namespace HexLoader {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for gui
	/// </summary>
	public ref class gui : public System::Windows::Forms::Form
	{
	private:
		bool mouseDown;
		Point cursorDownPos,
			cursorDelta;
		const char* binPath;
		System::Collections::Generic::List<String^> libPaths;
		System::Windows::Forms::Button^ buttonPtr;

	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ button_build;
	private: System::Windows::Forms::Button^ button_sb;
	private: System::Windows::Forms::Button^ button_sl;
	private: System::Windows::Forms::LinkLabel^ link_more;
	private: System::Windows::Forms::Label^ header_1;

	public:
		gui(void)
			:binPath(nullptr)
		{
			InitializeComponent();
			mouseDown = false;
			timer_anim->Start();

			button_build->FlatStyle = FlatStyle::Flat;
			button_sb->FlatStyle = FlatStyle::Flat;
			button_sl->FlatStyle = FlatStyle::Flat;
			button_build->FlatAppearance->BorderSize = 0;
			button_sb->FlatAppearance->BorderSize = 0;
			button_sl->FlatAppearance->BorderSize = 0;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~gui()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::RadioButton^ radio_loader;
	protected:
	private: System::Windows::Forms::RadioButton^ radio_installer;
	private: System::Windows::Forms::Label^ header_1_back;

	private: System::Windows::Forms::TextBox^ input_bin;
	private: System::Windows::Forms::TextBox^ input_lib;

	private: System::Windows::Forms::Label^ label_bin;
	private: System::Windows::Forms::Label^ label_libs;
	private: System::Windows::Forms::CheckBox^ checkBox1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Timer^ timer_anim;

	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(gui::typeid));
			this->radio_loader = (gcnew System::Windows::Forms::RadioButton());
			this->radio_installer = (gcnew System::Windows::Forms::RadioButton());
			this->header_1_back = (gcnew System::Windows::Forms::Label());
			this->input_bin = (gcnew System::Windows::Forms::TextBox());
			this->input_lib = (gcnew System::Windows::Forms::TextBox());
			this->label_bin = (gcnew System::Windows::Forms::Label());
			this->label_libs = (gcnew System::Windows::Forms::Label());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->timer_anim = (gcnew System::Windows::Forms::Timer(this->components));
			this->header_1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button_build = (gcnew System::Windows::Forms::Button());
			this->button_sb = (gcnew System::Windows::Forms::Button());
			this->button_sl = (gcnew System::Windows::Forms::Button());
			this->link_more = (gcnew System::Windows::Forms::LinkLabel());
			this->SuspendLayout();
			// 
			// radio_loader
			// 
			this->radio_loader->AutoSize = true;
			this->radio_loader->Checked = true;
			this->radio_loader->Font = (gcnew System::Drawing::Font(L"Lucida Sans Unicode", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->radio_loader->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->radio_loader->Location = System::Drawing::Point(505, 119);
			this->radio_loader->Name = L"radio_loader";
			this->radio_loader->Size = System::Drawing::Size(67, 20);
			this->radio_loader->TabIndex = 2;
			this->radio_loader->TabStop = true;
			this->radio_loader->Text = L"Loader";
			this->radio_loader->UseVisualStyleBackColor = true;
			// 
			// radio_installer
			// 
			this->radio_installer->AutoSize = true;
			this->radio_installer->Font = (gcnew System::Drawing::Font(L"Lucida Sans Unicode", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->radio_installer->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->radio_installer->Location = System::Drawing::Point(610, 119);
			this->radio_installer->Name = L"radio_installer";
			this->radio_installer->Size = System::Drawing::Size(76, 20);
			this->radio_installer->TabIndex = 1;
			this->radio_installer->Text = L"Installer";
			this->radio_installer->UseVisualStyleBackColor = true;
			// 
			// header_1_back
			// 
			this->header_1_back->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(33)), static_cast<System::Int32>(static_cast<System::Byte>(33)),
				static_cast<System::Int32>(static_cast<System::Byte>(33)));
			this->header_1_back->Font = (gcnew System::Drawing::Font(L"Lucida Console", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->header_1_back->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(85)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->header_1_back->Location = System::Drawing::Point(208, 44);
			this->header_1_back->Name = L"header_1_back";
			this->header_1_back->Size = System::Drawing::Size(381, 34);
			this->header_1_back->TabIndex = 2;
			this->header_1_back->Text = L"--- HexLoader ---";
			this->header_1_back->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// input_bin
			// 
			this->input_bin->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->input_bin->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->input_bin->Font = (gcnew System::Drawing::Font(L"Consolas", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->input_bin->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->input_bin->Location = System::Drawing::Point(123, 121);
			this->input_bin->Name = L"input_bin";
			this->input_bin->Size = System::Drawing::Size(196, 16);
			this->input_bin->TabIndex = 0;
			// 
			// input_lib
			// 
			this->input_lib->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->input_lib->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->input_lib->Font = (gcnew System::Drawing::Font(L"Consolas", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->input_lib->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->input_lib->Location = System::Drawing::Point(124, 173);
			this->input_lib->Multiline = true;
			this->input_lib->Name = L"input_lib";
			this->input_lib->ReadOnly = true;
			this->input_lib->Size = System::Drawing::Size(196, 118);
			this->input_lib->TabIndex = 1;
			// 
			// label_bin
			// 
			this->label_bin->AutoSize = true;
			this->label_bin->Font = (gcnew System::Drawing::Font(L"Lucida Sans Unicode", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_bin->Location = System::Drawing::Point(36, 120);
			this->label_bin->Name = L"label_bin";
			this->label_bin->Size = System::Drawing::Size(70, 16);
			this->label_bin->TabIndex = 5;
			this->label_bin->Text = L"Executable";
			// 
			// label_libs
			// 
			this->label_libs->AutoSize = true;
			this->label_libs->Font = (gcnew System::Drawing::Font(L"Lucida Sans Unicode", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_libs->Location = System::Drawing::Point(36, 169);
			this->label_libs->Name = L"label_libs";
			this->label_libs->Size = System::Drawing::Size(76, 16);
			this->label_libs->TabIndex = 6;
			this->label_libs->Text = L"Library Files";
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Font = (gcnew System::Drawing::Font(L"Lucida Sans Unicode", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->checkBox1->Location = System::Drawing::Point(538, 210);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(111, 19);
			this->checkBox1->TabIndex = 4;
			this->checkBox1->Text = L"Cleanup Thread";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Lucida Sans Unicode", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(456, 174);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(80, 16);
			this->label1->TabIndex = 9;
			this->label1->Text = L"Run Location";
			// 
			// textBox1
			// 
			this->textBox1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Consolas", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox1->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->textBox1->Location = System::Drawing::Point(543, 175);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(196, 16);
			this->textBox1->TabIndex = 3;
			this->textBox1->Text = L"C:\\temp";
			// 
			// timer_anim
			// 
			this->timer_anim->Interval = 1;
			this->timer_anim->Tick += gcnew System::EventHandler(this, &gui::timer_anim_Tick);
			// 
			// header_1
			// 
			this->header_1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(33)), static_cast<System::Int32>(static_cast<System::Byte>(33)),
				static_cast<System::Int32>(static_cast<System::Byte>(33)));
			this->header_1->Font = (gcnew System::Drawing::Font(L"Lucida Console", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->header_1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->header_1->Location = System::Drawing::Point(330, 44);
			this->header_1->Name = L"header_1";
			this->header_1->Size = System::Drawing::Size(139, 34);
			this->header_1->TabIndex = 10;
			this->header_1->Text = L"HexLoader";
			this->header_1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label2
			// 
			this->label2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(25)),
				static_cast<System::Int32>(static_cast<System::Byte>(25)));
			this->label2->Font = (gcnew System::Drawing::Font(L"Trebuchet MS", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->label2->Location = System::Drawing::Point(34, 7);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(105, 19);
			this->label2->TabIndex = 11;
			this->label2->Text = L"HexLoader ALPHA";
			// 
			// button_build
			// 
			this->button_build->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button_build.BackgroundImage")));
			this->button_build->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button_build->Font = (gcnew System::Drawing::Font(L"Lucida Sans Unicode", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button_build->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->button_build->Location = System::Drawing::Point(658, 271);
			this->button_build->Name = L"button_build";
			this->button_build->Size = System::Drawing::Size(75, 23);
			this->button_build->TabIndex = 12;
			this->button_build->Text = L"Build";
			this->button_build->UseVisualStyleBackColor = true;
			this->button_build->Visible = false;
			// 
			// button_sb
			// 
			this->button_sb->AutoSize = true;
			this->button_sb->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button_sb.BackgroundImage")));
			this->button_sb->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(30)),
				static_cast<System::Int32>(static_cast<System::Byte>(30)));
			this->button_sb->Location = System::Drawing::Point(329, 121);
			this->button_sb->Name = L"button_sb";
			this->button_sb->Size = System::Drawing::Size(24, 15);
			this->button_sb->TabIndex = 13;
			this->button_sb->UseVisualStyleBackColor = true;
			this->button_sb->Visible = false;
			this->button_sb->Click += gcnew System::EventHandler(this, &gui::button_sb_Click);
			// 
			// button_sl
			// 
			this->button_sl->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button_sl.BackgroundImage")));
			this->button_sl->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(30)),
				static_cast<System::Int32>(static_cast<System::Byte>(30)));
			this->button_sl->Location = System::Drawing::Point(335, 173);
			this->button_sl->Name = L"button_sl";
			this->button_sl->Size = System::Drawing::Size(12, 12);
			this->button_sl->TabIndex = 14;
			this->button_sl->UseVisualStyleBackColor = true;
			this->button_sl->Visible = false;
			this->button_sl->Click += gcnew System::EventHandler(this, &gui::button_sl_Click);
			// 
			// link_more
			// 
			this->link_more->AutoSize = true;
			this->link_more->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->link_more->LinkColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(210)), static_cast<System::Int32>(static_cast<System::Byte>(210)),
				static_cast<System::Int32>(static_cast<System::Byte>(210)));
			this->link_more->Location = System::Drawing::Point(713, 50);
			this->link_more->Name = L"link_more";
			this->link_more->Size = System::Drawing::Size(31, 13);
			this->link_more->TabIndex = 15;
			this->link_more->TabStop = true;
			this->link_more->Text = L"More";
			this->link_more->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->link_more->VisitedLinkColor = System::Drawing::SystemColors::ButtonFace;
			// 
			// gui
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(30)),
				static_cast<System::Int32>(static_cast<System::Byte>(30)));
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(796, 325);
			this->Controls->Add(this->link_more);
			this->Controls->Add(this->button_sl);
			this->Controls->Add(this->button_sb);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->header_1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->label_libs);
			this->Controls->Add(this->label_bin);
			this->Controls->Add(this->input_lib);
			this->Controls->Add(this->input_bin);
			this->Controls->Add(this->header_1_back);
			this->Controls->Add(this->radio_installer);
			this->Controls->Add(this->radio_loader);
			this->Controls->Add(this->button_build);
			this->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"gui";
			this->Text = L"gui";
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &gui::gui_MouseDown);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &gui::gui_MouseMove);
			this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &gui::gui_MouseUp);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		private: bool CheckMouseover(vec2 cursorPos, AREA area)
		{
			switch (area)
			{
			case BUTTON_SELECT_BIN:
				return (cursorPos.x >= BSB_AREA_L && cursorPos.x <= BSB_AREA_R
					&& cursorPos.y >= BSB_AREA_T && cursorPos.y <= BSB_AREA_B);

			case BUTTON_SELECT_LIB:
				return (cursorPos.x >= BSL_AREA_L && cursorPos.x <= BSL_AREA_R
					&& cursorPos.y >= BSL_AREA_T && cursorPos.y <= BSL_AREA_B);

			case BUTTON_BUILD:
				return (cursorPos.x >= BB_AREA_L && cursorPos.x <= BB_AREA_R
					&& cursorPos.y >= BB_AREA_T && cursorPos.y <= BB_AREA_B);
			}
		}
		private: System::Void timer_anim_Tick(System::Object^ sender, System::EventArgs^ e)
		{
			static int currentFrame{ 0 },
				ticks{ 0 };

			// Animate header text
			if (++ticks == HEADER_TICK_RATE)
			{
				header_1_back->Text = (currentFrame < NUM_HEADER_FRAMES-1 ? gcnew String(headerFrames[++currentFrame].data()) : gcnew String(headerFrames[currentFrame = 0].data()));
				ticks = 0;
			}
		}
		private: System::Void gui::gui_MouseDown(System::Object^ Sender, System::Windows::Forms::MouseEventArgs^ e)
		{
			// Set mouseDown if left mouse button is down over title bar
			if (e->Y <= TITLE_BAR_HEIGHT && e->X < TITLE_BAR_WIDTH)
			{
				cursorDownPos = Cursor->Position;
				mouseDown = true;
			}

			// Close application if mouse is over close button
			else if (e->Y <= TITLE_BAR_HEIGHT && e->X >= TITLE_BAR_WIDTH)
				Application::Exit();
		}
		private: System::Void gui::gui_MouseUp(System::Object^ Sender, System::Windows::Forms::MouseEventArgs^ e)
		{
			mouseDown = false;
		}
		private: System::Void gui::gui_MouseMove(System::Object^ Sender, System::Windows::Forms::MouseEventArgs^ e)
		{
			// If mouse button down over title bar, move window with cursor
			if (mouseDown)
			{	
				if (Cursor->Position != cursorDownPos)
				{
					cursorDelta = Point(cursorDownPos.X - Cursor->Position.X, cursorDownPos.Y - Cursor->Position.Y);
					Location = System::Drawing::Point(Location.X - cursorDelta.X, Location.Y - cursorDelta.Y);
					cursorDownPos = Cursor->Position;
				}
			}

			// Cycle through button coords, toggle highlight overlay button visibility
			for (unsigned int i = BUTTON_SELECT_BIN; i < NUM_BUTTONS; ++i)
			{
				switch (i)
				{
				case BUTTON_SELECT_BIN:
					buttonPtr = button_sb;
					break;
				case BUTTON_SELECT_LIB:
					buttonPtr = button_sl;
					break;
				case BUTTON_BUILD:
					buttonPtr = button_build;
				}

				if (CheckMouseover(vec2(e->X, e->Y), AREA(i)))
					buttonPtr->Visible = true;

				else if (buttonPtr->Visible)
					buttonPtr->Visible = false;
			}

			//std::cout << "\nX: " << e->X << ", Y: " << e->Y << '\n';	// debug
		}
	
		private: const char* GetPath(AREA button)
		{
			OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;
			static std::string str;
			const char* result{ nullptr };

			openFileDialog1->InitialDirectory = gcnew String(getenv("USERPROFILE"));
			openFileDialog1->FilterIndex = 2;
			openFileDialog1->RestoreDirectory = true;

			switch (button)
			{
			case BUTTON_SELECT_BIN:
				openFileDialog1->Filter = "Exe Files (.exe)|*.exe";
				break;
			case BUTTON_SELECT_LIB:
				openFileDialog1->Filter = "DLL Files (.dll)|*.dll";
			}

			if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				ConvertString(openFileDialog1->FileName, str);
				result = str.c_str();
			}

			return result;
		}
		private: System::Void button_sb_Click(System::Object^ sender, System::EventArgs^ e)
		{
			// Store full path, set input cursor to end
			binPath = GetPath(BUTTON_SELECT_BIN);
			input_bin->Text = gcnew String(binPath);
			input_bin->Select(input_bin->Text->Length, 0);
		}
		private: System::Void button_sl_Click(System::Object^ sender, System::EventArgs^ e)
		{
			// Store full path, add only filename to input_lib text
			std::string path = GetPath(BUTTON_SELECT_LIB);
			libPaths.Add(gcnew String(path.c_str()));
			size_t pos = path.find_last_of("\\");
			path.erase(0, pos + 1);
			input_lib->AppendText(gcnew String(path.c_str()));
			input_lib->AppendText(Environment::NewLine);
		}
	};
}

void ConvertString(System::String^ s, std::string& os)
{
	using namespace System::Runtime::InteropServices;
	const char* chars =
		(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(System::IntPtr((void*)chars));
}