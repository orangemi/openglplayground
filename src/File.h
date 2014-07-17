#ifndef FILE_H_
#define FILE_H_
#include "include.h"

class File {
public:
	File();
	~File();

public:
//	static bool readChar(const char * filename, char ** data);
//	static bool readChar(const char * filename, std::string &data);
	static bool readChar(const std::string filename, std::string &data);
};

#endif // FILE_H_