#include "FlurryManager.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )

#include "platform/android/jni/JniHelper.h" //vem do projeto principal - pasta cocos2dx  
 
#include <jni.h>  

//using namespace cocos2d;

#define CLASS_PATH "org.cocos2dx.cpp/AppActivity"


extern "C"  
{
	void logFlurryJNI( const char * _text ){
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, CLASS_PATH  
                        ,"logFlurryJNI"  
                        ,"(Ljava/lang/String;)V"))  
        {  

            jstring jmsg = t.env->NewStringUTF( _text );
            t.env->CallStaticVoidMethod(t.classID , t.methodID , jmsg );  
        }  
    }  

}

void FlurryManager::logFlurry( std::string log_text )
{
	logFlurryJNI( log_text.c_str() );
}

#endif
