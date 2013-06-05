#ifndef __HERO_SPRITE_H__
#define __HERO_SPRITE_H__

#include "cocos2d.h"

#include "MapTiled.h"

using namespace cocos2d;

class HeroSprite : public cocos2d::CCSprite
{	
public:
	void move(CCPoint finalLocation, int direction);
	void run(CCPoint finalLocation, int direction);

	static float metaDuration;
	static float stepLength;
};

#endif
