#include "AppDelegate.h"
#include "../../common/Definition.h"
#include "../../scenes/ui/splash/SplashScreenScene.h"

static cocos2d::Size designResolutionSize = cocos2d::Size(SREEEN_RESOLUTION_WIDTH, SREEEN_RESOLUTION_HEIGHT);

AppDelegate::AppDelegate()
{
	// Constructor
}

AppDelegate::~AppDelegate()
{
	// Destructor
}

void AppDelegate::initOpenGL()
{
	auto director = cocos2d::Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
		glview = cocos2d::GLViewImpl::createWithRect("The Hopeful Letter",
			cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
		glview = cocos2d::GLViewImpl::create("The Hopeful Letter");
#endif
		director->setOpenGLView(glview);
	}
}

void AppDelegate::initDirector()
{
	auto director = cocos2d::Director::getInstance();
	director->setAnimationInterval(1.0 / FPS);
}

void AppDelegate::initMultiResolution()
{
	auto director = cocos2d::Director::getInstance();
	auto glview = director->getOpenGLView();

	glview->setDesignResolutionSize(
		designResolutionSize.width,
		designResolutionSize.height,
		ResolutionPolicy::NO_BORDER
	);

	std::vector<std::string> searchPaths;

	cocos2d::Size frameSize = glview->getFrameSize();

	cocos2d::FileUtils::getInstance()->setSearchPaths(searchPaths);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
	return 0; //flag for packages manager
}

void AppDelegate::createAndRunScene()
{
	register_all_packages();

	auto scene = SplashScreenScene::createScene();

	cocos2d::Director::getInstance()->runWithScene(scene);
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
	// set OpenGL context attributes: red,green,blue,alpha,depth,stencil,multisamplesCount
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8, 0 };

	cocos2d::GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
	initOpenGL();
	initDirector();
	initMultiResolution();
	createAndRunScene();

	return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
	cocos2d::Director::getInstance()->stopAnimation();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	cocos2d::Director::getInstance()->startAnimation();
}
