#ifndef __TALK_NODE_H__
#define __TALK_NODE_H__

#include<string>

#include "cocos2d.h"

#include "tinyxml/tinyxml.h"

class TalkNode
{
public:
	bool anchor;
	std::string icon;
	std::string name;
	std::string content;
	void init(TiXmlNode *node);
	bool getAnchor(){return anchor;};
	const char* getIcon(){return icon.c_str();};
	const char* getName(){return name.c_str();};
	const char* getContent(){return content.c_str();};
	std::string getContentByLength(int length);
	int contentLeght;
	int getContentLength();
};

#endif