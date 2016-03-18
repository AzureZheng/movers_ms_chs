#include "VideoManager.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )

#include "platform/android/jni/JniHelper.h" //vem do projeto principal - pasta cocos2dx  
 
#include <jni.h>  

//using namespace cocos2d;

#define CLASS_PATH "org.cocos2dx.cpp/AppActivity"


extern "C"  
{
	void playVodeoJNI(){  
        JniMethodInfo t;  
        if (JniHelper::getStaticMethodInfo(t, CLASS_PATH  
                        ,"playVideoJNI"  
                        ,"()V"))  
        {  
            t.env->CallStaticVoidMethod(t.classID,t.methodID);  
        }  
    }  

	bool isVideoPlayableJNI(){
		bool _result = false;
        JniMethodInfo t;  
        if (JniHelper::getStaticMethodInfo(t, CLASS_PATH  
                        ,"isVideoPlayableJNI"  
                        ,"()Z"))  
        {  
            jboolean _RESULT = t.env->CallStaticBooleanMethod(t.classID,t.methodID);
			if( _RESULT == JNI_TRUE ) _result = true;
        }

		return _result;
    }

	bool isVideoCompletedJNI(){
		bool _result = false;
        JniMethodInfo t;  
        if (JniHelper::getStaticMethodInfo(t, CLASS_PATH  
                        ,"isVideoCompletlyJNI"  
                        ,"()Z"))  
        {  
            jboolean _RESULT = t.env->CallStaticBooleanMethod(t.classID,t.methodID);
			if( _RESULT == JNI_TRUE ) _result = true;
        }

		return _result;
    }

	bool isVideoPlayingJNI(){
		bool _result = false;
        JniMethodInfo t;  
        if (JniHelper::getStaticMethodInfo(t, CLASS_PATH  
                        ,"isVideoPlayingJNI"  
                        ,"()Z"))  
        {  
            jboolean _RESULT = t.env->CallStaticBooleanMethod(t.classID,t.methodID);
			if( _RESULT == JNI_TRUE ) _result = true;
        }

		return _result;
    }

}

bool VideoManager::isAdPlayable()
{
	return isVideoPlayableJNI();
}

bool VideoManager::isAdPlayedCompletely()
{
	return isVideoCompletedJNI();
}

void VideoManager::tryPlayVideoAd()
{
	playVodeoJNI();
}

bool VideoManager::isVideoPlaying()
{
	return isVideoPlayingJNI();
}


#endif
