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
class InitTesting : public ::testing::Test
{
public:
	Loader obj;

	void SetUp() override
	{
		// Set bin, lib and run paths
		obj.SetPath(Loader::PATH_BIN, "C:\\temp\\hl_mock_bin.exe");
		obj.SetPath(Loader::PATH_LIB, "C:\\temp\\hl_mock_lib1.dll");
		obj.SetPath(Loader::PATH_LIB, "C:\\temp\\hl_mock_lib2.dll");
		obj.SetPath(Loader::PATH_RUN, "C:\\temp");

		// Create exe file at set location
		std::ofstream outFile(obj.GetBinPath().c_str(), std::ios::out);

		// Create two dll files at set location
		std::ofstream outFile1(obj.GetLibPaths()[0].c_str(), std::ios::out),
			outFile2(obj.GetLibPaths()[1].c_str(), std::ios::out);
		outFile2.close();
		outFile1.close();
	}
};

class CompilerTesting : public ::testing::Test
{
public:
	Loader obj;

	void SetUp() override
	{

	}
	std::string ExecuteCmd(const std::string& cmd)
	{
		obj.SetProcessCmd(cmd);
		obj.SpawnInstallerThread();
		std::string output("");
		do
		{
			output += obj.OffloadBuffer();
			obj.ClearBuffer();
			Sleep(100);

		} while (obj.GetBufferLoaded());

		return output;
	}
};

/*											*
				Init Tests
 *											*/

TEST_F(InitTesting, BinPathSet)
{
	ASSERT_THAT(obj.GetBinPath(), Ne(""));
}
TEST_F(InitTesting, LibPathsSet)
{
	ASSERT_FALSE(obj.GetLibPaths().empty());
}
TEST_F(InitTesting, RunPathSet)
{
	ASSERT_THAT(obj.GetRunPath(), Ne(""));
}
TEST_F(InitTesting, BinPathValid)
{	
	ASSERT_THAT(obj.ValidatePath(Loader::PATH_BIN), Eq(SUCCESS));
}
TEST_F(InitTesting, LibPathsValid)
{
	ASSERT_THAT(obj.ValidatePath(Loader::PATH_LIB), Eq(SUCCESS));
}
TEST_F(InitTesting, RunPathValid)
{
	ASSERT_THAT(obj.ValidatePath(Loader::PATH_RUN), Eq(SUCCESS));
}
TEST_F(InitTesting, AllPathsValid)
{
	ASSERT_THAT(obj.ValidatePath(Loader::PATH_ALL), Eq(SUCCESS));
}

/*											*
				Compiler Tests
 *											*/

TEST_F(CompilerTesting, CompilerInstallChecked)
{
	// Check whether compiler is installed on target system, ignore result
	obj.CompilerInstalled();

	// Verify that installation was checked
	ASSERT_TRUE(obj.CompilerChecked());
}
TEST_F(CompilerTesting, ReadProcessStdout)
{
	std::string output{ ExecuteCmd("echo hexloader") };

	ASSERT_THAT(output, Eq("hexloader \n"));
}
TEST_F(CompilerTesting, ReadProcessErrout)
{
	std::string output{ ExecuteCmd("tasklist x") };

	ASSERT_THAT(output.find("ERROR"), Ne(std::string::npos));
}
TEST_F(CompilerTesting, RunProcessAsynchronously)
{
	ASSERT_THAT(obj.SpawnInstallerThread(), Eq(SUCCESS));
}
TEST_F(CompilerTesting, DISABLED_CompilerInstallSuccessful)
{
	obj.InstallCompiler();
	ASSERT_TRUE(obj.CompilerInstalled());
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
		Loader obj;
		Application::EnableVisualStyles();
		Application::SetCompatibleTextRenderingDefault(false);
		HexLoader::gui mainForm(obj);
		Application::Run(% mainForm);
	}
	catch (std::exception& e)
	{
		MessageBox::Show(gcnew String(e.what()), "Exception occured.");
		return EXIT_FAILURE;
	}
	catch (...)
	{
		MessageBox::Show("Unknown exception.", "Exception occured.");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}