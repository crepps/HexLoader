#pragma once

#include <sstream>
#include <vector>
#include <sys/stat.h>
#include <thread>
#include <mutex>
#include <Windows.h>
#include <iostream>
#include <ShlObj.h>
#include <filesystem>
#include <fstream>

// Return codes
#define SUCCESS 0
#define FAILURE_ABORT 1
#define FAILURE_CONTINUE 2

// Console output related
#define BUFFER_SIZE 128
#define DELAY_OUTPUT_LONG 100
#define DELAY_OUTPUT_SHORT 5

class Loader
{
private:
	unsigned int outputDelay;

	std::string binPath,
				runPath,
				error,
				newProcessCmd,
				outputBuffer,
				appDataPath,
				loader_impl_0,
				loader_impl_1;

	std::vector<std::string> libPaths,
		fileNames,
		varNames;

	std::vector<uint64_t> fileSizes;
		
	std::atomic<bool> bufferLoaded,
					reading;

	std::mutex outputMutex;

	const char *PATH_COMPILER{ "C:\\ProgramData\\mingw64\\mingw64\\bin\\g++.exe" },
			   *PATH_CHOCO{ "C:\\ProgramData\\chocolatey" };

public:
	enum PATH_TYPE
	{
		PATH_ALL,
		PATH_BIN,
		PATH_LIB,
		PATH_RUN
	};

	Loader() noexcept;
	inline void SetError(const std::string& arg) noexcept { error = arg; }
	inline std::string GetError() const noexcept { return error; }
	void SetPath(PATH_TYPE, const std::string&) noexcept;
	unsigned int ValidatePath(PATH_TYPE) const noexcept;
	inline std::string GetBinPath() const noexcept { return binPath; };
	inline std::vector<std::string> GetLibPaths() const noexcept { return libPaths; };
	inline std::string GetRunPath() const noexcept { return runPath; };
	bool CompilerInstalled() const noexcept;
	unsigned int SpawnProcThread(const std::string&) noexcept;
	unsigned int Command(const std::string&) noexcept;
	void LoadBuffer(const std::string&) noexcept;
	inline bool GetBufferLoaded() const noexcept { return bufferLoaded; }
	const char* OffloadBuffer() noexcept;
	void ClearBuffer() noexcept;
	inline bool Reading() const noexcept { return reading; }
	bool ChocoInstalled() const noexcept;
	inline void DelayOutput(unsigned int arg) noexcept { outputDelay = arg; }
	bool CheckAppData() noexcept;
	std::string HexDump(const std::string&) noexcept;
	unsigned int BuildHeader() noexcept;
	unsigned int BuildImplFile() noexcept;
	unsigned int Compile() noexcept;
	~Loader() noexcept {}
};