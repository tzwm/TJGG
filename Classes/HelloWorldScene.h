#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#include "SimpleAudioEngine.h"

#include "Talking.h"
#include "helper.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
	void setViewpointCenter(CCPoint pos);

	void registerWithTouchDispatcher(void);
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void setPlayerPosition(CCPoint pos);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif  // __HELLOWORLD_SCENE_H__