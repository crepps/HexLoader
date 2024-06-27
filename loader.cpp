#include "loader.h"

unsigned int Loader::ValidatePath(PATH_TYPE type)
{
	switch (type)
	{
	case PATH_BIN:
		// If exists, return SUCCESS; else, return PATH_BIN
		return (unsigned int)type;
	}

	return FAILURE_CONTINUE;
}