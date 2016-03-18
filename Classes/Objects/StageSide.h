/****************************************
¥��һ��
2016-02-01 by Azure Zheng
*****************************************/


#ifndef __STAGE_SIDE_H__
#define __STAGE_SIDE_H__

#include "cocos2d.h"
#include "Objects/RabbitHamal.h"

USING_NS_CC;

class StageSide : public Node
{
public:

	//��ģ��������ʵ��(0:����ͨ;1:����ͨ;2:��һ��;3:��һ��)
	static StageSide * createWithType(int type);

	//����ʵ��
	CREATE_FUNC(StageSide);

	//��ʼ��
	virtual bool init();

	//��ȡ����ʵ��
	RabbitHamal * getRabbit();

	//��������ʵ��
	void setRabbit(RabbitHamal * rabbit);

	//�������
	void clearRabbit();

	//��ȡ����
	int getSide(){ return m_side; }

	//��������
	void setSide(int side,bool flipped = true);

	//���ý�����ת
	void setBuildingFlipped(bool flipped);

	//��������ͼ��
	void setRail(Sprite * rail);

	//����ǽ��ͼ��
	void setWall(Sprite * wall);

	//���ӳ���
	void showRabbit(float dt = 0.5f);

	//��������
	void hideRabbit();

	//�������ӷ�λ
	void refreshRabbitPos();

	//��ȡ�����Ƿ�����
	bool isRabbitHide(){ return m_hideRabbit; }

	//��ȡǽ�ڴ�С
	Size getWallSize();

	//��ʾ��
	void showYou(bool fourPlayer = false);

	//������
	void hideYou();

protected:

	//λ��(0:��1:��)
	int m_side;
	
	//�Ƿ�ת
	bool m_isFlipped;

	//����ʵ��
	RabbitHamal * m_rabbit;

	//����
	Sprite * m_rail;

	//ǽ��
	Sprite * m_wall;

	//�����Ƿ�����
	bool m_hideRabbit;

	//ǽ�ڴ�С
	Size m_wallSize;

};


#endif
