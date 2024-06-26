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

	case PATH_RUN:
		if (stat(runPath.c_str(), &statInfo) != 0 || runPath == "")
			return (unsigned int)PATH_RUN;
	}

	return SUCCESS;
}
bool Loader::CompilerInstalled() noexcept
{
	struct stat statInfo;

	if (stat(PATH_COMPILER, &statInfo) == 0)
		compilerInstalled = true;

	compilerCheck = true;

	return compilerInstalled;
}
unsigned int Loader::InstallCompiler() noexcept
{
	// Redirect process's stderr to stdout stream
	std::string command(newProcessCmd);
	command += " 2>&1";

	// Open pipe for reading, execute command
	FILE* pipe;
	try
	{
		pipe = _popen(command.c_str(), "r");
	}
	catch (...)
	{
		LoadBuffer("Failed: _popen threw an exception when attempting to install compiler.");
		return FAILURE_CONTINUE;
	}
	if (!pipe)
	{
		LoadBuffer("Failed to open pipe when attempting to install compiler.");
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
		SetError("Failed to read from pipe when attempting to install compiler.");
		return FAILURE_CONTINUE;
	}

	return SUCCESS;
}
void Loader::LoadBuffer(const std::string& arg) noexcept
{
	/*	Block until output buffer unlocked,
		lock buffer, write data, unlock		*/ 

	{
		std::lock_guard<std::mutex> lock(outputMutex);
		outputBuffer += arg;
	}

	bufferLoaded = true;

	// Sleep until buffer is emptied by client
	while (bufferLoaded)
		Sleep(10);
}
const char* Loader::OffloadBuffer() noexcept
{
	/*	Block until output buffer unlocked,
		lock buffer, return data, unlock	*/

	std::unique_lock<std::mutex> lock(outputMutex);
	return outputBuffer.c_str();
}
void Loader::ClearBuffer() noexcept
{
	outputBuffer.clear();
	outputBuffer = "";
	bufferLoaded = false;
}
unsigned int Loader::SpawnInstallerThread()
{
	try
	{
		std::thread installerThread(&Loader::InstallCompiler, this);
		installerThread.detach();
	}
	catch (std::exception& e)
	{
		SetError(e.what());
		return EXIT_FAILURE;
	}
	catch (...)
	{
		SetError("Exception thrown when attempting to spawn compiler installation thread.");
	}

	return SUCCESS;
}