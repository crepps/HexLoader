#include "loader.h"

void Loader::SetPath(PATH_TYPE type, std::string path)
{
	switch (type)
	{
	case PATH_BIN:
		binPath = path;
		break;
	case PATH_LIB:
		libPaths.push_back(path);
		break;
	case PATH_RUN:
		runPath = path;
	}
}
//unsigned int Loader::ValidatePath(PATH_TYPE type) const
//{
//	switch (type)
//	{
//	case PATH_BIN:
//		// If exists, return SUCCESS; else, return PATH_BIN
//		return (unsigned int)type;
//	}
//
//	return FAILURE_CONTINUE;
//}