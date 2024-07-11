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
unsigned int Loader::Command(const std::string& arg) noexcept
{
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
		Sleep(100);
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
		return EXIT_FAILURE;
	}
	catch (...)
	{
		SetError("Exception thrown when attempting to spawn process thread.");
	}

	return SUCCESS;
}