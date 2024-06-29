#pragma once
#include <string>
#include <vector>
#include <sys/stat.h>

#define SUCCESS 0
#define FAILURE_ABORT 1
#define FAILURE_CONTINUE 2

class Loader
{
private:
	std::string binPath,
				runPath,
				error;
	std::vector<std::string> libPaths;
	bool compilerInstalled,
		compilerCheck;

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
		:compilerInstalled(false), compilerCheck(false) {};
	void SetError(std::string arg) noexcept { error = arg; }
	std::string GetError() const noexcept { return error; }
	void SetPath(PATH_TYPE, std::string) noexcept;
	unsigned int ValidatePath(PATH_TYPE) const noexcept;
	std::string GetBinPath() const noexcept { return binPath; };
	std::vector<std::string> GetLibPaths() const noexcept { return libPaths; };
	std::string GetRunPath() const noexcept { return runPath; };
	bool CompilerInstalled() noexcept;
	bool CompilerChecked() const noexcept { return compilerCheck;  }
	~Loader() noexcept {}
};