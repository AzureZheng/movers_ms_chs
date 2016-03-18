/****************************************
����������
2016-02-01 by Azure Zheng
*****************************************/


#ifndef __BUILDING_SCENE_H__
#define __BUILDING_SCENE_H__

#include "cocos2d.h"
#include "Scene/PlayerLayer.h"
#include "Objects/MoversTruck.h"
#include "Info/GameInfo.h"
#include "UI/MoverGameUI.h"

USING_NS_CC;



class BuildingScene : public Layer
{
public:

	//�ͷ���Դ
	virtual ~BuildingScene();

	//��������
	static Scene * createScene(int playerCount);

	//�ӹ���ģʽ��������
	static Scene * createSceneWithStory(int playerCount);

	//����ʵ��
	CREATE_FUNC(BuildingScene);

	//��ʼ��ʵ��
	virtual bool init();

	//��������ʼ����Ϸ
	void initWithPlayerCount(int playerCount,bool startStory = true);

	//���ٿ�ʼ��Ϸ
	void quicklyStartGame();

	//������Ҳ���
	void createPlayerLayers();

	//����������Ҳ�
	void createSinglePlayerLayer();

	//����˫����Ҳ�
	void createDoublePlayersLayers();

	//����������Ҳ�
	void createMultiPlayersLayers();

	//��ȡ��Ϸ����
	int getPlayerCount(){ return m_playerCount; }

	//����������
	void addBackWorld();

	//����ǰ����
	void addFrontWorld();

	//���£���ʼ����
	void runWithStory();

	//���£��Ƴ�
	void moveCar(float dt = 0);

	//���£��Ż�
	void pushGoods();

	//���£�����
	void openDoor();

	//���£���ǻ
	void talkStart();

	//���£��߳���
	void moveOut();

	//��ʼһ��
	virtual void startWave(float dt);

	//�¿�һ��
	virtual void startNewRound();

	//�л�ģʽ
	static void setGameMode(int mode){ m_gameMode = mode; }

	//��ȡģʽ
	static int getGameMode(){ return m_gameMode; }

	//��ȡ��Ҳ��Ӧ��ǰ����λ��
	Vec2 getPlayerLayerPosInFrontLayer(int layerIndex);

	//��ȡ��Ҳ��Ӧ��UI��λ��
	Vec2 getPlayerLayerPosInUILayer(int layerIndex);

	//ʱ�Ӳ���
	void clockStep(float dt);

	//�߼�����
	void logicStep(float dt);

	//���ַ�����ȡ�����������б���
	void readStringToGame(const std::string & _A0B);

	//��ȡ��һ������
	void newWave();

	//������¥
	void upFloor();

	//������¥����
	void upFloorFinish();

	//ʹ��һ������
	void doMeterOnce(int meterIndex);

	//��ȡ����ͷ
	void readMusicHead();

	//��ȡ������
	void readMusicBody();

	//���1�������
	bool touchControl(Touch * touch, Event * e);

	//������Ҵ������
	void touchControlMulti(int playerID, const Vec2 & touchLocation);

	//������Ҳ���
	void unlockTouchControl(int playerID);
	void unlockTouchControlSide2(int side,int playerID = 0);

	//ע�ᴥ������
	void setupTouchListener();

	//Ԥ����Ч
	void preloadEffect();

	//�����ƶ�
	void createClouds(float dt);

	//���UI��
	void addUILayer();

	//��ҳ��ť�ص�
	void gameHomeButtonCallBack(Ref* sender);

	//���԰�ť�ص�
	void gameRetryButtonCallBack(Ref* sender);

	//��ͣ��ť�ص�
	void gamePauseButtonCallBack(Ref* sender);

	//�ָ���ť�ص�
	void gameResumeButtonCallBack(Ref* sender);

	//�ָ�
	void resumeGame();

	//��ͣ
	void pauseGame();

	//����
	void retryPlay();

	//��ҳ
	void returnHome();

	//ֱ�ӽ�����ҳ
	void intoHome();

	//�ָ�����
	void countDown(float dt);

	//��̬���ӷ���
	static void staticAwardScore(int playerID,int score = 100);

	//���ӷ���
	void awardScore(int playerID, int score = 100);

	//��ȡʵ��
	static BuildingScene * getInstance();

	//��ȡ��Ϸ��Ҳ�
	PlayerLayer * getPlayerLayer(int playerID){ return m_playerLayers.at(playerID); }

	//����Ļ
	void shakeScreen();

	//��Ϸ��������
	void gameOver(int playerID, int side = 0);

	//��Ϸ������������
	void gameTruelyOver();

	//�Ƴ���������
	void removeTouchListener();

	//��ʾ��Ϸ����
	void pushResult(float dt);

	//������ҵ��������(�����Ƿ�������)
	bool checkMultiPlayerInput(int * playerIDToBeSaved, Vec2 * posToBeSaved);

	//ѭ����������������
	void loopCheckMultiPlayerInput(float dt);

	//ͨ���豸ID��ȡ���ID������-1Ϊʧ�ܣ�
	int getPlayerIDByDeviceID(int deviceID);

	//��ȡ��Ҷ�Ӧ��ϵָ��
	static std::map<int, int> * getPlayersIDMap(){ return &m_playersIDMap; }

	//--------------------- �������� ------------------------
	//�����������
	static unsigned int m_bgmIndex;

	//������Ч���
	static unsigned int m_sfxIndex;

protected:

	//��̬ʵ��
	static BuildingScene * m_instance;

	//�����б�
	std::vector<MeterOnce> m_meterList;

	//��Ҷ�Ӧ��ϵ(�豸ID->���ID)
	static std::map<int, int> m_playersIDMap;

	//��������
	int m_meterStep;

	//���ֶβ���
	int m_bgmStep;

	//һ�ֵĿ�ʼ����
	int m_beginStep;

	//һ�ֵĽ�������
	int m_endStep;

	//��������
	int m_lastLen;

	//����������
	EventListenerTouchOneByOne * m_listener;

	//��Ϸ�߼�
	GameInfo * m_logicInfo;

	//�е�
	Vec2 m_centerPoint;

	//��Ļ��С
	Size m_visibleSize;

	//��Ϸ����
	int m_playerCount;

	//��Ҳ���
	Vector<PlayerLayer*> m_playerLayers;

	//����̶���
	Node * m_worldHolder;

	//����ı����̶���
	SpriteBatchNode * m_backOfWorldHolder;
	Sprite * m_backSky;
	Sprite * m_backMountain;
	Sprite * m_backBuildings;
	Sprite * m_backTrees;

	//�����¥��̶���
	Node * m_buildingsOfWorldHolder;

	//�����ǰ���̶���
	Node * m_frontOfWorldHolder;

	//UI�̶���
	Node * m_uiHolder;
	MoverGameplayUI * m_gameUI;
	MoverGamepauseUI * m_pauseUI;
	MoverResultUI * m_resultUI;

	//����
	MoversTruck * m_car;

	//����Boss
	Vector<RabbitHamal*> m_rabbitBosses;

	//ͳһ���������ıߵĶ���
	int m_rabbitSide;

	//��Ϸģʽ(0:����ģʽ;1:����ģʽ)
	static int m_gameMode;

	//�Ƿ����˳���
	bool m_isLeaving;

	//�Ƿ�ʼ����Ϸ
	bool m_isBegan;

	//�Ƿ��������Ϸ
	bool m_isOvered;

};








#endif
