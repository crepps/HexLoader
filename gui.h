#pragma once
#include <iostream>
#include <string>
#include <vector>



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
		Loader* loaderPtr;
		bool mouseDown,
			expandConsole;
		Point cursorDownPos,
			cursorDelta;
		const char *binPath,
					*appName;
		std::string* loaderOutput;
		System::Collections::Generic::List<String^> libPaths;
		System::Windows::Forms::Button^ buttonPtr;

		/*
					Constants
		*/

		// Text animation-related
		const unsigned int NUM_BUTTONS{ 3 },
		NUM_HEADER_FRAMES{ 16 },
		HEADER_TICK_RATE{ 9 },

		// Mouse-selectable window regions
		TITLE_BAR_HEIGHT{ 30 },
		TITLE_BAR_WIDTH{ 751 },

		BSB_AREA_L{ 329 },	// BUTTON_SELECT_BIN left, right, top, bottom
		BSB_AREA_R{ 352 },
		BSB_AREA_T{ 121 },
		BSB_AREA_B{ 136 },

		BSL_AREA_L{ 333 },	// BUTTON_SELECT_LIB
		BSL_AREA_R{ 349 },
		BSL_AREA_T{ 172 },
		BSL_AREA_B{ 188 },

		BB_AREA_L{ 657 },	// BUTTON_BUILD
		BB_AREA_R{ 733 },
		BB_AREA_T{ 270 },
		BB_AREA_B{ 294 },

		// Label locations
		XPOS_OFFSET{ 400 },
		XPOS_CHECK_CLEANUP{ 538 },
		XPOS_CHECK_UNINSTALLER{ 554 },
		XPOS_PROMPTS{ 460 },

		// Defaults
		CONSOLE_WIDTH{ 341 };
		const char* DEFAULT_TEXT_RUN{ "C:\\temp" };


	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ button_build;
	private: System::Windows::Forms::Button^ button_sb;
	private: System::Windows::Forms::Button^ button_sl;
	private: System::Windows::Forms::LinkLabel^ link_more;
	private: System::Windows::Forms::CheckBox^ check_shortcut;

	private: System::Windows::Forms::Label^ label_prompts;
	private: System::Windows::Forms::CheckBox^ check_startup;


	private: System::Windows::Forms::CheckBox^ check_uninstaller;
	private: System::Windows::Forms::LinkLabel^ linkLabel1;
	private: System::Windows::Forms::TextBox^ text_output;


	private: System::Windows::Forms::Label^ header_1;

	public:
		gui(Loader& obj)
			:binPath(""),
			appName(""), 
			mouseDown (false),
			expandConsole(false)
		{
			loaderPtr = &obj;
			mouseDown = false;

			InitializeComponent();

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
	private: System::Windows::Forms::CheckBox^ check_cleanup;

	private: System::Windows::Forms::Label^ label_run;

	private: System::Windows::Forms::TextBox^ input_run;

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
			this->check_cleanup = (gcnew System::Windows::Forms::CheckBox());
			this->label_run = (gcnew System::Windows::Forms::Label());
			this->input_run = (gcnew System::Windows::Forms::TextBox());
			this->timer_anim = (gcnew System::Windows::Forms::Timer(this->components));
			this->header_1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button_build = (gcnew System::Windows::Forms::Button());
			this->button_sb = (gcnew System::Windows::Forms::Button());
			this->button_sl = (gcnew System::Windows::Forms::Button());
			this->link_more = (gcnew System::Windows::Forms::LinkLabel());
			this->check_shortcut = (gcnew System::Windows::Forms::CheckBox());
			this->label_prompts = (gcnew System::Windows::Forms::Label());
			this->check_startup = (gcnew System::Windows::Forms::CheckBox());
			this->check_uninstaller = (gcnew System::Windows::Forms::CheckBox());
			this->linkLabel1 = (gcnew System::Windows::Forms::LinkLabel());
			this->text_output = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// radio_loader
			// 
			this->radio_loader->AutoSize = true;
			this->radio_loader->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(32)), static_cast<System::Int32>(static_cast<System::Byte>(32)),
				static_cast<System::Int32>(static_cast<System::Byte>(32)));
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
			this->radio_loader->UseVisualStyleBackColor = false;
			this->radio_loader->CheckedChanged += gcnew System::EventHandler(this, &gui::radio_loader_CheckedChanged);
			// 
			// radio_installer
			// 
			this->radio_installer->AutoSize = true;
			this->radio_installer->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(32)), static_cast<System::Int32>(static_cast<System::Byte>(32)),
				static_cast<System::Int32>(static_cast<System::Byte>(32)));
			this->radio_installer->Font = (gcnew System::Drawing::Font(L"Lucida Sans Unicode", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->radio_installer->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->radio_installer->Location = System::Drawing::Point(610, 119);
			this->radio_installer->Name = L"radio_installer";
			this->radio_installer->Size = System::Drawing::Size(76, 20);
			this->radio_installer->TabIndex = 1;
			this->radio_installer->Text = L"Installer";
			this->radio_installer->UseVisualStyleBackColor = false;
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
			this->input_bin->TextChanged += gcnew System::EventHandler(this, &gui::input_bin_TextChanged);
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
			// check_cleanup
			// 
			this->check_cleanup->AutoSize = true;
			this->check_cleanup->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(32)), static_cast<System::Int32>(static_cast<System::Byte>(32)),
				static_cast<System::Int32>(static_cast<System::Byte>(32)));
			this->check_cleanup->Font = (gcnew System::Drawing::Font(L"Lucida Sans Unicode", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->check_cleanup->Location = System::Drawing::Point(538, 199);
			this->check_cleanup->Name = L"check_cleanup";
			this->check_cleanup->Size = System::Drawing::Size(111, 19);
			this->check_cleanup->TabIndex = 4;
			this->check_cleanup->Text = L"Cleanup Thread";
			this->check_cleanup->UseVisualStyleBackColor = false;
			// 
			// label_run
			// 
			this->label_run->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->label_run->Font = (gcnew System::Drawing::Font(L"Lucida Sans Unicode", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_run->Location = System::Drawing::Point(432, 162);
			this->label_run->Name = L"label_run";
			this->label_run->Size = System::Drawing::Size(99, 16);
			this->label_run->TabIndex = 9;
			this->label_run->Text = L"Run Location";
			this->label_run->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// input_run
			// 
			this->input_run->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->input_run->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->input_run->Font = (gcnew System::Drawing::Font(L"Consolas", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->input_run->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->input_run->Location = System::Drawing::Point(543, 163);
			this->input_run->Name = L"input_run";
			this->input_run->Size = System::Drawing::Size(196, 16);
			this->input_run->TabIndex = 3;
			this->input_run->Text = L"C:\\temp";
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
			this->header_1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(170)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
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
			this->button_build->Click += gcnew System::EventHandler(this, &gui::button_build_Click);
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
			// check_shortcut
			// 
			this->check_shortcut->AutoSize = true;
			this->check_shortcut->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(25)),
				static_cast<System::Int32>(static_cast<System::Byte>(25)));
			this->check_shortcut->Font = (gcnew System::Drawing::Font(L"Lucida Sans Unicode", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->check_shortcut->Location = System::Drawing::Point(860, 243);
			this->check_shortcut->Name = L"check_shortcut";
			this->check_shortcut->Size = System::Drawing::Size(72, 19);
			this->check_shortcut->TabIndex = 16;
			this->check_shortcut->Text = L"Shortcut";
			this->check_shortcut->UseVisualStyleBackColor = false;
			// 
			// label_prompts
			// 
			this->label_prompts->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(29)), static_cast<System::Int32>(static_cast<System::Byte>(29)),
				static_cast<System::Int32>(static_cast<System::Byte>(29)));
			this->label_prompts->Font = (gcnew System::Drawing::Font(L"Lucida Sans Unicode", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_prompts->Location = System::Drawing::Point(860, 223);
			this->label_prompts->Name = L"label_prompts";
			this->label_prompts->Size = System::Drawing::Size(65, 15);
			this->label_prompts->TabIndex = 17;
			this->label_prompts->Text = L"Prompts";
			// 
			// check_startup
			// 
			this->check_startup->AutoSize = true;
			this->check_startup->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(20)), static_cast<System::Int32>(static_cast<System::Byte>(20)),
				static_cast<System::Int32>(static_cast<System::Byte>(20)));
			this->check_startup->Font = (gcnew System::Drawing::Font(L"Lucida Sans Unicode", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->check_startup->Location = System::Drawing::Point(860, 264);
			this->check_startup->Name = L"check_startup";
			this->check_startup->Size = System::Drawing::Size(65, 19);
			this->check_startup->TabIndex = 18;
			this->check_startup->Text = L"Startup";
			this->check_startup->UseVisualStyleBackColor = false;
			// 
			// check_uninstaller
			// 
			this->check_uninstaller->AutoSize = true;
			this->check_uninstaller->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(32)),
				static_cast<System::Int32>(static_cast<System::Byte>(32)), static_cast<System::Int32>(static_cast<System::Byte>(32)));
			this->check_uninstaller->Font = (gcnew System::Drawing::Font(L"Lucida Sans Unicode", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->check_uninstaller->Location = System::Drawing::Point(954, 199);
			this->check_uninstaller->Name = L"check_uninstaller";
			this->check_uninstaller->Size = System::Drawing::Size(84, 19);
			this->check_uninstaller->TabIndex = 19;
			this->check_uninstaller->Text = L"Uninstaller";
			this->check_uninstaller->UseVisualStyleBackColor = false;
			// 
			// linkLabel1
			// 
			this->linkLabel1->AutoSize = true;
			this->linkLabel1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(20)), static_cast<System::Int32>(static_cast<System::Byte>(20)),
				static_cast<System::Int32>(static_cast<System::Byte>(20)));
			this->linkLabel1->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->linkLabel1->LinkColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->linkLabel1->Location = System::Drawing::Point(593, 276);
			this->linkLabel1->Name = L"linkLabel1";
			this->linkLabel1->Size = System::Drawing::Size(35, 13);
			this->linkLabel1->TabIndex = 20;
			this->linkLabel1->TabStop = true;
			this->linkLabel1->Text = L"Reset";
			this->linkLabel1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->linkLabel1->VisitedLinkColor = System::Drawing::SystemColors::ButtonFace;
			this->linkLabel1->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &gui::linkLabel1_LinkClicked);
			// 
			// text_output
			// 
			this->text_output->BackColor = System::Drawing::SystemColors::InfoText;
			this->text_output->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->text_output->Cursor = System::Windows::Forms::Cursors::Default;
			this->text_output->Font = (gcnew System::Drawing::Font(L"Cascadia Code", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->text_output->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(170)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->text_output->Location = System::Drawing::Point(400, 106);
			this->text_output->Margin = System::Windows::Forms::Padding(5);
			this->text_output->Multiline = true;
			this->text_output->Name = L"text_output";
			this->text_output->ReadOnly = true;
			this->text_output->Size = System::Drawing::Size(0, 193);
			this->text_output->TabIndex = 21;
			// 
			// gui
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(30)),
				static_cast<System::Int32>(static_cast<System::Byte>(30)));
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(793, 325);
			this->Controls->Add(this->text_output);
			this->Controls->Add(this->linkLabel1);
			this->Controls->Add(this->check_uninstaller);
			this->Controls->Add(this->check_startup);
			this->Controls->Add(this->label_prompts);
			this->Controls->Add(this->check_shortcut);
			this->Controls->Add(this->link_more);
			this->Controls->Add(this->button_sl);
			this->Controls->Add(this->button_sb);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->header_1);
			this->Controls->Add(this->label_run);
			this->Controls->Add(this->input_run);
			this->Controls->Add(this->check_cleanup);
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
			static bool build{ false };

			// Animate header text
			if (++ticks == HEADER_TICK_RATE)
			{
				header_1_back->Text = (currentFrame < NUM_HEADER_FRAMES-1 ? gcnew String(headerFrames[++currentFrame].data()) : gcnew String(headerFrames[currentFrame = 0].data()));
				ticks = 0;
			}

			// Expand console
			if (expandConsole)
			{
				if (text_output->Size.Width < CONSOLE_WIDTH)
					text_output->Width += 25;
				else if (!build)
				{
					build = true;
					Build();
				}
			}

			// Hide console
			else
			{
				if (text_output->Size.Width > 0)
					text_output->Width -= 25;
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
			input_lib->AppendText(System::Environment::NewLine);
		}
		private: System::Void radio_loader_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
		{
			// Loader selected
			if (radio_loader->Checked == true)
			{
				// Displace installer input
				check_uninstaller->Location = System::Drawing::Point(XPOS_CHECK_UNINSTALLER + XPOS_OFFSET, check_uninstaller->Location.Y);
				label_prompts->Location = System::Drawing::Point(XPOS_PROMPTS + XPOS_OFFSET, label_prompts->Location.Y);
				check_shortcut->Location = System::Drawing::Point(XPOS_PROMPTS + XPOS_OFFSET, check_shortcut->Location.Y);
				check_startup->Location = System::Drawing::Point(XPOS_PROMPTS + XPOS_OFFSET, check_startup->Location.Y);

				// Restore loader input
				check_cleanup->Location = System::Drawing::Point(XPOS_CHECK_CLEANUP, check_cleanup->Location.Y);

				// Change label
				label_run->Text = "Run Location";

				// Change suggested path
				input_run->Text = "C:\\temp";
			}

			// Installer selected
			else
			{
				// Displace loader input
				check_cleanup->Location = System::Drawing::Point(XPOS_CHECK_CLEANUP + XPOS_OFFSET, check_cleanup->Location.Y);

				// Restore installer input
				check_uninstaller->Location = System::Drawing::Point(XPOS_CHECK_UNINSTALLER, check_uninstaller->Location.Y);
				label_prompts->Location = System::Drawing::Point(XPOS_PROMPTS, label_prompts->Location.Y);
				check_shortcut->Location = System::Drawing::Point(XPOS_PROMPTS, check_shortcut->Location.Y);
				check_startup->Location = System::Drawing::Point(XPOS_PROMPTS, check_startup->Location.Y);
				check_startup->Size.Width += 1;

				// Change label
				label_run->Text = "Install Location";

				// Change suggested path
				std::string path("C:\\Program Files\\");
				path.append(appName);
				input_run->Text = gcnew String(path.c_str());
			}
		}
		private: System::Void Reset()
		{
			radio_loader->Checked = true;
			libPaths.Clear();
			input_bin->Text = "";
			input_lib->Text = "";
			input_run->Text = gcnew String(DEFAULT_TEXT_RUN);
			check_cleanup->Checked = false;
			check_uninstaller->Checked = false;
			check_shortcut->Checked = false;
			check_startup->Checked = false;
		}
		private: System::Void linkLabel1_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e)
		{
			Reset();
		}
		private: System::Void input_bin_TextChanged(System::Object^ sender, System::EventArgs^ e)
		{
			std::string path;
			ConvertString(input_bin->Text, path);
			loaderPtr->SetPath(Loader::PATH_BIN, path);
		}
		private: System::Void button_build_Click(System::Object^ sender, System::EventArgs^ e)
		{
			/* Reveal text output area, call Build() from
				timer_anim_tick() when area is fully expanded */

			expandConsole = true;
		}
		private: unsigned int Build()
		{
			text_output->Clear();

			// Validate file paths
			text_output->AppendText("Validating file paths.                         <-"
				+ System::Environment::NewLine);

			unsigned int pathResult = loaderPtr->ValidatePath(Loader::PATH_ALL);

			if (pathResult != SUCCESS)
			{
				switch (pathResult)
				{
				case Loader::PATH_BIN:
					text_output->AppendText("Invalid executable path specified.");
					break;
				case Loader::PATH_LIB:
					text_output->AppendText("Invalid DLL path(s) specified.");
					break;
				case Loader::PATH_RUN:
					text_output->AppendText("Invalid run path specified.");
					break;
				}

				return FAILURE_CONTINUE;
			}

			// Check for compiler, install if not found
			if (!loaderPtr->CompilerInstalled())
				loaderPtr->InstallCompiler(loaderOutput);

			return SUCCESS;
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