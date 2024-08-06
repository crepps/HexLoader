#include "loader.h"

void Loader::SetPath(PATH_TYPE type, const std::string& path) noexcept
{
	switch (type)
	{
	case PATH_BIN:
		binPath = path;
		break;

	case PATH_LIB:
		try
		{
			libPaths.push_back(path);
		}
		catch (...)
		{
			SetError("Exeception thrown while attempting to push lib path.");
		}
		break;

	case PATH_EXPORT:
		exportPath = path;
		break;

	case PATH_RUN:
		runPath = path;
	}
}
unsigned int Loader::ValidatePath(PATH_TYPE type) const noexcept
{
	struct stat statInfo;

	// Return path type if file/directory doesn't exist
	switch (type)
	{
	case PATH_ALL:
	case PATH_BIN:
		if (stat(binPath.c_str(), &statInfo) != 0 || binPath == "")
			return (unsigned int)PATH_BIN;
		if (type)
			break;

	case PATH_LIB:
		if (libPaths.empty())
			return (unsigned int)PATH_LIB;
		for (auto& path : libPaths)
		{
			if (stat(path.c_str(), &statInfo) != 0)
				return (unsigned int)PATH_LIB;
		}
		if (type)
			break;

	case PATH_EXPORT:
		if (stat(exportPath.c_str(), &statInfo) != 0 || exportPath == "")
			return (unsigned int)PATH_EXPORT;
		if (type)
			break;

	case PATH_RUN:
		if (stat(runPath.c_str(), &statInfo) != 0 || runPath == "")
			return (unsigned int)PATH_RUN;
	}

	return SUCCESS;
}
bool Loader::CompilerInstalled() const noexcept
{
	struct stat statInfo;

	if (stat(PATH_COMPILER, &statInfo) == 0)
		return true;

	return false;
}
unsigned int Loader::SpawnProcThread(const std::string& cmd) noexcept
{
	try
	{
		std::thread procThread(&Loader::Command, this, cmd);
		procThread.detach();
	}
	catch (std::exception& e)
	{
		SetError(e.what());
		return FAILURE_CONTINUE;
	}
	catch (...)
	{
		SetError("Exception thrown when attempting to spawn process thread.");
		return FAILURE_CONTINUE;
	}

	return SUCCESS;
}
unsigned int Loader::Command(const std::string& arg) noexcept
{
	// There's output to be read
	reading = true;

	// Redirect process's stderr to stdout stream
	std::string command(arg);
	command += " 2>&1";

	// Open pipe for reading, execute command
	FILE* pipe;
	try
	{
		pipe = _popen(command.c_str(), "r");
	}
	catch (...)
	{
		LoadBuffer("Failed: _popen threw an exception when attempting to open pipe.");
		return FAILURE_CONTINUE;
	}
	if (!pipe)
	{
		LoadBuffer("Failed to open pipe.");
		return FAILURE_CONTINUE;
	}

	// Load buffer with process output
	try
	{
		char output[BUFFER_SIZE];
		while (fgets(output, BUFFER_SIZE, pipe) != NULL)
			LoadBuffer(output);
		_pclose(pipe);
	}
	catch (...)
	{
		_pclose(pipe);
		SetError("Failed to read from pipe when loading output buffer.");
		return FAILURE_CONTINUE;
	}

	// No more output
	reading = false;

	return SUCCESS;
}
void Loader::LoadBuffer(const std::string& arg) noexcept
{
	/*	Block until output mutex unlocked,
		lock mutex, write data, unlock   */ 

	try
	{
		{
			std::scoped_lock<std::mutex> lock(outputMutex);
			outputBuffer += arg;
		}
	}
	catch (std::exception& e)
	{
		SetError(e.what());
		return;
	}
	catch (...)
	{
		SetError("Exception thrown when attempting to lock or unlock output mutex.");
		return;
	}

	// Tell front-end that a chunk of output is ready
	bufferLoaded = true;

	// Sleep until buffer is emptied by client
	while (bufferLoaded)
		Sleep(outputDelay);
}
const char* Loader::OffloadBuffer() noexcept
{
	/*	Block until output mutex unlocked,
		lock mutex, return data   */

	try
	{
		outputMutex.lock();
	}
	catch (std::exception& e)
	{
		SetError(e.what());
	}
	catch (...)
	{
		SetError("Exception thrown when attempting to lock output mutex for reading.");
	}

	return outputBuffer.c_str();
}
void Loader::ClearBuffer() noexcept
{
	// Clear buffer, unlock mutex, reset flag
	try
	{
		outputBuffer.clear();
		outputBuffer = "";
		outputMutex.unlock();
		bufferLoaded = false;
	}
	catch (std::exception& e)
	{
		SetError(e.what());
	}
	catch (...)
	{
		SetError("Exception thrown when attempting to unlock output mutex.");
	}
}
bool Loader::ChocoInstalled() const noexcept
{
	struct stat statInfo;

	if (stat(PATH_CHOCO, &statInfo) == 0)
		return true;

	return false;
}
bool Loader::CheckAppData() noexcept
{
	/*	Check whether app data exists,
		attempt to create if it doesn't   */

	try
	{
		struct stat statInfo;
		
		// Set path
		appDataPath = getenv("LOCALAPPDATA");
		appDataPath += "\\HexLoader";

		// Return true if folder exists
		if (stat(appDataPath.c_str(), &statInfo) == 0)
			return true;

		// Attempt to create folder
		std::error_code err;
		std::filesystem::create_directories(appDataPath, err);

		// Return whether folder was created successfully
		return stat(appDataPath.c_str(), &statInfo) == 0;
	}
	catch (std::exception& e)
	{
		SetError(e.what());
		return false;
	}
	catch (...)
	{
		SetError("Exception thrown when attempting to create app data folder.");
		return false;
	}
}
std::string Loader::HexDump(const std::string& path) noexcept
{
	/*	
		Convert file data to hex
								   */

	try
	{
		// Read file data
		std::ifstream inFile(path, std::ios::in | std::ios::binary);
		std::stringstream ss;
		ss << inFile.rdbuf();
		inFile.close();
		std::string data{ ss.str() };
		ss.clear();
		ss.str("");

		// Convert to comma-separated hex bytes and return string
		for (auto& byte : data)
		{
			ss << "0x" << std::hex << std::setw(2) << std::setfill('0') << (unsigned int)(byte & 0xFF);
			if (&byte != &data.back())
				ss << ", ";
		}

		return ss.str();
	}
	catch (std::exception& e)
	{
		SetError(e.what());
	}
	catch (...)
	{
		SetError("Exception thrown while attempting to hex dump files.");
	}

	return "FAILURE_CONTINUE";
}
std::string Loader::GetResourceData(unsigned int arg) const noexcept
{
	std::string result;
	HRSRC hRes = FindResource(GetModule(), MAKEINTRESOURCE(arg), MAKEINTRESOURCE(TEXTFILE));
	HGLOBAL hData = LoadResource(GetModule(), hRes);
	DWORD hSize = SizeofResource(GetModule(), hRes);
	char* hFinal = (char*)LockResource(hData);
	result.assign(hFinal, hSize);

	return result;
}
unsigned int Loader::BuildHeader() noexcept
{
	/*	Write C instructions to store hex data
		in char array inside new header file   */

	try
	{
		uint64_t fileSize{ 0 };
		std::string varName,
			headerPath;
		std::ofstream outFile;

		varNames.clear();
		fileSizes.clear();

		// Load file paths into one vector
		std::vector<std::string> paths;
		paths.push_back(binPath);

		for (auto& path : libPaths)
			paths.push_back(path);

		// Create app data folder if it doesn't exist
		if (!CheckAppData())
		{
			SetError("Failed to create app data folder when attempting to build header.");
			return FAILURE_CONTINUE;
		}

		// Create empty file
		headerPath = appDataPath + "\\data.h";
		outFile.open(headerPath, std::ios::trunc);
		outFile.close();

		// For all paths
		for (auto& path : paths)
		{
			/*	Get file size, store original file name,
				replace '.' in file extension with '_'
				for new variable name   */

			fileSize = std::filesystem::file_size(path);
			varName = path;
			size_t strPos = varName.find_last_of("\\");
			varName.erase(0, strPos + 1);
			fileNames.push_back(varName);
			varName.replace(varName.length() - 4, 1, "_");

			// Push both into parallel member vectors
			varNames.push_back(varName);
			fileSizes.push_back(fileSize);

			/* Hex dump bin file, open header file, write declarations

					static const unsigned int varName_size{ fileSize };

					unsigned char varName[] = {
						(hex bytes)
					};
			*/

			std::string hex{ HexDump(path) };

			if (hex == "FAILURE_CONTINUE")
				return FAILURE_CONTINUE;

			outFile.open(headerPath, std::ios::app);

			if (!outFile.is_open())
			{
				SetError("Failed to create header file.");
				return FAILURE_CONTINUE;
			}

			// Write C instructions
			outFile << "static const unsigned int " << varName << "_size{ " << fileSize << " };\n\n";
			outFile << "unsigned char " << varName << "[] = {\n\t";
			outFile << hex;
			outFile << "\n};\n\n\n";
			outFile.close();
		}
	}
	catch (std::exception& e)
	{
		SetError(e.what());
		return FAILURE_CONTINUE;
	}
	catch (...)
	{
		SetError("Exception thrown while attempting to generate header file.");
		return FAILURE_CONTINUE;
	}

	return SUCCESS;
}
unsigned int Loader::BuildImplFile() noexcept
{
	/*	Write C instructions to create
		files in specified location   */

	try
	{
		// Open file and write first instructions
		std::ofstream outFile(appDataPath + "\\impl.cpp", std::ios::out);

		if (!outFile.is_open())
		{
			SetError("Failed to open file when attempting to generate implementation file.");
			return FAILURE_CONTINUE;
		}

		outFile << GetResourceData(LOADER_DATA_0);

		// Write variables
		outFile << "\tpath = R\"(" << runPath << ")\";\n\n";

		for (auto& fileName : fileNames)
			outFile << "\tfileNames.push_back(\"" << fileName << "\");\n";

		outFile << "\n";

		for (auto& varName : varNames)
			outFile << "\tdata.push_back(" << varName << ");\n";

		outFile << "\n";

		for (auto& fileSize : fileSizes)
			outFile << "\tsizes.push_back(" << fileSize << ");\n";

		outFile << "\n";

		// Write remaining instructions and close file
		outFile << GetResourceData(LOADER_DATA_1);
		outFile.close();
	}
	catch (std::exception& e)
	{
		SetError(e.what());
		return FAILURE_CONTINUE;
	}
	catch (...)
	{
		SetError("Exception thrown when attempting to generate implementation file.");
		return FAILURE_CONTINUE;
	}

	return SUCCESS;
}
unsigned int Loader::Compile() noexcept
{
	try
	{
		std::string cmd{ PATH_COMPILER };
		cmd += " " + appDataPath + "\\impl.cpp -o " + exportPath + "\\" + fileNames[0];
		return SpawnProcThread(cmd.c_str());
	}
	catch (std::exception& e)
	{
		SetError(e.what());
	}
	catch (...)
	{
		SetError("Exception thrown when attempting to append output filename to compile command string.");
	}

	return FAILURE_CONTINUE;
}
unsigned int Loader::CleanUp() noexcept
{
	/*	Clear lib paths vector and
		attempt to remove all files
		in %LOCALAPPDATA%\HexLoader   */

	try
	{
		libPaths.clear();
		appDataPath = getenv("LOCALAPPDATA");
		appDataPath += "\\HexLoader";

		for (auto& filePath : std::filesystem::directory_iterator(appDataPath))
			std::filesystem::remove_all(filePath);

		if (!std::filesystem::is_empty(appDataPath))
		{
			SetError("Failed to purge AppData files.");
			return FAILURE_CONTINUE;
		}

		return SUCCESS;
	}
	catch (std::exception& e)
	{
		SetError(e.what());
	}
	catch (...)
	{
		SetError("Exception thrown during cleanup.");
	}

	return FAILURE_CONTINUE;
}

HMODULE GetModule()
{
	HMODULE hModule = NULL;
	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
		(LPCTSTR)GetModule,
		&hModule);

	return hModule;
}
