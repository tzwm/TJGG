#include "NpcSprite.h"


NpcSprite* NpcSprite::create(std::string file)
{
	NpcSprite* tmp = NpcSprite::create();
	tmp->initWithFile(file.c_str());
	//tmp->name = file;
	
	return tmp;
}

//NpcSprite::NpcSprite(std::string file)
//{
//	npc = CCSprite::create(file.c_str());
//	name = "";
//}
//
//NpcSprite::~NpcSprite()
//{
//	npc->release();
//}
