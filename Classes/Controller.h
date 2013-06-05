#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "cocos2d.h"

#include "helper.h"
#include "HeroSprite.h"
#include "MainScene.h"
#include "MapTiled.h"

using namespace cocos2d;

class Controller{
	MainScene* currentLayer;
	CCScene* currentScene;
	MapTiled* currentMap;
	HeroSprite* hero;


};

#endif
