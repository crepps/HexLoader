#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <windows.h>
#include "data.h"

int main()
{
	std::string path;
	std::vector<std::string> fileNames;
	std::vector<unsigned char*> data;
	std::vector<uint64_t> sizes;
	std::ofstream outFile;

	