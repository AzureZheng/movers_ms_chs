LOCAL_PATH := $(call my-dir)

# include $(CLEAR_VARS)

# LOCAL_MODULE := libuipc_loader
# LOCAL_SRC_FILES := libuipc_loader.so

# include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/Info/GameInfo.cpp \
                   ../../Classes/Objects/Building.cpp \
                   ../../Classes/Objects/BuildingStage.cpp \
                   ../../Classes/Objects/MoversTruck.cpp \
                   ../../Classes/Objects/RabbitHamal.cpp \
                   ../../Classes/Objects/StageSide.cpp \
                   ../../Classes/Objects/ThrowableObject.cpp \
                   ../../Classes/Scene/BuildingScene.cpp \
                   ../../Classes/Scene/MoversHomeScene.cpp \
                   ../../Classes/Scene/OpeningScene.cpp \
                   ../../Classes/Scene/PlayerLayer.cpp \
                   ../../Classes/sdkManage/AdmobAndroid.cpp \
                   ../../Classes/sdkManage/AndroidManager.cpp \
                   ../../Classes/sdkManage/FlurryAndroid.cpp \
                   ../../Classes/sdkManage/MoneyAndroid.cpp \
                   ../../Classes/sdkManage/VideoAndroid.cpp \
                   ../../Classes/UI/MoverGameUI.cpp \
				   ../../Classes/GlobalUtils/SpriteButton.cpp \
				   ../../Classes/GlobalUtils/UIPC_Loader.cpp \
                   ../../Classes/UI/PushButton.cpp \
				   ../../Classes/UI/ConnectUI.cpp \
				   ../../Classes/UI/HPBar.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END

LOCAL_STATIC_LIBRARIES := cocos2dx_static
LOCAL_SHARED_LIBRARIES := mobclickcpp_shared
# LOCAL_SHARED_LIBRARIES += libuipc_loader

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,libmobclickcpp)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
