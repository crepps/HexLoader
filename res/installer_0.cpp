#include <sstream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <shlobj.h>
#include <locale>
#include <codecvt>
#include <windows.h>
#include "data.h"

std::string browsePath(const std::string appName)
{
	BROWSEINFO bi{ 0 };
	LPITEMIDLIST list;
	TCHAR buffer[MAX_PATH] = "\0";

	bi.lpszTitle = "Select installation location...";
	list = SHBrowseForFolder(&bi);

	if (SHGetPathFromIDList(list, buffer))
	{
		std::string path = buffer;
		path.append("\\" + appName);
		return path;
	}

	return "CANCEL";
}

unsigned int prompt(unsigned int stage,
					const std::string& appName,
					std::string& path,
					bool& shortcut)
{
	int input{ 0 };
	std::string msg1{ "" },
		   msg2{ "" },
		   msg3{ "" },
		   title1{ "" };
	std::stringstream ss;

	// Concatenate messages with stringstream
	ss << "Press OK to install " << appName << ".";
	msg1 = ss.str();
	
	ss.str("");
	ss << appName << " Installer";
	title1 = ss.str();

	ss.str("");
	ss << "Installation location: " << path << "\n\nInstall to default location?";
	msg2 = ss.str();

	ss.str("");
	ss << "Installation complete.\n\nLaunch " << appName << " now?";
	msg3 = ss.str();

	// Spawn message boxes, two stages
	if (!stage)
	{
		input = MessageBoxA(0, msg1.c_str(), title1.c_str(), MB_OKCANCEL);

		if (input == IDCANCEL)
			return 1;

		input = MessageBoxA(0, msg2.c_str(), "Install Location", MB_YESNO);

		if (input == IDNO)
		{
			std::string buffer{ browsePath(appName) };
			path = (buffer == "CANCEL" ? path : buffer);
		}

		input = MessageBoxA(0, "Create a desktop shortcut?", "Shortcut", MB_YESNO);

		if (input == IDYES)
			shortcut = true;
		
		return 0;
	}

	else
	{
		input = MessageBoxA(0, msg3.c_str(), "Success", MB_YESNO);

		if (input == IDYES)
			return 1;

		return 0;
	}
}

int createShortcut(const std::string& path, const std::string& appName)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	CoInitialize(NULL);
	IShellLink* pShellLink = NULL;
	HRESULT hres;
	hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_ALL,
		IID_IShellLink, (void**)&pShellLink);

	if (SUCCEEDED(hres))
	{
		std::string filePath{ path + "\\" + appName};
		pShellLink->SetPath(filePath.c_str());
		pShellLink->SetDescription(appName.c_str());
		pShellLink->SetIconLocation(filePath.c_str(), 0);

		IPersistFile* pPersistFile;
		hres = pShellLink->QueryInterface(IID_IPersistFile, (void**)&pPersistFile);

		if (SUCCEEDED(hres))
		{
			std::string linkPath{ getenv("USERPROFILE") };
			linkPath += "\\Desktop\\" + appName + ".lnk";
			std::wstring wLinkPath = converter.from_bytes(linkPath);
			hres = pPersistFile->Save(wLinkPath.c_str(), TRUE);
			pPersistFile->Release();
		}

		else
			return 2;

		pShellLink->Release();
	}

	else
		return 1;

	return 0;
}

int main()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	
	std::string appName, path;
	std::vector<std::string> fileNames;
	std::vector<unsigned char*> data;
	std::vector<uint64_t> sizes;
	std::ofstream outFile;
	bool shortcut{ false },
		 autoStart{ false };
		 
	const unsigned int STAGE1{0},
					   STAGE2{1};

	