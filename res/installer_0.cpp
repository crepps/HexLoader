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
					bool& shortcut,
					bool& startup)
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

		if (shortcut)
		{
			input = MessageBoxA(0, "Create a desktop shortcut?", "Shortcut", MB_YESNO);

			if (input == IDYES)
				shortcut = true;
		}
		
		if (startup)
		{
			input = MessageBoxA(0, "Launch application when Windows starts?", "Startup", MB_YESNO);

			if (input == IDYES)
				startup = true;
		}
		
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

int createRegKey(const std::string& path, const std::string& filename, const std::string& appName)
{
	std::string filePath{ path + "\\" + filename };

	std::wstring wstr1{ std::wstring(filePath.begin(), filePath.end()) },
				wstr2(std::wstring(appName.begin(), appName.end()));

	HKEY hKey;

	LONG result = RegCreateKeyExW(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, 0, KEY_WRITE, NULL, &hKey, NULL);

	if (result != 0)
		return result;

	result = RegSetValueExW(hKey, wstr2.c_str(), 0, REG_SZ, (BYTE*)wstr1.c_str(), ((wstr1.size() + 1) * sizeof(wchar_t)));

	return (int)result;
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
		startup{ false },
		launch{ false };
	int result{ 0 };
		 
	const unsigned int STAGE1{0},
					   STAGE2{1};

	