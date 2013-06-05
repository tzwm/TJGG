#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include<vector>

#include "cocos2d.h"

#include "helper.h"
#include "HeroSprite.h"
#include "TalkLayer.h"
#include "MapTiled.h"
#include "NpcSprite.h"
#include "MenuScene.h"

using namespace cocos2d;

class MainScene : public cocos2d::CCLayer
{
public:
	MapTiled* map;
	HeroSprite* player;
	static CCScene* mainScene;
	std::vector<NpcSprite*> npcGroup;
	std::vector<CCTouch> touches;

	virtual bool init();

	static cocos2d::CCScene* scene();

	void changeMap(std::string file);
	void getNpcs();
	void setViewpointCenter(CCPoint pos);
	void registerWithTouchDispatcher(void);
	void close();
	void backMenu();

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCTouch *pTouches, CCEvent *pEvent);
	
	void reEnableTouches(float dt);
	void update(float dt);

	void menuBackCallback(CCObject* pSender);
	void menuShowImgCallback(CCObject* pSender);
	void menuCloseCallback(CCObject* pSender);

	CREATE_FUNC(MainScene);
};

#endif
