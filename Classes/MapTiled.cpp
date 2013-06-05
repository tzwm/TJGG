#include "MapTiled.h"

CCPoint MapTiled::tileCoortoPos(CCPoint pos)
{
	int x = pos.x / this->getTileSize().width;
	int y = (this->getTileSize().height * this->getMapSize().height - pos.y) / this->getTileSize().height;

	return ccp(x, y);
}

bool MapTiled::canMove(CCPoint pos)
{
	if(pos.x < 64 || pos.y < 64)
		return false;
	if(pos.x >= this->getContentSize().width -64 || pos.y >= this->getContentSize().height -64)
		return false;

	CCPoint tileCoord = this->tileCoortoPos(pos);
	CCTMXLayer* meta = this->layerNamed("meta");
	int tileGid = meta->tileGIDAt(tileCoord);
	if(tileGid)
	{
		CCDictionary* properties =  this->propertiesForGID(tileGid);
		if(properties != NULL)
		{
			std::string collision = "";
			if(properties->valueForKey("Collidable"))
			{
				collision = properties->valueForKey("Collidable")->getCString();
			}
			if(collision.length() > 0 && collision == "True")
			{
				return false;
			}
		}
	}

	return true;
}
