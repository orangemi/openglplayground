#pragma once

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

class File {
public:
	File();
	~File();

public:
//	static bool readChar(const char * filename, char ** data);
//	static bool readChar(const char * filename, std::string &data);
	static bool readChar(const std::string filename, std::string &data);
};

