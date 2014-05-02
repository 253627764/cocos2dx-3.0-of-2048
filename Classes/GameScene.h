#ifndef _GAME_SCENE_H
#define _GAME_SCENE_H

#include "cocos2d.h"
#include "Card.h"

class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();  
	CREATE_FUNC(GameScene);

	//�����¼������ص�����
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

private:
	//������Ļ��С������Ƭ
	void createCardSprite(Size size);
	//˽�б��˼�¼������ʼ�ڽ���ʱ������
	int beginX,beginY,endX,endY;
	//�󻬶�
	bool doLeft();
	//�һ���
	bool doRight();
	//�ϻ���
	bool doUp();
	//�»���
	bool doDown();
	//���濨Ƭ��
	CardSprite *cardArr[4][4];
	//����
	int score;
	//��ʾ�����ؼ�
	LabelTTF *cardNumberTTF;
	//�������������Ƭ
	void createCardNumber();
	//�����Ϸ�Ƿ����
	void doCheck();
	//���÷���
	void setScore(int score);
};

#endif // _GAME_SCENE_H
