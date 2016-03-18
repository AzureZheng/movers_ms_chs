#include "AdmobManager.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )

#include "platform/android/jni/JniHelper.h" //vem do projeto principal - pasta cocos2dx  
 
#include <jni.h>  

//using namespace cocos2d;

#define CLASS_PATH "org.cocos2dx.cpp/AppActivity"


extern "C"  
{
	void showAdmobJNI(){  
        JniMethodInfo t;  
        if (JniHelper::getStaticMethodInfo(t, CLASS_PATH  
                        ,"showAdmobJNI"  
                        ,"()V"))  
        {  
            t.env->CallStaticVoidMethod(t.classID,t.methodID);  
        }  
    }  

	void newAdmobJNI(){  
        JniMethodInfo t;  
        if (JniHelper::getStaticMethodInfo(t, CLASS_PATH  
                        ,"newAdmobJNI"  
                        ,"()V"))  
        {  
            t.env->CallStaticVoidMethod(t.classID,t.methodID);  
        }  
    }

}

// if you want pop a full screen ad, you must call this first.
void AdmobManager::preloadFullScreenAd()
{
	newAdmobJNI();
}

// this will pop a full screen ad if it was loaded.
void AdmobManager::popUpFullScreenAd()
{
	showAdmobJNI();
}


#endif