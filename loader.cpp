#include "loader.h"

void Loader::SetPath(PATH_TYPE type, std::string path) noexcept
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
	case PATH_BIN:
		if (stat(binPath.c_str(), &statInfo) != 0)
			return (unsigned int)type;
		break;
		
	case PATH_LIB:
		for (auto& path : libPaths)
		{
			if (stat(path.c_str(), &statInfo) != 0)
				return (unsigned int)type;
		}
		break;

	case PATH_RUN:
		if (stat(runPath.c_str(), &statInfo) != 0)
			return (unsigned int)type;
	}

	return SUCCESS;
}