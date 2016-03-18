#ifndef  _FLURRY_MANAGER_H_
#define  _FLURRY_MANAGER_H_

#include "cocos2d.h"
USING_NS_CC;


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )

class FlurryManager
{
public:
	static void logFlurry( std::string log_text ){ cocos2d::log( log_text.c_str() ); }
};


#else

class FlurryManager
{
public:
	static void logFlurry( std::string log_text );
};

#endif

#endif // _FLURRY_MANAGER_H_

