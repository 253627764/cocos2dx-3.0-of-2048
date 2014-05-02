#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();  
    CREATE_FUNC(HelloWorld);

	//�����¼������ص�����
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);
private:
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
};

#endif // __HELLOWORLD_SCENE_H__
