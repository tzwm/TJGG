#ifndef __TALKING_H__
#define __TALKING_H__

#include<vector>
#include<string>

#include "TalkNode.h"
#include "helper.h"

#include "cocos2d.h"
using namespace cocos2d;

class Talking
{
public:
	std::vector<TalkNode*> talkList;
	int talkCount;
	int wordCount;
	int talkIndex;
	CCLabelTTF* talkingLabel;
	CCSprite* talkingHead;

	Talking();
	void setTalkingLabel(CCLabelTTF* _TalkingLabel);
	void readXml(const char* filename);
	bool showTalk();
	std::string getHeadIcon();
	//bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
};

#endif