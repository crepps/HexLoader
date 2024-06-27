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
		PATH_EXPORT
	};

	Loader() {};
	unsigned int ValidatePath(PATH_TYPE);
	~Loader() {}
};