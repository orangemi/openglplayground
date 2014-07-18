#include "File.h"

File::File() {
}

File::~File() {
}

bool File::readChar(const std::string filename, std::string &data) {

	std::ifstream file;

	char buffer[FILENAME_MAX];
	GetModuleFileNameA(NULL, buffer, FILENAME_MAX);
	char *p = strrchr(buffer, '\\');
	if (p) *p = '\0';
	std::string dir = std::string(buffer);
	file.open(dir + "/" + filename);
	std::cout << "load file: " + dir + "/" + filename << std::endl;
//	file.open(filename);

	if (!file.is_open()) return false;

	while (!file.eof()) {
		std::string line;
		std::getline(file, line);
		data.append(line + "\n");
	}

	file.close();

	return true;

}