/****************************************
ȫ���趨
2016-01-11 by Azure Zheng
*****************************************/

#ifndef __GLOBAL_SETTING_H__
#define __GLOBAL_SETTING_H__


//------------------------------------------------ ͨ���趨 -------------------------------------------------

//��Ļ��С
#define GS_VISIBLE_SIZE (Director::getInstance()->getVisibleSize())

//��Ļ�е�
#define GS_SCREEN_MID_POINT cocos2d::Vec2(GS_VISIBLE_SIZE.width/2,GS_VISIBLE_SIZE.height/2);

//������Ч
#define PLAY_EFFECT(file) CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(file);



#endif
