#ifndef  _ANDROID_MANAGER_H_
#define  _ANDROID_MANAGER_H_

#include "cocos2d.h"
USING_NS_CC;


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )

class AndroidManager
{
public:

	static bool systemVersionCodeUpon5();
};


#endif

#endif // _ANDROID_MANAGER_H_

