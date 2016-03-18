#include "AdmobManager.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS )


// if you want pop a full screen ad, you must call this first.
void AdmobManager::preloadFullScreenAd()
{
	//if( random( 0 , 1 ) == 1 )
}

// this will pop a full screen ad if it was loaded.
void AdmobManager::popUpFullScreenAd()
{
}


#endif