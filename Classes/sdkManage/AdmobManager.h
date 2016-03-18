#ifndef  _ADMOB_MANAGER_H_
#define  _ADMOB_MANAGER_H_

#include "cocos2d.h"
USING_NS_CC;


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )

class AdmobManager
{
public:
	// if you want pop a full screen ad, you must call this first.
	static void preloadFullScreenAd(){}

	// this will pop a full screen ad if it was loaded.
	static void popUpFullScreenAd(){}
};


#else

class AdmobManager
{
public:
	// if you want pop a full screen ad, you must call this first.
	static void preloadFullScreenAd();

	// this will pop a full screen ad if it was loaded.
	static void popUpFullScreenAd();
};

#endif

#endif // _ADMOB_MANAGER_H_

