//***********************************************

// MoversHomeScene ----- home scene of game

//***********************************************

#ifndef _MOVERS_HOME_SCENE_H_
#define _MOVERS_HOME_SCENE_H_

#include "cocos2d.h"

USING_NS_CC;

#include "FilePathDefine.h"
#include "Info\GameInfo.h"
#include "UI/MoverGameUI.h"
#include "UI/PushButton.h"
#include "UI/ConnectUI.h"
#include "Info/GameInfo.h"
#include "Objects/MoversTruck.h"

class MoversHomeScene : public Layer
{
	MoversTruck * _car;

	Node * downHolder;

	Node * uiHolder;

	bool inOption;
	bool inMenu;

	EventListenerTouchOneByOne * _listener;

	std::function<void()> doIntoGame;

	PushButton * buttonGame, *buttonGame2, *buttonMod1, *buttonMod2, *buttonMod3, *buttonBack, *buttonAbout, *buttonRecord;

	int _playerCount;

	ConnectUI * _connectUI_2;
	ConnectUI * _connectUI_4;
	ConnectUI * _connectUI;

public:
	void unlockMode();
	void intoMod1();

	void intoMod2();

	void confirmMenu(){ inMenu = true; }

	void confirmAbout(){ inOption = true; }

	bool onTouchBegan( Touch *touch , Event *event );

	void onTouchEnded( Touch *touch , Event *event );

	void onExit();

	void showAbout();

	void hideOptions();

	void showRecord();

	void intoGame();

	void blackScreen();

	void goToGame(int playerCount);

	void goToGame1();

	void goToGame2();

	void goToGame3();

	void backHome();

	float _bv;

	void swapCloud( float dt = 0 );

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC( MoversHomeScene );

	void loodGrass1( float dt );

	void landGrass1( float PX );

	void loodGrass2( float dt );

	void landGrass2( float PX );

	void loodMountain( float dt );

	void landMountain( float PX );

	void subBgmV( float dt );

	//��Ӹ߷ּ������UI
	void addHighScoreUI();

	//��ӱ���ͼ
	void addBackWorld();

	//�������UI
	void addConnectUI();

	//�������ӽ���
	void popConnectUI();

	//�ر����ӽ���
	void closeConnectUI(Ref * ref);

	//�������ӻص�
	void reconnectForConnectUI(Ref * ref);

	//��ʼ��Ϸ�ص�
	void startGameButtonCallback(Ref * ref);

	//���������ص�
	int connectListener(int playerID, bool isEmptyLoops);

	//�������Buffer
	void clearListenerBuffer();

};

#endif // _MOVERS_HOME_SCENE_H_