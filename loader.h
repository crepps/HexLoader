#pragma once
#include <sstream>
#include <vector>
#include <sys/stat.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <Windows.h>
#include <iostream>

#define SUCCESS 0
#define FAILURE_ABORT 1
#define FAILURE_CONTINUE 2
#define BUFFER_SIZE 128

class Loader
{
private:
	std::string binPath,
				runPath,
				error,
				newProcessCmd,
				outputBuffer;

	std::vector<std::string> libPaths;

	bool compilerInstalled,
		compilerCheck,
		bufferLoaded;

	std::mutex outputMutex;
	std::condition_variable waitCondition;

	const char* PATH_COMPILER{ "C:\\ProgramData\\mingw64\\mingw64\\bin\\g++.exe" };

public:
	enum PATH_TYPE
	{
		PATH_ALL,
		PATH_BIN,
		PATH_LIB,
		PATH_RUN
	};

	Loader() noexcept
		:compilerInstalled(false),
		compilerCheck(false),
		bufferLoaded(false),
		runPath("C:\\temp"),
		newProcessCmd("choco install mingw64"),
		outputBuffer("") {};
	void SetError(const std::string& arg) noexcept { error = arg; }
	std::string GetError() const noexcept { return error; }
	void SetPath(PATH_TYPE, const std::string&) noexcept;
	unsigned int ValidatePath(PATH_TYPE) const noexcept;
	std::string GetBinPath() const noexcept { return binPath; };
	std::vector<std::string> GetLibPaths() const noexcept { return libPaths; };
	std::string GetRunPath() const noexcept { return runPath; };
	bool CompilerInstalled() noexcept;
	bool CompilerChecked() const noexcept { return compilerCheck;  }
	unsigned int InstallCompiler() noexcept;
	void SetProcessCmd(const std::string& arg) { newProcessCmd = arg; }
	unsigned int SpawnInstallerThread();
	void LoadBuffer(const std::string&) noexcept;
	const char* OffloadBuffer() noexcept;
	bool GetBufferLoaded() const noexcept { return bufferLoaded; }
	void ClearBuffer() noexcept;
	~Loader() noexcept {}
};