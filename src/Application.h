#ifndef APPLICATION_H_
#define APPLICATION_H_
#include "include.h"

class Application {
public:
	static Application* _currentApp;
	Application(void);
	~Application(void);
	virtual void start();
	virtual void startup();
	virtual void end();
	virtual void render(double time);
	static void onErrorCallback(int error, const char* desc);
	static void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	bool isRunning();

protected:
	bool loadVertexSharderSource(const std::string shaderName, GLuint &shader);
	bool loadFragSharderSource(const std::string shaderName, GLuint &shader);
	bool compileShader(GLuint vertexShader, GLuint fragShader, GLuint &program);
	bool loadPngImg(const std::string filename, int &outWidth, int &outHeight, bool &outHasAlpha, GLubyte **outData);
	bool loadImgTexture(int width, int height, bool hasAlpha, GLubyte *imgData, GLuint &texture);

protected:
	bool _isRunning;
	char* _name;
	GLFWwindow* _window;

};

#endif // APPCIATION_H_