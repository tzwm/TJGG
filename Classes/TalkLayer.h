#ifndef __TALK_LAYER_H__
#define __TALK_LAYER_H__

#include<string>

#include "cocos2d.h"

#include "helper.h"
#include "Talking.h"
#include "MainScene.h"

using namespace cocos2d;

class TalkLayer : public CCLayer
{
public:
	CCScene* scene;

	Talking* talking;
	CCLabelTTF* talkingText;
	std::string xmlFile;
	CCSprite* headIcon;

	void setScene(CCScene* scene);
	void setXml(std::string _xmlFile);

	static TalkLayer* create(std::string _xmlFile, CCScene* _scene);
	virtual bool init();

	virtual void registerWithTouchDispatcher(void);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	CREATE_FUNC(TalkLayer);
};

#endif