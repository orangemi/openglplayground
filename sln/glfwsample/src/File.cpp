#include "File.h"

File::File() {
}

File::~File() {
}

bool File::readChar(const std::string filename, std::string &data) {

	std::ifstream file;
	file.open(filename);
	if (!file.is_open()) return false;

	while (!file.eof()) {
		std::string line;
		std::getline(file, line);
		data.append(line + "\n");
	}

	file.close();

	return true;

}