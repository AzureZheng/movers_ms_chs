/****************************************
���鰴��
2016-01-13 by Azure Zheng
*****************************************/


#ifndef __SPRITE_BUTTON_H__
#define __SPRITE_BUTTON_H__


#include "cocos2d.h"

class SpriteButton : public cocos2d::Sprite
{
public:

	//�����Ƴ�����֡�������
	virtual ~SpriteButton();

	//����ʵ��
	CREATE_FUNC(SpriteButton);

	//����������ʵ��
	static SpriteButton * create(const std::string & normalSpriteFrameName, const std::string & pressSpriteFrameName = "", const std::string & disabledSpriteFrameName = "");
	static SpriteButton * create(cocos2d::SpriteFrame * normalSpriteFrame, cocos2d::SpriteFrame * pressSpriteFrame = nullptr, cocos2d::SpriteFrame * disabledSpriteFrame = nullptr);

	//�������а�ť����״̬
	static void setAllButtonsMutexStatus(bool isEnabled);

	//ת��������״̬
	void switchToPress();

	//ת��������״̬
	void switchToNormal();

	//ת��������״̬
	void switchToDisabled();

	//���ÿ���״̬
	void setEnabled(bool enabled);

	//���ؿ���״̬
	bool isEnabled();

	//���ûص�����
	void setCallback(const std::function<void(cocos2d::Ref*)> callback);

	//���øհ���ʱ�ص�����
	void setCallbackTouchBegan(const std::function<void(cocos2d::Ref*)> callback);

	//���ý���ʱ�Ļص�����
	void setCallbackDisabled(const std::function<void(cocos2d::Ref*)> callback);

	//���ػص�����
	const std::function<void(cocos2d::Ref*)> & getCallback() const;

	//��������״̬����֡
	void setNormalSpriteFrame(cocos2d::SpriteFrame * sf);

	//���ð���״̬����֡
	void setPressSpriteFrame(cocos2d::SpriteFrame * sf);

	//���ý���״̬����֡
	void setDisabledSpriteFrame(cocos2d::SpriteFrame * sf);

	//���ô�������
	void setSwallowTouches(bool needSwallow);

	//����ȡ��
	void touchCancel();

	//�˳�ʱ�Ƴ�������
	virtual void onExit();

protected:

	//��ʼ��(�����ֶ�����)
	virtual bool init();

	//��������������
	void _setupTouchListener();

	//����Ƿ񸸽ڵ�ɼ�
	bool _isAncensterEnabled(Node * node);

	//-------------------------------------------------------------------

	//����״̬
	static bool m_mutexStatus;

	//��ǰ״̬(0:������1:���£�2:���ã�3:����ȡ��)
	short m_status;

	//����������
	cocos2d::EventListenerTouchOneByOne * m_touchListener;

	//����״̬����֡
	cocos2d::SpriteFrame * m_normalSpriteFrame;

	//����״̬����֡
	cocos2d::SpriteFrame * m_pressSpriteFrame;

	//����״̬����֡
	cocos2d::SpriteFrame * m_disabledSpriteFrame;

	//���»ص�����
	std::function<void(cocos2d::Ref*)> m_callback;

	//�հ�ʱ�ص�����
	std::function<void(cocos2d::Ref*)> m_touchBeganCallback;

	//����ʱ�ص�����
	std::function<void(cocos2d::Ref*)> m_disabledCallback;

	//����״̬
	bool m_isEnabled;

	//����״̬
	float m_scaledRateX;
	float m_scaledRateY;

	//��ʼ����״̬
	bool m_startToBeTouched;
};

















#endif
