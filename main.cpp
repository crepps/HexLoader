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
		std::ofstream outFile1(obj.GetBinPath().c_str(), std::ios::out);
		outFile1 << "bin data";
		outFile1.close();

		// Create two dll files at set location
		std::ofstream outFile2(obj.GetLibPaths()[0].c_str(), std::ios::out),
			outFile3(obj.GetLibPaths()[1].c_str(), std::ios::out);
		outFile2 << "lib data1";
		outFile3 << "lib data2";
		outFile2.close();
		outFile3.close();
	}
};

class CompilerTesting : public ::testing::Test
{
public:
	Loader obj;

	std::string ExecuteCmd(const std::string& cmd)
	{
		obj.SpawnProcThread(cmd);
		std::string output("");

		while (!obj.Reading());

		while (obj.Reading())
		{
			if (obj.GetBufferLoaded())
			{
				output += obj.OffloadBuffer();
				obj.ClearBuffer();
				Sleep(100);
			}
		}

		return output;
	}
};

class BuildTesting : public ::testing::Test
{
public:
	Loader obj;
	const char *TEST_FILE_PATH{ "C:\\temp\\hex_test.exe" },
			   *HEX_REPRESENTATION{ "0x64, 0x61, 0x74, 0x61" };

	void SetUp() override
	{
		// Create exe file at set location
		std::ofstream outFile{ TEST_FILE_PATH, std::ios::out };
		outFile << "data";
		outFile.close();
		obj.SetPath(Loader::PATH_BIN, TEST_FILE_PATH);
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
	unsigned int installed{ 2 };
	installed = (int)obj.CompilerInstalled();
	ASSERT_THAT(installed, Ne(2));
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
TEST_F(CompilerTesting, ChocoInstallChecked)
{
	unsigned int installed{ 2 };
	installed = (int)obj.ChocoInstalled();
	ASSERT_THAT(installed, Ne(2));
}

/*											*
				Build Tests
 *											*/

TEST_F(BuildTesting, AppDataExists)
{
	ASSERT_TRUE(obj.CheckAppData());
}
TEST_F(BuildTesting, FilesHexDumped)
{
	std::string hex{ obj.HexDump(TEST_FILE_PATH) };
	ASSERT_THAT(hex, Eq(HEX_REPRESENTATION));
}
TEST_F(BuildTesting, HeaderGenerated)
{
	ASSERT_THAT(obj.BuildHeader(), Eq(SUCCESS));
}
TEST_F(BuildTesting, ImplFileGenerated)
{
	ASSERT_THAT(obj.BuildImplFile(), Eq(SUCCESS));
}
TEST_F(BuildTesting, NewBinCompiled)
{
	obj.BuildHeader();
	obj.BuildImplFile();

	unsigned int result = obj.Compile();

	while (!obj.Reading());

	while (obj.Reading())
		obj.GetBufferLoaded();
	
	ASSERT_THAT(result, Eq(SUCCESS));
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