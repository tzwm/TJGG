#include "MainScene.h"

CCScene* MainScene::mainScene = CCScene::create();

CCScene* MainScene::scene()
{
	// 'scene' is an autorelease object
	mainScene = CCScene::create();

	// 'layer' is an autorelease object
	MainScene *layer = MainScene::create();

	// add layer as a child to scene
	mainScene->addChild(layer, 0, 0);

	// return the scene
	return mainScene;
}

bool MainScene::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	setTouchEnabled(true);

	CCMenuItemImage* back = CCMenuItemImage::create(
		"pic/back.png", "pic/back.png", this, menu_selector(MainScene::menuBackCallback));
	CCMenuItemImage* showMap = CCMenuItemImage::create(
		"pic/camera.png", "pic/camera.png", this, menu_selector(MainScene::menuShowImgCallback));
	CCMenu* menu = CCMenu::create(back, showMap, NULL);
	menu->alignItemsHorizontally();
	menu->setPosition(ccp(600, 400));
	this->addChild(menu, 3);

	map = (MapTiled*)MapTiled::create("maps/mapUp1.tmx");
	//map->runAction((CCScaleBy::create(0.1, 1)));
	this->addChild(map, 0);

	player = (HeroSprite*)CCSprite::create("hero/hero.png");
	player->setPosition(Helper::getPosByName("hero", map));
	this->addChild(player, 1);
	setViewpointCenter(player->getPosition());

	getNpcs();

	this->schedule( schedule_selector(MainScene::update), player->metaDuration/2);

	return true;
}

void MainScene::setViewpointCenter(CCPoint pos)
{
	//this->runAction(CCFollow::create(player));
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	int x = MAX(pos.x, winSize.width/2);
	int y = MAX(pos.y, winSize.height/2);
	x = MIN(x, (map->getMapSize().width * map->getTileSize().width) - winSize.width/2);
	y = MIN(y, (map->getMapSize().height * map->getTileSize().height) - winSize.height/2);
	CCPoint actualPos = ccp(x, y);

	CCPoint centerOfView = ccp(winSize.width/2, winSize.height/2);
	CCPoint viewPoint = ccpSub(centerOfView, actualPos);
	this->runAction(CCMoveTo::create(0.3, viewPoint));
	//setPosition(viewPoint);
}


bool MainScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}

void MainScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCTouch tmp = *pTouch;
	touches.push_back(tmp);
}

void MainScene::ccTouchesMoved(CCTouch *pTouches, CCEvent *pEvent)
{

}

void MainScene::reEnableTouches(float dt)
{
	this->unschedule(schedule_selector(MainScene::reEnableTouches));
	this->setTouchEnabled(true);
}

void MainScene::registerWithTouchDispatcher(void)
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void MainScene::backMenu()
{
	CCScene* scene = MenuScene::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(2, scene));
}

void MainScene::menuBackCallback(CCObject* pSender)
{
	this->backMenu();
}

void MainScene::menuShowImgCallback(CCObject* pSender)
{
}

void MainScene::update(float dt)
{
	if(touches.size() == 0)
		return;

	CCTouch* touch = &touches[0];
	touches.erase(touches.begin());
	CCPoint location = touch->getLocationInView();
	CCPoint finalLocation = player->getPosition();	//最终移动的终点

	//鼠标点击的位置
	location = CCDirector::sharedDirector()->convertToGL(location);

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	//int offX = location.x - this->getPosition().x;
	//int offY = location.y - this->getPosition().y;
	int offX = location.x - size.width/2;
	int offY = location.y - size.height/2;

	int changeX = 0;
	int changeY = 0;

	int direction;
	if (abs(offX) >= abs(offY))
	{
		if (offX > 0)
		{
			changeX += player->stepLength;	//right
			direction = 4;
		} else 
		{
			changeX -= player->stepLength;	//left			
			direction = 0;
		}
	} else 
	{
		if (offY > 0)
		{
			changeY += player->stepLength;	//up
			direction = 2;
		} else
		{
			changeY -= player->stepLength;	//down
			direction = 6;
		}
	}
	finalLocation.x += changeX;
	finalLocation.y += changeY;

	if(! map->canMove(finalLocation))
	{
		//this->setTouchEnabled(true);
		if(finalLocation.y < 64)
		{
			changeMap("maps/mapDown.tmx");
		}
		if(finalLocation.y > map->getContentSize().height -64)
		{
			changeMap("maps/mapUp1.tmx");
		}
		if(finalLocation.x < 64)
		{
			this->backMenu();
		}
		if(finalLocation.x > map->getContentSize().width -80)
		{
			this->backMenu();
		}

		return;
	}

	CCRect rect = CCRectMake(
		player->getPosition().x - player->getContentSize().width/2 + changeX +64,
		player->getPosition().y - player->getContentSize().height/2 + changeY +64,
		player->getContentSize().width + changeX -128,
		player->getContentSize().height + changeY -128);
	for(int i = 0; i<npcGroup.size(); i++)
	{
		CCRect npcRect = CCRectMake(
			npcGroup[i]->getPosition().x - npcGroup[i]->getContentSize().width/2,
			npcGroup[i]->getPosition().y - npcGroup[i]->getContentSize().height/2,
			npcGroup[i]->getContentSize().width,
			npcGroup[i]->getContentSize().height);
		bool b = rect.intersectsRect(npcRect);
		if(!b)
			continue;
		std::string name = npcGroup[i]->name;
		TalkLayer* talklayer = TalkLayer::create("talks/"+name+".xml", this->mainScene);
		setTouchEnabled(false);
		this->mainScene->addChild(talklayer, 2);
		return;
	}

	//this->schedule(schedule_selector(MainScene::reEnableTouches), player->metaDuration);

	//if(touches.size() < 3)
	//player->move(finalLocation, direction);
	//else
	player->run(finalLocation, direction);

	setViewpointCenter(player->getPosition());
}

void MainScene::changeMap(std::string file)
{
	this->removeChild(map);
	map = (MapTiled*)MapTiled::create(file.c_str());
	//map->runAction((CCScaleBy::create(0.1, 1)));
	this->getNpcs();
	player->setPosition(ccp(player->getPosition().x, map->getContentSize().height-player->getPosition().y));
	this->addChild(map, 0);
}

void MainScene::getNpcs()
{
	npcGroup.clear();
	CCTMXObjectGroup* objectGroup = this->map->objectGroupNamed("Object");
	CCArray* objectForGroup = objectGroup->getObjects();
	for(int i = 0; i < objectForGroup->count(); i++)
	{
		CCDictionary* objectInfo = (CCDictionary*)objectForGroup->objectAtIndex(i);
		std::string name = objectInfo->valueForKey("name")->getCString();
		if(name == "hero") 
			continue;
		std::string file = "npc/" + name + ".png";
		//NpcSprite* npc = (NpcSprite*)CCSprite::create(file.c_str());
		NpcSprite* npc = NpcSprite::create(file);
		npc->name = name;
		npcGroup.push_back(npc);
		npc->setPosition(Helper::getPosByName(name, map));
		this->addChild(npc, 1);
	}
}

void MainScene::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void MainScene::close()
{
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
