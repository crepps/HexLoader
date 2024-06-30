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
unsigned int Loader::InstallCompiler(std::string* pOutput) noexcept
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
		*pOutput += "Failed: _popen threw an exception when attempting to install compiler.";
		return FAILURE_CONTINUE;
	}
	if (!pipe)
	{
		*pOutput += "Failed to open pipe when attempting to install compiler.";
		return FAILURE_CONTINUE;
	}

	// Feed output to caller
	try
	{
		char buffer[BUFFER_SIZE];
		while (fgets(buffer, BUFFER_SIZE, pipe) != NULL)
			*pOutput += buffer;

		_pclose(pipe);
	}
	catch (...)
	{
		*pOutput += "Failed to read from pipe when attempting to install compiler.";
		return FAILURE_CONTINUE;
	}

	return SUCCESS;
}