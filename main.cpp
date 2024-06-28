#include <Windows.h>
#include <filesystem>
#include "loader.h"
#include "gui.h"

#define UNIT_TESTING

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

TEST_F(LoaderTesting, CheckBinPathSet)
{
	obj.SetPath(Loader::PATH_BIN, "C:\\temp\\bin.exe");
	ASSERT_THAT(obj.GetBinPath(), Ne(""));
}
TEST_F(LoaderTesting, CheckLibPathsSet)
{
	obj.SetPath(Loader::PATH_LIB, "C:\\temp\\lib.dll");
	ASSERT_THAT(obj.GetLibPaths().empty(), Eq(false));
}
TEST_F(LoaderTesting, CheckRunPathSet)
{
	obj.SetPath(Loader::PATH_RUN, "C:\\temp\\");
	ASSERT_THAT(obj.GetRunPath(), Ne(""));
}
//TEST_F(LoaderTesting, ValidateBinPath)
//{
//	ASSERT_THAT(obj.ValidatePath(Loader::PATH_BIN), Eq(SUCCESS));
//}

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