/****************************************
�����Ϸ��
2016-02-01 by Azure Zheng
*****************************************/

#ifndef __PLAYER_LAYER_H__
#define __PLAYER_LAYER_H__

#include "cocos2d.h"
#include "Objects/Building.h"

USING_NS_CC;


class PlayerLayer : public ClippingRectangleNode
{
public:

	//����ʵ��
	CREATE_FUNC(PlayerLayer);

	//��ʼ��ʵ��
	virtual bool init();

	//����������
	void setPlayerID(int id){ m_playerID = id; }

	//��ȡ������
	int getPlayerID(){ return m_playerID; }

	//���һ��¥��
	void addBuildingStage();

	//��ȡ��ǰ¥�����
	int getStageCount(){ return m_stageCount; }

	//��ȡ¥��
	Building * getBuilding(){ return m_building; }

	//������ʼ¥��
	void initBuilding();

	//���òü���С
	void setClippingArea(const Size & size);

	//����¥�����
	void gainStageCount(){ m_stageCount++; }

	//��ʱ���Ӳ㼶
	void delayUpFloor(float dt);

	//���Ӳ㼶
	void upFloor();

	//ˢ����Ұ
	void refreshView();

	//�㼶�������
	virtual void upFloorFinish();

	//����¥���ӽ�λ��
	virtual void setFloorCameraPos(const Vec2 & pos);

	//����¥���ӽ�ƫ��
	virtual void setFloorCameraOffset(const Vec2 & offset);

	//��ȡ¥���ӽ�λ��
	virtual const Vec2 & getFloorCameraPos() const;

	//���ø�����Ƿ�����
	void setOver(bool isOver){ m_isOver = isOver; }

	//��ȡ������Ƿ�����
	bool getOver(){ return m_isOver; }

	//������������
	void setControlLocked(bool lock){ m_lockControl = lock; }
	void setControlLockedSide2(bool lock){ m_lockControl2 = lock; }

	//��ȡ��ǰ����Ƿ���������
	bool isLockedControl(){ return m_lockControl; }
	bool isLockedControlSide2(){ return m_lockControl2; }

	//��ȡ��ʾ����
	int getViewScore(){ return m_viewScore; }

	//��ȡĿ�����
	int getScore(){ return m_score; }

	//������ʾ����
	void setViewScore(int score){ m_viewScore = score; }

	//����Ŀ�����
	void setSocre(int score){ m_score = score; }

	//����Ŀ�����
	void gainScore(int score){ m_score += score; }

	//������ʾ����
	void gainViewScore(int score){ m_viewScore += score; }

protected:

	//������
	int m_playerID;

	//¥�����
	int m_stageCount;

	//����Ƿ�����
	bool m_isOver;

	//��������
	bool m_lockControl;
	bool m_lockControl2;

	//�����ʾ����
	int m_viewScore;

	//���Ŀ�����
	int m_score;

	//------------------ ����̶��� --------------------
	//¥������̶���
	Node * m_objectsHolder;

	//¥��
	Building * m_building;


	//------------------- UI�̶��� ----------------------


};



#endif
