#include "File.h"

File::File() {
}

File::~File() {
}

bool File::readChar(const std::string filename, std::string &data) {

	char buffer[FILENAME_MAX];
	GetModuleFileName(NULL, buffer, FILENAME_MAX);
	char *p = strrchr(buffer, '//');
	*p = '\0';
	std::string dir = std::string(buffer);
	//GetCurrentDir(buffer, FILENAME_MAX);
	//std::string dir = std::string(buffer);
std::cout << dir << std::endl << std::endl;


	std::ifstream file;
	file.open(dir + "/" + filename);

std::cout << "load file: " + dir + "/" + filename << std::endl;

	if (!file.is_open()) return false;

	while (!file.eof()) {
		std::string line;
		std::getline(file, line);
		data.append(line + "\n");
	}

	file.close();

	return true;

}