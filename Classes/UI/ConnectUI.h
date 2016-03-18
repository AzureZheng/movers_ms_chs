/*----------------------------
������UI
2016-02-25 by Azure Zheng
------------------------------*/

#ifndef __CONNECT_UI_H__
#define __CONNECT_UI_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "GlobalUtils/SpriteButton.h"

USING_NS_CC;

class ConnectUI : public Layer
{
public:

	virtual bool init();

	CREATE_FUNC(ConnectUI);

	//��ʼ������UI
	void initWithDoublePlayers();

	//��ʼ������UI
	void initWithFourPlayers();

	//�ڼ��������ʾΪ������״̬(0~3)
	void connectPlayer(int playerID);

	//�ڼ��������ʾΪδ����״̬(0~3)
	void disconnectPlayer(int playerID);

	//�ڼ��������ʾΪ�ȴ�����״̬(0~3)
	void waitConnectPlayer(int playerID,bool cancelWait = false);

	//���������ʾΪδ����״̬
	void disconnectAllPlayers();

	//����һ���������ͼ
	ui::Layout * _createConnectPlayerLayout(int playerID);

	//�Ƿ񼤻�������������ʾ
	void activeConnectingListenerAndShow(bool active);
	
	//���ùرհ�ť�ص�
	void setCloseButtonCallback(const std::function<void(Ref*)> & callback);

	//���ÿ�ʼ��Ϸ�Ļص�
	void setStartButtonCallback(const std::function<void(Ref*)> & callback);

	//�����������ӵĻص�
	void setReconnectButtonCallback(const std::function<void(Ref*)> & callback);

	//���ô������������ĺ���(��һ�����������ID���ڶ����������Ƿ�ִ�п�ѭ��������ֵ��-2�������ã�-1��������Ϸ�����������𶯽�ɫ��ID)
	void setTriggerConnectCallback(const std::function<int(int,bool)> & callback);

	//�Ƿ���ʾ���ֲ�
	void setBlackBackVisible(bool visible);

	//��������
	void update(float dt);

	//�������ӵĻص�
	void reconnect();

	//�����
	void shakePlayer(int playerID);

protected:

	//���ֲ�
	ui::Layout * m_blackBack;

	//UI��
	Layer * m_uiLayer;

	//�Ƿ���ʱ�ر�����
	bool m_isPauseConnectListener;

	//�������ͼ����
	Vector<ui::Layout*> m_connectPlayerLayouts;

	//�������������Ľӿں��������ID���Ƿ�ִ�п�ѭ����
	std::function<int(int,bool)> m_triggerConnectCallback;

	//�رհ�ť
	SpriteButton * m_closeButton;

	//�������Ӱ�ť
	SpriteButton * m_reconnectButton;

	//��ʼ��Ϸ��ť
	SpriteButton * m_startButton;

	//�������
	int m_playerCount;

	//�����ӵ��������
	int m_connectedPlayerCount;

};





#endif