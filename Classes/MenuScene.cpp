#include "MenuScene.h"

CCScene* MenuScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	MenuScene *layer = MenuScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool MenuScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

	CCSprite* background = CCSprite::create("pic/menuBackground_new.png");
	background->setPosition(ccp(400, 303));
	addChild(background);

	CCSprite* title = CCSprite::create("pic/title.png");
	title->setPosition(ccp(420, 450));
	title->runAction(CCScaleBy::create(0.1, 1.4));
	addChild(title);

	CCSprite* logoTongji = CCSprite::create("pic/logoTongji.png");
	logoTongji->setPosition(ccp(650, 450));
	logoTongji->runAction(CCScaleBy::create(0.5, 0.28));
	addChild(logoTongji);

	CCSprite* playIcon = CCSprite::create("pic/play.png");
	CCSprite* infoIcon = CCSprite::create("pic/info.png");
	CCSprite* quitIcon = CCSprite::create("pic/quit.png");
	playIcon->setPosition(ccp(360, 315));
	this->addChild(playIcon);
	quitIcon->setPosition(ccp(360, 225));
	this->addChild(quitIcon);


	CCMenuItemFont::setFontName("Î¢ÈíÑÅºÚ");
	CCMenuItemFont::setFontSize(60);
	CCMenuItemFont* newMenu = CCMenuItemFont::create("Start", this, menu_selector(MenuScene::menuNewCallback));
	CCMenuItemFont* quitMenu = CCMenuItemFont::create("Quit", this, menu_selector(MenuScene::menuCloseCallback));

	//CCMenuItemImage* back = CCMenuItemImage::create(
	//	"pic/back.png", "pic/back.png", this, menu_selector(MenuScene::menuNewCallback));
	//CCMenuItemImage* showMap = CCMenuItemImage::create(
	//	"pic/camera.png", "pic/camera.png", this, menu_selector(MenuScene::menuCloseCallback));
	//CCMenu* menu = CCMenu::create(back, showMap, NULL);
	//menu->alignItemsHorizontally();
	//menu->setPosition(ccp(600, 400));
	//this->addChild(menu, 3);

	CCMenu* menu = CCMenu::create(newMenu, quitMenu, NULL);
	menu->alignItemsVertically();
	menu->setPosition(ccp(500, 270));

	int i=0;
	CCNode* child;
	CCArray * pArray = menu->getChildren();
	CCObject* pObject = NULL;
	CCARRAY_FOREACH(pArray, pObject)
	{
		if(pObject == NULL)
			break;

		child = (CCNode*)pObject;

		CCPoint dstPoint = child->getPosition();
		int offset = (int) (150 + 50);
		if( i % 2 == 0)
			offset = -offset;

		child->setPosition( CCPointMake( dstPoint.x + offset, dstPoint.y) );
		child->runAction( 
			CCEaseElasticOut::create(
			CCMoveBy::create(2, CCPointMake(dstPoint.x - offset,0)), 0.5f
			) 
			);
		i++;
	}
	addChild(menu);

	return true;
}

void MenuScene::menuNewCallback(CCObject* pSender)
{
	CCScene* scene = MainScene::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(2, scene, true));
}

void MenuScene::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
