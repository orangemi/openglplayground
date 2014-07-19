#ifndef APPLICATION_H_
#define APPLICATION_H_
#include "include.h"

class Application {
public:

	Application(void);
	~Application(void);

	void start();
	bool isRunning();

	virtual void startup();
	virtual void end();
	virtual void render(double time);

	virtual void Application::onError(int error, const char * desc);
	virtual void onKeyDown(int keycode, int mods);
	virtual void onKeyUp(int keycode, int mods);
	virtual void onKeyPress(int keycode, int mods);
	virtual void onMouseDown(int x, int y, int button, int mods);
	virtual void onMouseUp(int x, int y, int button, int mods);
	virtual void onMouseClick(int x, int y, int button, int mods);
	virtual void onMouseScroll(double x, double y);
	virtual void onMouseMove(double x, double y);

	static Application* _currentApp;
	static void onErrorCallback(int error, const char * desc);
	static void onKeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods);
	static void onMouseCallback(GLFWwindow * window, int button, int action, int mods);
	static void onMouseScrollCallback(GLFWwindow * window, double x, double y);
	static void onMouseMoveCallback(GLFWwindow * window, double x, double y);

protected:
	bool loadVertexSharderSource(const std::string shaderName, GLuint &shader);
	bool loadFragSharderSource(const std::string shaderName, GLuint &shader);
	bool compileShader(GLuint vertexShader, GLuint fragShader, GLuint &program);
	bool loadPngImg(const std::string filename, int &outWidth, int &outHeight, bool &outHasAlpha, GLubyte **outData);
	bool loadImgTexture(int width, int height, bool hasAlpha, GLubyte *imgData, GLuint &texture);

protected:
	bool _isRunning;
	char* _name;
	int _width;
	int _height;
	GLFWwindow* _window;
	bool _isShowFPS;

private:
	void showFPS();

private:
	double _lastRenderTime;
	int _fpsCount;
	bool _isShowConsole;

};

#endif // APPCIATION_H_