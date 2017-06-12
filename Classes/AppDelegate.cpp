#include "AppDelegate.h"
//#include "../cocos2d/cocos/audio/include/SimpleAudioEngine.h"
#include "Scene/SceneLoader.hpp"

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size( 1080, 1920 );

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate() 
{
}

void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    GLView::setGLContextAttrs(glContextAttrs);
}

static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {

    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("Gekiyokekun", Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("Gekiyokekun");
#endif
        director->setOpenGLView(glview);
    }

    director->setDisplayStats( true );
    director->setAnimationInterval(1.0 / 60);

    register_all_packages();

    User::SceneLoader::createSystemAppDelegate();
  
    return true;
}

void AppDelegate::applicationDidEnterBackground()
{
//    Director::getInstance()->stopAnimation();
//    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
//    Director::getInstance()->startAnimation();
//    CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
