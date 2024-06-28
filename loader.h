#pragma once
#include <string>
#include <vector>

#define SUCCESS 0
#define FAILURE_ABORT 1
#define FAILURE_CONTINUE 2

class Loader
{
private:
	std::string binPath,
				runPath;
	std::vector<std::string> libPaths;

public:
	enum PATH_TYPE
	{
		ALL,
		PATH_BIN,
		PATH_LIB,
		PATH_RUN
	};

	Loader()
	:binPath(""), runPath(""){};
	void SetPath(PATH_TYPE, std::string);
	//unsigned int ValidatePath(PATH_TYPE) const;
	std::string GetBinPath() const noexcept { return binPath; };
	std::vector<std::string> GetLibPaths() const noexcept { return libPaths; };
	std::string GetRunPath() const noexcept { return runPath; };
	~Loader() {}
};