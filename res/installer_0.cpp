#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <windows.h>
#include "data.h"

unsigned int prompt(unsigned int stage,
					const std::string& appName,
					std::string& path,
					bool& shortcut,
					bool& autoStart)
{
	int input{ 0 };
	std::string

	if (!stage)
	{
		input = MessageBoxA(0, "Press OK to install " + appName + ".", appName + " Installer", MB_OKCANCEL);

		if (input == IDCANCEL)
			return 1;

		input = MessageBoxA(0, "Installation location: " + path + "\n\nInstall to default location ? ", "Install Location", MB_YESNO);

		if (input == IDNO)
		{
			std::string buffer{ browsePath(appName) };
			path = (buffer == "CANCEL" ? path : buffer);
		}

		input = MessageBoxA(0, "Create a desktop shortcut?", "Shortcut", MB_YESNO);

		if (input == IDYES)
			shortcut = true;
	}

	else
	{
		input = MessageBoxA(0, "Installation complete.\n\nLaunch " + appName + " now?", "Success", MB_YESNO);

		if (input == IDNO)
			autoStart = false;
	}
}

std::string Installer::browsePath(const std::string appName)
{
	BROWSEINFO bi{ 0 };
	LPITEMIDLIST list;
	TCHAR buffer[MAX_PATH] = L"\0";

	bi.lpszTitle = L"Select installation location...";
	list = SHBrowseForFolder(&bi);

	if (SHGetPathFromIDList(list, buffer))
	{
		std::string path = buffer;
		path.append("\\" + appName);
		return path;
	}

	return "CANCEL";
}

int createShortcut(const std::string& path, const std::string& appName)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::wstring wPath{ converter.from_bytes(path) },
				 wAppName{ converter.from_bytes(appName) };

	CoInitialize(NULL);
	IShellLink* pShellLink = NULL;
	HRESULT hres;
	hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_ALL,
		IID_IShellLink, (void**)&pShellLink);

	if (SUCCEEDED(hres))
	{
		std::wstring filePath{ wPath + L"\\" + wAppName};

		pShellLink->SetPath(filePath.c_str());
		pShellLink->SetDescription(wAppName);
		pShellLink->SetIconLocation(filePath.c_str(), 0);

		IPersistFile* pPersistFile;
		hres = pShellLink->QueryInterface(IID_IPersistFile, (void**)&pPersistFile);

		if (SUCCEEDED(hres))
		{
			std::string linkPath{ getenv("USERPROFILE") + "\\Desktop\\" + appName + ".lnk" };
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
	std::string appName, path;
	std::vector<std::string> fileNames;
	std::vector<unsigned char*> data;
	std::vector<uint64_t> sizes;
	std::ofstream outFile;

	