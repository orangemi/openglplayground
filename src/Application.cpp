#include "Application.h"

Application* Application::_currentApp = nullptr;

Application::Application() {
	_isRunning = false;
	_name = "Sample";
	_isShowFPS = false;
}

Application::~Application() {
}

bool Application::isRunning() {
	return _isRunning;
}

void Application::onErrorCallback(int error, const char * desc) {
	_currentApp->_isRunning = false;
	std::cout << "GLFW Error: " << desc << std::endl;
}

void Application::onKeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods) {
	std::cout << "input key: " << key << " , scancode: " << scancode << " , action: " << action << " , mods: " << mods << std::endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
		_currentApp->_isRunning = false;
	}
}

void Application::onMouseCallback(GLFWwindow * window, int button, int action, int mods) {
	std::cout << "mouse button: " << button << " , action: " << action << " , mods: " << mods << std::endl;
}

void Application::onMouseScrollCallback(GLFWwindow * window, double x, double y) {
	std::cout << "mouse wheel x: " << x << " , y: " << y << std::endl;
}

void Application::startup() {

}

void Application::render(double time) {

}

void Application::end() {

}

void Application::start() {
	Application::_currentApp = this;
	glfwSetErrorCallback(onErrorCallback);
	if (!glfwInit()) return;
	_window = glfwCreateWindow(640, 480, this->_name, NULL, NULL);
	if (!_window) {
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(_window);
	glfwSetKeyCallback(_window, onKeyCallback);
	glfwSetMouseButtonCallback(_window, onMouseCallback);
	glfwSetScrollCallback(_window, onMouseScrollCallback);

	//init fps;
	_lastRenderTime = 0.0;
	_fpsCount = 0;

	startup();

	_isRunning = true;
	do {
		render(glfwGetTime());
		showFPS();

		glfwSwapBuffers(_window);
		glfwPollEvents();
	} while (_isRunning && !glfwWindowShouldClose(_window));

	end();
	glfwTerminate();
}

void Application::showFPS() {
	if (!_isShowFPS) return;
	_fpsCount++;
	if (glfwGetTime() - _lastRenderTime > 1.0) {
		double fps = _fpsCount / (glfwGetTime() - _lastRenderTime);
		std::cout << "fps: " << fps << std::endl;
		_lastRenderTime = glfwGetTime();
		_fpsCount = 0;
	}
}

bool Application::loadVertexSharderSource(const std::string shaderName, GLuint &shader) {
	std::string source;
	File::readChar(shaderName, source);
	const GLchar * data[] = { source.c_str() };
	shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shader, 1, data, NULL);
	glCompileShader(shader);
	return true;
}

bool Application::loadFragSharderSource(const std::string shaderName, GLuint &shader) {
	std::string source;
	File::readChar(shaderName, source);
	const GLchar * data[] = { source.c_str() };
	shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(shader, 1, data, NULL);
	glCompileShader(shader);
	return true;
}

bool Application::compileShader(GLuint vertexShader, GLuint fragShader, GLuint &program) {
	GLint compileStatus;
	char logMsg[1024];

	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus == GL_FALSE) {
		glGetShaderInfoLog(vertexShader, 1024, NULL, logMsg);
		std::cout << "Fail to compile with the following error: " << logMsg << std::endl;
	}

	glCompileShader(fragShader);

	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus == GL_FALSE) {
		glGetShaderInfoLog(fragShader, 1024, NULL, logMsg);
		std::cout << "Fail to compile with the following error: " << logMsg << std::endl;
	}

	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragShader);
	glLinkProgram(program);

	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);

	return true;
}

bool Application::loadPngImg(const std::string filename, int &outWidth, int &outHeight, bool &outHasAlpha, GLubyte **outData) {
	png_structp png_ptr;
	png_infop info_ptr;
	unsigned int sig_read = 0;
	int color_type, interlace_type;
	FILE *fp;

	char buffer[FILENAME_MAX];
	GetModuleFileNameA(NULL, buffer, FILENAME_MAX);
	char *p = strrchr(buffer, '\\');
	if (p) *p = '\0';
	std::string dir = std::string(buffer);

	if ((fp = fopen((dir + "/" + filename).c_str(), "rb")) == NULL)
//	if ((fp = fopen(filename.c_str(), "rb")) == NULL)
		return false;

	/* Create and initialize the png_struct
	* with the desired error handler
	* functions.  If you want to use the
	* default stderr and longjump method,
	* you can supply NULL for the last
	* three parameters.  We also supply the
	* the compiler header file version, so
	* that we know if the application
	* was compiled with a compatible version
	* of the library.  REQUIRED
	*/
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
		NULL, NULL, NULL);

	if (png_ptr == NULL) {
		fclose(fp);
		return false;
	}

	/* Allocate/initialize the memory
	* for image information.  REQUIRED. */
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		fclose(fp);
		png_destroy_read_struct(&png_ptr, NULL, NULL);
		return false;
	}

	/* Set error handling if you are
	* using the setjmp/longjmp method
	* (this is the normal method of
	* doing things with libpng).
	* REQUIRED unless you  set up
	* your own error handlers in
	* the png_create_read_struct()
	* earlier.
	*/
	if (setjmp(png_jmpbuf(png_ptr))) {
		/* Free all of the memory associated
		* with the png_ptr and info_ptr */
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		fclose(fp);
		/* If we get here, we had a
		* problem reading the file */
		return false;
	}

	/* Set up the output control if
	* you are using standard C streams */
	png_init_io(png_ptr, fp);

	/* If we have already
	* read some of the signature */
	png_set_sig_bytes(png_ptr, sig_read);

	/*
	* If you have enough memory to read
	* in the entire image at once, and
	* you need to specify only
	* transforms that can be controlled
	* with one of the PNG_TRANSFORM_*
	* bits (this presently excludes
	* dithering, filling, setting
	* background, and doing gamma
	* adjustment), then you can read the
	* entire image (including pixels)
	* into the info structure with this
	* call
	*
	* PNG_TRANSFORM_STRIP_16 |
	* PNG_TRANSFORM_PACKING  forces 8 bit
	* PNG_TRANSFORM_EXPAND forces to
	*  expand a palette into RGB
	*/
	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);

	png_uint_32 width, height;
	int bit_depth;
	png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
		&interlace_type, NULL, NULL);
	outWidth = width;
	outHeight = height;

	//Getting number of channels from the image
	png_byte channels = png_get_channels(png_ptr, info_ptr);

	if (channels == 4) outHasAlpha = true;
	else outHasAlpha = false;

	unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);
	*outData = (unsigned char*)malloc(row_bytes * outHeight);

	png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);

	for (int i = 0; i < outHeight; i++) {
		// note that png is ordered top to
		// bottom, but OpenGL expect it bottom to top
		// so the order or swapped
		memcpy(*outData + (row_bytes * (outHeight - 1 - i)), row_pointers[i], row_bytes);
	}

	/* Clean up after the read,
	* and free any memory allocated */
	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

	/* Close the file */
	fclose(fp);

	/* That's it */
	return true;
}

bool Application::loadImgTexture(int width, int height, bool hasAlpha, GLubyte *imgData, GLuint &texture) {

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		hasAlpha ? GL_RGBA : GL_RGB,
		width,
		height,
		0,
		hasAlpha ? GL_RGBA : GL_RGB,
		GL_UNSIGNED_BYTE,
		imgData);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	return true;
}
