#include <Windows.h>
#include <filesystem>
#include "loader.h"
#include "gui.h"

//#define UNIT_TESTING

using namespace System;
using namespace System::Windows::Forms;


#ifdef UNIT_TESTING
#include "gmock/gmock.h"
using namespace testing;
class LoaderTesting : public ::testing::Test
{
public:
	Loader obj;
};

TEST_F(LoaderTesting, Test1)
{
	ASSERT_THAT(someValue, Eq(0));
}

#endif

[STAThreadAttribute]
int main(array<String^>^ args)
{
#ifdef UNIT_TESTING
	testing::InitGoogleMock();

	if (RUN_ALL_TESTS())
		return EXIT_FAILURE;
#endif

	try
	{
		Application::EnableVisualStyles();
		Application::SetCompatibleTextRenderingDefault(false);
		HexLoader::gui mainForm;
		Application::Run(% mainForm);
	}
	catch (std::exception& e)
	{
		MessageBox::Show(gcnew String(e.what()));
		return EXIT_FAILURE;
	}
	catch (...)
	{
		MessageBox::Show("Unknown exception occured.");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}