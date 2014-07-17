
#ifndef INCLUDE_H_
#define INCLUDE_H_

//system file include
#include <fstream>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>

//platform file include
#ifdef WIN32
	#include <direct.h>
	#include <windows.h>
	#define GetCurrentDir _getcwd
#else
	#include <unistd.h>
	#define GetCurrentDir getcwd
#endif

//Helper file include
#include <math.h>
#include <GLFW/glfw3.h>
#include <gl/glext.h>
#include <png.h>
#include <glm/glm.hpp>

//User file include
#include "File.h"

#endif //INCLUDE_H_