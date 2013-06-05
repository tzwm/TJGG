#include "HeroSprite.h"

float HeroSprite::metaDuration = 0.4;
float HeroSprite::stepLength = 32;

void HeroSprite::move(CCPoint finalLocation, int direction)
{
	//CCTouch* touch = _touch;
	//CCPoint location = touch->getLocationInView();
	//CCPoint finalLocation = this->getPosition();	//最终移动的终点

	////鼠标点击的位置
	//location = CCDirector::sharedDirector()->convertToGL(location);

	//CCSize size = CCDirector::sharedDirector()->getWinSize();

	////int offX = location.x - this->getPosition().x;
	////int offY = location.y - this->getPosition().y;
	//int offX = location.x - CCDirector::sharedDirector()->getWinSize().width/2;
	//int offY = location.y - CCDirector::sharedDirector()->getWinSize().height/2;

	//int direction;
	//if (abs(offX) >= abs(offY))
	//{
	//	if (offX > 0)
	//	{
	//		finalLocation.x += stepLength;	//right
	//		direction = 4;
	//	} else 
	//	{
	//		finalLocation.x -= stepLength;	//left			
	//		direction = 0;
	//	}
	//} else 
	//{
	//	if (offY > 0)
	//	{
	//		finalLocation.y += stepLength;	//up
	//		direction = 2;
	//	} else
	//	{
	//		finalLocation.y -= stepLength;	//down
	//		direction = 6;
	//	}
	//}

	//if(! map->canMove(finalLocation))
	//	return ccp(-1, -1);

	CCArray* pArray = CCArray::create();

	pArray->addObject(CCSpriteFrame::create("hero/heroMove_02.png", CCRectMake(0, 256 * direction, 256, 256)));
	pArray->addObject(CCSpriteFrame::create("hero/heroMove_03.png", CCRectMake(0, 256 * direction, 256, 256)));
	pArray->addObject(CCSpriteFrame::create("hero/heroMove_04.png", CCRectMake(0, 256 * direction, 256, 256)));
	pArray->addObject(CCSpriteFrame::create("hero/heroMove_05.png", CCRectMake(0, 256 * direction, 256, 256)));
	pArray->addObject(CCSpriteFrame::create("hero/heroMove_06.png", CCRectMake(0, 256 * direction, 256, 256)));
	pArray->addObject(CCSpriteFrame::create("hero/heroMove_07.png", CCRectMake(0, 256 * direction, 256, 256)));
	pArray->addObject(CCSpriteFrame::create("hero/heroMove_08.png", CCRectMake(0, 256 * direction, 256, 256)));
	pArray->addObject(CCSpriteFrame::create("hero/heroMove_01.png", CCRectMake(0, 256 * direction, 256, 256)));

	CCAnimation* animation = CCAnimation::create();
	animation->initWithSpriteFrames(pArray, 0.05);

	CCAnimate* animate = CCAnimate::create(animation);
	this->runAction(animate);

	this->runAction(CCSequence::create(
		CCMoveTo::create(metaDuration, finalLocation)
		,NULL
		,NULL));
}

void HeroSprite::run(CCPoint finalLocation, int direction)
{
	CCArray* pArray = CCArray::create();

	pArray->addObject(CCSpriteFrame::create("hero/heroMove_02.png", CCRectMake(0, 256 * direction, 256, 256)));
	//pArray->addObject(CCSpriteFrame::create("hero/heroMove_03.png", CCRectMake(0, 256 * direction, 256, 256)));
	//pArray->addObject(CCSpriteFrame::create("hero/herkoMove_04.png", CCRectMake(0, 256 * direction, 256, 256)));
	//pArray->addObject(CCSpriteFrame::create("hero/heroMove_05.png", CCRectMake(0, 256 * direction, 256, 256)));
	pArray->addObject(CCSpriteFrame::create("hero/heroMove_06.png", CCRectMake(0, 256 * direction, 256, 256)));
	pArray->addObject(CCSpriteFrame::create("hero/heroMove_07.png", CCRectMake(0, 256 * direction, 256, 256)));
	pArray->addObject(CCSpriteFrame::create("hero/heroMove_08.png", CCRectMake(0, 256 * direction, 256, 256)));
	pArray->addObject(CCSpriteFrame::create("hero/heroMove_01.png", CCRectMake(0, 256 * direction, 256, 256)));

	CCAnimation* animation = CCAnimation::create();
	animation->initWithSpriteFrames(pArray, 0.05);

	CCAnimate* animate = CCAnimate::create(animation);
	this->runAction(animate);

	this->runAction(CCSequence::create(
		CCMoveTo::create(metaDuration/2, finalLocation)
		,NULL
		,NULL));
}
