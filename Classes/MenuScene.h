#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"

#include "MainScene.h"

using namespace cocos2d;

class MenuScene : public CCLayer
{
public:
	virtual bool init();

	static CCScene* scene();

	void menuNewCallback(CCObject* pSender);
	void menuCloseCallback(CCObject* pSender);

	CREATE_FUNC(MenuScene);
};

#endif
