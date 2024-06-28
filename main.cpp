#include <Windows.h>
#include <fstream>
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
	obj.SetPath(Loader::PATH_BIN, "C:\\temp\\hl_mock_bin.exe");
	ASSERT_THAT(obj.GetBinPath(), Ne(""));
}
TEST_F(LoaderTesting, CheckLibPathsSet)
{
	obj.SetPath(Loader::PATH_LIB, "C:\\temp\\hl_mock_lib1.dll");
	ASSERT_THAT(obj.GetLibPaths().empty(), Eq(false));
}
TEST_F(LoaderTesting, CheckRunPathSet)
{
	obj.SetPath(Loader::PATH_RUN, "C:\\temp");
	ASSERT_THAT(obj.GetRunPath(), Ne(""));
}
TEST_F(LoaderTesting, ValidateBinPath)
{
	obj.SetPath(Loader::PATH_BIN, "C:\\temp\\hl_mock_bin.exe");
	std::ofstream outFile(obj.GetBinPath().c_str(), std::ios::out);	// Create exe at set location
	outFile.close();
	ASSERT_THAT(obj.ValidatePath(Loader::PATH_BIN), Eq(SUCCESS));
}
TEST_F(LoaderTesting, ValidateLibPaths)
{
	obj.SetPath(Loader::PATH_LIB, "C:\\temp\\hl_mock_lib1.dll");
	obj.SetPath(Loader::PATH_LIB, "C:\\temp\\hl_mock_lib2.dll");

	// Create two .dlls at set location
	std::ofstream outFile1(obj.GetLibPaths()[0].c_str(), std::ios::out),
					outFile2(obj.GetLibPaths()[1].c_str(), std::ios::out);
	outFile2.close();
	outFile1.close();

	ASSERT_THAT(obj.ValidatePath(Loader::PATH_LIB), Eq(SUCCESS));
}
TEST_F(LoaderTesting, ValidateRunPath)
{
	obj.SetPath(Loader::PATH_RUN, "C:\\temp");
	ASSERT_THAT(obj.ValidatePath(Loader::PATH_RUN), Eq(SUCCESS));
}
TEST_F(LoaderTesting, ValidateAllPaths)
{
	// Set all paths
	obj.SetPath(Loader::PATH_BIN, "C:\\temp\\hl_mock_bin.exe");
	obj.SetPath(Loader::PATH_LIB, "C:\\temp\\hl_mock_lib1.dll");
	obj.SetPath(Loader::PATH_LIB, "C:\\temp\\hl_mock_lib2.dll");
	obj.SetPath(Loader::PATH_RUN, "C:\\temp");

	// Create exe at set location
	std::ofstream outFile(obj.GetBinPath().c_str(), std::ios::out);
	outFile.close();

	// Create two .dlls at set location
	std::ofstream outFile1(obj.GetLibPaths()[0].c_str(), std::ios::out),
		outFile2(obj.GetLibPaths()[1].c_str(), std::ios::out);
	outFile2.close();
	outFile1.close();

	ASSERT_THAT(obj.ValidatePath(Loader::PATH_ALL), Eq(SUCCESS));
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