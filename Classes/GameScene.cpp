#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	//���ô����¼�����
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	//������Ϸ����
	auto layerColorBG = LayerColor::create(Color4B(180, 170, 160, 255));
	this->addChild(layerColorBG);

	//��������
	auto cardNumberTitle = LabelTTF::create("SCORE","Consolas",80);
	cardNumberTitle->setPosition(Point(visibleSize.width/2 + 340, visibleSize.height/2 + 130));
	addChild(cardNumberTitle);

	score = 0;
	cardNumberTTF = LabelTTF::create("0", "Consolas", 70);
	cardNumberTTF->setPosition(Point(visibleSize.width/2 + 340, visibleSize.height/2 - 100));
	addChild(cardNumberTTF);

	//����4X4��Ƭ
	createCardSprite(visibleSize);

	//��ʼʱ��������2
	createCardNumber();
	createCardNumber();

	return true;
}

//������Ļ��С������Ƭ
void GameScene::createCardSprite(Size size)
{
	//�����Ԫ��Ŀ�͸�
	int cardSize = (size.height - 36) / 4;
	//���Ƴ�4X4�ĵ�Ԫ��
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			//��Ҫ��Ļ�ֱ�������
			CardSprite *card = CardSprite::createCardSprite(0, cardSize, cardSize, cardSize*i+80, cardSize*j+20);
			cardArr[i][j] = card;
			addChild(card);
		}
	}
}

bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
	//�õ�����ʱ����
	Point beginTouch = touch->getLocation();  //��ȡOpenGL���꣬�����½�Ϊԭ��
	beginX = beginTouch.x;
	beginY = beginTouch.y;

	return true;
}

void GameScene::onTouchEnded(Touch* touch, Event* event)
{
	//�õ���������ʱ����
	Point endTouch = touch->getLocation();  //��ȡOpenGL���꣬�����½�Ϊԭ��
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
			createCardNumber();
			doCheck();
			setScore(score);
		}
		else
		{
			//�����ƶ�
			doRight();
			createCardNumber();
			doCheck();
			setScore(score);
		}
	}
	else //�����������ƶ�
	{
		if (endY + 5 > 0)
		{
			//�����ƶ�
			doDown();
			createCardNumber();
			doCheck();
			setScore(score);
		}
		else
		{
			//�����ƶ�
			doUp();
			createCardNumber();
			doCheck();
			setScore(score);
		}
	}
}

//�������������Ƭ
void GameScene::createCardNumber()
{
	int i = CCRANDOM_0_1() * 4;        //����0~3�����
	int j = CCRANDOM_0_1() * 4;

	//�ж��Ƿ��Ѿ�����
	if (cardArr[i][j]->getNumber() > 0)
	{
		createCardNumber();
	}
	else
	{
		//2��4��������Ϊ9:1
		cardArr[i][j]->setNumber(CCRANDOM_0_1()*10 < 1 ? 4 : 2);
	}
}

//�����Ϸ�Ƿ����
void GameScene::doCheck()
{
	bool isGameOver = true;
	//�ж�ÿһ�����������Һ��Լ��Ƿ���ͬ
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (cardArr[x][y]->getNumber() == 0 ||
				(x<3 && cardArr[x][y]->getNumber() == cardArr[x+1][y]->getNumber()) ||
				(x>0 && cardArr[x][y]->getNumber() == cardArr[x-1][y]->getNumber()) ||
				(y<3 && cardArr[x][y]->getNumber() == cardArr[x][y+1]->getNumber()) ||
				(y>0 && cardArr[x][y]->getNumber() == cardArr[x][y-1]->getNumber()) )
			{
				isGameOver = false;
			}
		}
	}
	if (isGameOver)
	{
		//����
		Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::createScene()));
	}
}

//�󻬶�
bool GameScene::doLeft()
{
	//�ж���û�з����ƶ�
	bool isMove = false;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			for (int x1 = x+1; x1<4; x1++)
			{
				if (cardArr[x1][y]->getNumber() > 0)
				{
					if (cardArr[x][y]->getNumber() <= 0)
					{
						cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber());
						cardArr[x1][y]->setNumber(0);
						x--;
						isMove = true;
					}
					else if(cardArr[x][y]->getNumber() == cardArr[x1][y]->getNumber())
					{
						 cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
						 cardArr[x1][y]->setNumber(0);

						 //�ı����
						 score += cardArr[x][y]->getNumber();
						 isMove = true;
					}
					break;
				}
			}
		}
	}

	return isMove;
}

//�һ���
bool GameScene::doRight()
{
	//�ж���û�з����ƶ�
	bool isMove = false;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 3; x >= 0; x--)
		{
			for (int x1 = x-1; x1>=0; x1--)
			{
				if (cardArr[x1][y]->getNumber() > 0)
				{
					if (cardArr[x][y]->getNumber() <= 0)
					{
						cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber());
						cardArr[x1][y]->setNumber(0);
						x++;
						isMove = true;
					}
					else if(cardArr[x][y]->getNumber() == cardArr[x1][y]->getNumber())
					{
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
						cardArr[x1][y]->setNumber(0);
						//�ı����
						score += cardArr[x][y]->getNumber();
						isMove = true;
					}
					break;
				}
			}
		}
	}

	return isMove;
}

//�ϻ���
bool GameScene::doUp()
{
	//�ж���û�з����ƶ�
	bool isMove = false;
	for (int x = 0; x < 4; x++)
	{
		for (int y = 3; y >= 0; y--)
		{
			for (int y1 = y-1; y1>=0; y1--)
			{
				if (cardArr[x][y1]->getNumber() > 0)
				{
					if (cardArr[x][y]->getNumber() <= 0)
					{
						cardArr[x][y]->setNumber(cardArr[x][y1]->getNumber());
						cardArr[x][y1]->setNumber(0);
						y++;
						isMove = true;
					}
					else if(cardArr[x][y]->getNumber() == cardArr[x][y1]->getNumber())
					{
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
						cardArr[x][y1]->setNumber(0);
						//�ı����
						score += cardArr[x][y]->getNumber();
						isMove = true;
					}
					break;
				}
			}
		}
	}

	return isMove;
}

//�»���
bool GameScene::doDown()
{
	//�ж���û�з����ƶ�
	bool isMove = false;
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y <4; y++)
		{
			for (int y1 = y+1; y1<4; y1++)
			{
				if (cardArr[x][y1]->getNumber() > 0)
				{
					if (cardArr[x][y]->getNumber() <= 0)
					{
						cardArr[x][y]->setNumber(cardArr[x][y1]->getNumber());
						cardArr[x][y1]->setNumber(0);
						y--;
						isMove = true;
					}
					else if(cardArr[x][y]->getNumber() == cardArr[x][y1]->getNumber())
					{
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
						cardArr[x][y1]->setNumber(0);
						//�ı����
						score += cardArr[x][y]->getNumber();
						isMove = true;
					}
					break;
				}
			}
		}
	}

	return isMove;
}

//���÷���
void GameScene::setScore(int score)
{
	cardNumberTTF->setString(__String::createWithFormat("%i",score)->getCString());
}