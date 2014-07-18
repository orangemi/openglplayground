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
	static void onErrorCallback(int error, const char * desc);
	static void onKeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods);
	static void onMouseCallback(GLFWwindow * window, int button, int action, int mods);
	static void Application::onMouseScrollCallback(GLFWwindow * window, double x, double y);
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
	bool _isShowFPS;

private:
	void showFPS();

private:
	double _lastRenderTime;
	int _fpsCount;

};

#endif // APPCIATION_H_