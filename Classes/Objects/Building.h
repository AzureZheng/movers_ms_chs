/****************************************
������
2016-02-02 by Azure Zheng
*****************************************/

#ifndef __BUILDING_H__
#define __BUILDING_H__


#include "cocos2d.h"
#include "Objects/BuildingStage.h"
USING_NS_CC;


class Building : public Node
{
public:
	
	//����ʵ��
	CREATE_FUNC(Building);

	//��ʼ��
	virtual bool init();

	//���һ��
	void addStage();

	//�Ƴ��ײ�
	void removeBottomStage();

	//��ȡ¥����
	const Vector<BuildingStage*> & getBuildingStages() const;

	//��ȡ�߲����
	int getHighFloorIndex(){ return m_highFloor; }

	//���¥��
	void clearFloors();

	//¥�������ƶ�
	void moveAllFloors(float height);

	//��ȡ�����
	BuildingStage * getThrowStage();

	//��ȡ���ֲ�
	BuildingStage * getRecvStage();

	//���ý�ɫ���
	void setPlayerFlag(int flag){ m_playerFlag = flag; }

	//��ȡ��ɫ���
	int getPlayerFlag(){ return m_playerFlag; }

protected:

	//¥����
	Vector<BuildingStage*> m_buildingStages;

	//��󻺴�¥����
	int m_maxStagesCache;

	//�߲����
	int m_highFloor;

	//��ɫ���
	int m_playerFlag;
};



#endif
