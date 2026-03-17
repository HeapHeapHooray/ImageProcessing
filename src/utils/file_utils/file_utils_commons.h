#pragma once
#include <sys\stat.h>
#include "../data.h"
/**
Check if file exists.

@param file_path The Path/Location where the file is.
@return True if file exists or false otherwise.*/
bool file_exists(const char* file_path) {
	struct stat stat_buffer;
	return stat(file_path, &stat_buffer) != -1;
}