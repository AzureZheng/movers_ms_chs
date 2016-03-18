/*----------------------------
连接用UI
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

	//初始化两人UI
	void initWithDoublePlayers();

	//初始化四人UI
	void initWithFourPlayers();

	//第几个玩家显示为已连接状态(0~3)
	void connectPlayer(int playerID);

	//第几个玩家显示为未连接状态(0~3)
	void disconnectPlayer(int playerID);

	//第几个玩家显示为等待连接状态(0~3)
	void waitConnectPlayer(int playerID,bool cancelWait = false);

	//所有玩家显示为未连接状态
	void disconnectAllPlayers();

	//创建一个玩家连接图
	ui::Layout * _createConnectPlayerLayout(int playerID);

	//是否激活连接侦听与显示
	void activeConnectingListenerAndShow(bool active);
	
	//设置关闭按钮回调
	void setCloseButtonCallback(const std::function<void(Ref*)> & callback);

	//设置开始游戏的回调
	void setStartButtonCallback(const std::function<void(Ref*)> & callback);

	//设置重新连接的回调
	void setReconnectButtonCallback(const std::function<void(Ref*)> & callback);

	//设置触发连接侦听的函数(第一个参数：玩家ID；第二个参数：是否执行空循环；返回值：-2：无作用；-1：加入游戏；其他：需震动角色的ID)
	void setTriggerConnectCallback(const std::function<int(int,bool)> & callback);

	//是否显示遮罩层
	void setBlackBackVisible(bool visible);

	//连接侦听
	void update(float dt);

	//重新连接的回调
	void reconnect();

	//震动玩家
	void shakePlayer(int playerID);

protected:

	//遮罩层
	ui::Layout * m_blackBack;

	//UI层
	Layer * m_uiLayer;

	//是否暂时关闭侦听
	bool m_isPauseConnectListener;

	//玩家连接图集合
	Vector<ui::Layout*> m_connectPlayerLayouts;

	//触发连接侦听的接口函数（玩家ID，是否执行空循环）
	std::function<int(int,bool)> m_triggerConnectCallback;

	//关闭按钮
	SpriteButton * m_closeButton;

	//重新连接按钮
	SpriteButton * m_reconnectButton;

	//开始游戏按钮
	SpriteButton * m_startButton;

	//玩家人数
	int m_playerCount;

	//已连接的玩家人数
	int m_connectedPlayerCount;

};





#endif