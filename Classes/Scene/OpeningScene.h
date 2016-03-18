/****************************************
��������
2016-01-28 by Azure Zheng
*****************************************/

#ifndef __OPENING_SCENE_H__
#define __OPENING_SCENE_H__

#include "cocos2d.h"

class OpeningScene : public cocos2d::Layer
{
public:

	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(OpeningScene);

	//��ʾ��������
	void showOpeningAnim();

	//Ԥ������Դ
	void preloadRes();

	//�رտ�������
	void closeOpeningAnim();

	//�л�����һ����
	void enterNextScene();

	//�������
	virtual void update(float dt);

	//���̼�����1
	void countProgressIndex();

	//����Ԥ������Դ��ɻص�(method: 0.��ͨ���أ�1.���һ�μ���)(plistPath��ͬʱ����plist���򲻼���)
	void preloadResCallback(cocos2d::Texture2D * tex,const std::string & plistPath);

	//����ʱ�Ƴ���Դ
	virtual void onExit();

protected:

	//����������
	cocos2d::Layer * m_openingAnimLayer;

	//��Ļ��С
	cocos2d::Size m_visibleSize;

	//���̼���
	int m_progressIndex;

	//���̵ȴ�
	bool m_progressWait;

	//��Դ���ؼ���
	int m_resPreloadCount;

	//��Դ����
	int m_resPreloadTotalCount;
};

#endif
