#include "HelloWorldScene.h"

using namespace cocos2d;

CCSprite *player;
CCTMXTiledMap* map;
Talking *talking;

CCScene* HelloWorld::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        HelloWorld *layer = HelloWorld::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    bool bRet = false;
    do 
    {
		setTouchEnabled(true);

		player = CCSprite::create("Player.png");

		map = CCTMXTiledMap::create("test.tmx");
		addChild(map);

		CCTMXObjectGroup *objectgroup = map->objectGroupNamed("object");
		CCDictionary *spawnPoint = objectgroup->objectNamed("SpawnPoint");
		int x = spawnPoint->valueForKey("x")->intValue();
		int y = spawnPoint->valueForKey("y")->intValue();
		player->setPosition(ccp(x, y));

		addChild(player);

		CCLabelTTF* talkingLabel = CCLabelTTF::create(GBKToUTF8("ÖÐÎÄ").c_str(), "Arial", 50, CCSize(0, 0), kCCTextAlignmentLeft);
		talkingLabel->setPosition(ccp(200, 200));


		addChild(talkingLabel);

		talking = new Talking();
		talking->setTalkingLabel(talkingLabel);
		talking->readXml("../Talks/test.xml");

		setViewpointCenter(player->getPosition());

        bRet = true;
    } while (0);

    return bRet;
}

void HelloWorld::setViewpointCenter(CCPoint pos)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	int x = MAX(pos.x, winSize.width/2);
	int y = MAX(pos.y, winSize.height/2);
	x = MIN(x, (map->getMapSize().width * map->getTileSize().width) - winSize.width/2);
	y = MIN(y, (map->getMapSize().height * map->getTileSize().height) - winSize.height/2);
	CCPoint actualPos = ccp(x, y);

	CCPoint centerOfView = ccp(winSize.width/2, winSize.height/2);
	CCPoint viewPoint = ccpSub(centerOfView, actualPos);
	setPosition(viewPoint);
}

void HelloWorld::registerWithTouchDispatcher(void)
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool HelloWorld::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}

void HelloWorld::setPlayerPosition(CCPoint pos)
{
	player->setPosition(pos);
}

void HelloWorld::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{

	CCPoint touchLocation = this->convertTouchToNodeSpace(pTouch);

	CCPoint playerPos = player->getPosition();
	CCPoint diff = ccpSub(touchLocation, playerPos);
	if (abs(diff.x) > abs(diff.y))
	{
		if (diff.x > 0)
		{
			playerPos.x += map->getTileSize().width;
		} 
		else
		{
			playerPos.x -= map->getTileSize().width;
		}
	} 
	else
	{
		if (diff.y > 0)
		{
			playerPos.y += map->getTileSize().height;
		} 
		else
		{
			playerPos.y -= map->getTileSize().height;
		}       
	}

	if (playerPos.x <= (map->getMapSize().width * map->getTileSize().width) &&
		playerPos.y <= (map->getMapSize().height * map->getTileSize().height) &&
		playerPos.y >= 0 && playerPos.x >= 0)
	{
		setPlayerPosition(playerPos);
	}

	setViewpointCenter(player->getPosition());
}