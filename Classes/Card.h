#ifndef _CARD_H_
#define _CARD_H_

#include "cocos2d.h"

USING_NS_CC;

class CardSprite : public Sprite
{
public:
	static CardSprite* createCardSprite(int number, int wight, int height, float CardSpriteX, float CardSpriteY);
	virtual bool init();
	CREATE_FUNC(CardSprite);

	//��ȡ����
	int getNumber();
	//��������
	void setNumber(int num);
private:
	//��ʾ������
	int number;
	//��ʼ��
	void enemyInit(int number, int wight, int height, float CardSpriteX, float CardSpriteY);
	//��ʾ���ֵĿؼ�
	LabelTTF *labelCardNumber;
	//����
	LayerColor *colorBackground;
};


#endif // _CARD_H_
