#pragma once

#include "cocos2d.h"

class  AppDelegate : private cocos2d::Application
{
private:
	void initOpenGL();
	void initDirector();
	void initMultiResolution();
	void createAndRunScene();

public:
	AppDelegate();
	virtual ~AppDelegate();

	virtual void initGLContextAttrs();
	virtual bool applicationDidFinishLaunching();
	virtual void applicationDidEnterBackground();
	virtual void applicationWillEnterForeground();
};
