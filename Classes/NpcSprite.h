#ifndef __NPC_SPRITE_H__
#define __NPC_SPRITE_H__

#include<string>

#include "Talking.h"

#include "cocos2d.h"
using namespace cocos2d;

class NpcSprite :public CCSprite
{
public:
	std::string name;

	static NpcSprite* create(std::string file);

	CREATE_FUNC(NpcSprite);
};

//class NpcSprite
//{
//public:
//	std::string name;
//	CCSprite* npc;
//
//	NpcSprite(std::string file);
//	~NpcSprite();
//};

#endif
