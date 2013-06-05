#ifndef __MAP_TILED_H__
#define __MAP_TILED_H__

#include<string>

#include "cocos2d.h"

using namespace cocos2d;

class MapTiled : public CCTMXTiledMap
{
public:
	//int name;

	bool canMove(CCPoint pos);
	CCPoint tileCoortoPos(CCPoint pos);
};

#endif
