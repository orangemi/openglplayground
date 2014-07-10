#include "File.h"

File::File() {
}

File::~File() {
}

bool File::readChar(char * filename, char * data) {
	FILE * fp;
	fopen(filename);
	return true;
}