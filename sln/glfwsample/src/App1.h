#pragma once
#include "Application.h"

class AppDeletgate : public Application {
public:
	AppDeletgate();
	~AppDeletgate();
	void startup();
	void render(double time);
};

