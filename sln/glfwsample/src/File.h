#pragma once

#include <stdio.h>

class File {
public:
	File();
	~File();

public:
	static bool readChar(char * filename, char * data);
};

