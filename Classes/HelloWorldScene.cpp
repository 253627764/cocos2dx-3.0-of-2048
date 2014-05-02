#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{

    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	//���ô����¼�����
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);


    return true;
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	Point beginTouch = touch->getLocation();
	beginX = beginTouch.x;
	beginY = beginTouch.y;
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
	Point endTouch = touch->getLocation();
	//������ָ��X��Y�ƶ��ľ���
	endX = beginX - endTouch.x;
	endY = beginY - endTouch.y;
	if (abs(endX) > abs(endY))
	{
		//���X���ƶ��ľ������Y�ᣬ���������ƶ�
		if (endX + 5 > 0)
		{
			//�����ƶ�
			doLeft();
		}
		else
		{
			//�����ƶ�
			doRight();
		}
	}
	else //�����������ƶ�
	{
		if (endY + 5 > 0)
		{
			//�����ƶ�
			doDown();
		}
		else
		{
			//�����ƶ�
			doUp();
		}
	}
}

//�󻬶�
bool HelloWorld::doLeft()
{
	CCLOG("����");

	return true;
}

//�һ���
bool HelloWorld::doRight()
{
	CCLOG("����");

	return true;
}

//�ϻ���
bool HelloWorld::doUp()
{
	CCLOG("����");

	return true;
}

//�»���
bool HelloWorld::doDown()
{
	CCLOG("����");

	return true;
}
