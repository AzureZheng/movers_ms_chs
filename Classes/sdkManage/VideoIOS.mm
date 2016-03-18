#include "VideoManager.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS )


bool VideoManager::isAdPlayable()
{
	return true;
}

bool VideoManager::isAdPlayedCompletely()
{
	return true;
}

void VideoManager::tryPlayVideoAd()
{

}

bool VideoManager::isVideoPlaying()
{
	return true;
}


#endif