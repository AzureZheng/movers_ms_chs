#ifndef  _VUNGLE_MANAGER_H_
#define  _VUNGLE_MANAGER_H_

#include "cocos2d.h"
USING_NS_CC;


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )

class VideoManager
{
public:

	static bool isAdPlayable(){ return true; }

	static bool isAdPlayedCompletely(){ return true; }

	static bool isVideoPlaying(){ return false; }

	static void tryPlayVideoAd(){}
};


#else

class VideoManager
{
public:

	static bool isAdPlayable();

	static bool isAdPlayedCompletely();

	static bool isVideoPlaying();

	static void tryPlayVideoAd();
};

#endif

#endif // _VUNGLE_MANAGER_H_ 

