#include "TalkLayer.h"

void TalkLayer::setScene(CCScene* _scene)
{
	this->scene = _scene;

	//((MainScene*)(this->scene->getChildByTag(0)))->setTouchEnabled(false);
}

void TalkLayer::setXml(std::string _xmlFile)
{
	this->xmlFile = _xmlFile;

	talking->readXml(this->xmlFile.c_str());
	talking->showTalk();

	headIcon = CCSprite::create(("headicons/"+talking->getHeadIcon()).c_str());
	headIcon->setPosition(ccp(700, 80));
	headIcon->setScale(1.4);
	this->addChild(headIcon);
}

TalkLayer* TalkLayer::create(std::string _xmlFile, CCScene* _scene)
{
	TalkLayer* tmp = TalkLayer::create();
	tmp->setXml(_xmlFile);
	tmp->setScene(_scene);

	return tmp;
}

bool TalkLayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	this->setTouchEnabled(true);

	talking = new Talking();

	CCSprite* background = CCSprite::create("pic/talkBackground.png");
	background->setPosition(ccp(400, 75));
	background->setOpacity(100);
	this->addChild(background);

	talkingText = CCLabelTTF::create("Hello", "Î¢ÈíÑÅºÚ", 24, CCSize(600,300), CCTextAlignment::kCCTextAlignmentLeft);
	talkingText->setColor(ccc3(255,255,255));
	talkingText->setPosition(ccp(320,000));
	talking->setTalkingLabel(talkingText);
	this->addChild(talkingText);

	return true;
}

bool TalkLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}

void TalkLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	bool tmp = talking->showTalk();
	if(! tmp)
	{
		this->scene->removeChild(this);
		((MainScene*)(this->scene->getChildByTag(0)))->setTouchEnabled(true);
	}
	else
	{
		this->removeChild(headIcon);
		std::string tmp = talking->getHeadIcon();
		tmp = "headicons/" + tmp;
		headIcon = CCSprite::create(tmp.c_str());
		headIcon->setPosition(ccp(700, 80));
		headIcon->setScale(1.4);
		this->addChild(headIcon);
	}

}

void TalkLayer::registerWithTouchDispatcher(void)
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}



