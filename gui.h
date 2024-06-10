#pragma once
#include <string>
#include <vector>

#define TITLE_BAR_HEIGHT 30
#define TITLE_BAR_WIDTH 751
#define NUM_HEADER_FRAMES 16
#define HEADER_TICK_RATE 9

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
			cursorPos,
			cursorDelta;
	private: System::Windows::Forms::Label^ header_1;


	public:
		gui(void)
		{
			InitializeComponent();
			mouseDown = false;
			timer_anim->Start();
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
	private: System::Windows::Forms::TextBox^ input_libs;
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
			this->input_libs = (gcnew System::Windows::Forms::TextBox());
			this->label_bin = (gcnew System::Windows::Forms::Label());
			this->label_libs = (gcnew System::Windows::Forms::Label());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->timer_anim = (gcnew System::Windows::Forms::Timer(this->components));
			this->header_1 = (gcnew System::Windows::Forms::Label());
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
			this->radio_loader->TabIndex = 0;
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
			this->header_1_back->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->header_1_back->Location = System::Drawing::Point(208, 44);
			this->header_1_back->Name = L"header_1_back";
			this->header_1_back->Size = System::Drawing::Size(381, 34);
			this->header_1_back->TabIndex = 2;
			this->header_1_back->Text = L"---- HexLoader ----";
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
			this->input_bin->TabIndex = 3;
			// 
			// input_libs
			// 
			this->input_libs->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->input_libs->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->input_libs->Font = (gcnew System::Drawing::Font(L"Consolas", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->input_libs->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->input_libs->Location = System::Drawing::Point(124, 173);
			this->input_libs->Multiline = true;
			this->input_libs->Name = L"input_libs";
			this->input_libs->ReadOnly = true;
			this->input_libs->Size = System::Drawing::Size(196, 118);
			this->input_libs->TabIndex = 4;
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
			this->checkBox1->Location = System::Drawing::Point(535, 210);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(111, 19);
			this->checkBox1->TabIndex = 7;
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
			this->textBox1->TabIndex = 8;
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
			// gui
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(30)),
				static_cast<System::Int32>(static_cast<System::Byte>(30)));
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(796, 325);
			this->Controls->Add(this->header_1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->label_libs);
			this->Controls->Add(this->label_bin);
			this->Controls->Add(this->input_libs);
			this->Controls->Add(this->input_bin);
			this->Controls->Add(this->header_1_back);
			this->Controls->Add(this->radio_installer);
			this->Controls->Add(this->radio_loader);
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
		private: System::Void timer_anim_Tick(System::Object^ sender, System::EventArgs^ e)
		{
			static int currentFrame{ 0 },
				ticks{ 0 };

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
			if (mouseDown)
			{
				cursorPos = Cursor->Position;
				if (cursorPos != cursorDownPos)
				{
					cursorDelta = Point(cursorDownPos.X - cursorPos.X, cursorDownPos.Y - cursorPos.Y);
					Location = System::Drawing::Point(Location.X - cursorDelta.X, Location.Y - cursorDelta.Y);
					cursorDownPos = cursorPos;
				}
			}
		}
};
}