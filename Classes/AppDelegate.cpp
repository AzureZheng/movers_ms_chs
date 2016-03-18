#include "AppDelegate.h"
#include "Scene/OpeningScene.h"
#include "SimpleAudioEngine.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
#include "MobClickCpp.h"
#endif


USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
	MOBCLICKCPP_START_WITH_APPKEY_AND_CHANNEL("56c68b24e0f55aeef5000a04", "MiniStation");
#endif

    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();

	if (!glview)
	{
		glview = GLViewImpl::create("Trick Rabbit");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
		glview->setFrameSize(1500, 844);
#endif
		director->setOpenGLView(glview);
	}

	glview->setDesignResolutionSize(1920, 1080, ResolutionPolicy::EXACT_FIT);

	Texture2D::PVRImagesHavePremultipliedAlpha(true);
	Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA4444);

    // turn on display FPS
    //director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
	auto scene = OpeningScene::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
	umeng::MobClickCpp::applicationDidEnterBackground();
#endif
	
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();

	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("BackgroundPause");
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
	umeng::MobClickCpp::applicationWillEnterForeground();
#endif

    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
