#include "Talking.h"

Talking::Talking()
{
	talkIndex = 0;
	wordCount = 0;
	talkCount = 0;
}

void Talking::readXml(const char *filename)
{
	unsigned long filesize;
	const char *path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(filename);
	char *buffer = (char *)CCFileUtils::sharedFileUtils()->getFileData(path, "rb", &filesize);


	if (buffer == NULL)
	{
		return;
	}

	TiXmlDocument doc;
	doc.Parse(buffer);
	TiXmlNode *root = doc.FirstChild("plist"); 

	if (root)
	{
		TiXmlElement *element = root->ToElement();
		for (TiXmlNode* entityNode = root->FirstChild(); entityNode; entityNode = entityNode->NextSibling())
		{
			TalkNode *node= new TalkNode();
			node->init(entityNode);
			talkList.push_back(node);
		}
		talkCount = talkList.size();
	}
}

bool Talking::showTalk()
{
	if(talkIndex >= talkList.size())
		return false;

	TalkNode* node = (TalkNode*)talkList[talkIndex];
	talkingLabel->setString(Helper::GBKToUTF8(node->getContentByLength(node->getContentLength())).c_str());

	talkIndex++;

	return true;
}

std::string Talking::getHeadIcon()
{
	TalkNode* node = (TalkNode*)talkList[talkIndex -1];
	return node->icon;
}

//bool Talking::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
//{
//	TalkNode* node = (TalkNode*)talkList[talkIndex];
//	if (wordCount < node->getContentLength())
//	{
//		wordCount = node->getContentLength();
//	}
//
//	return true;
//}

void Talking::setTalkingLabel(CCLabelTTF* _TalkingLabel)
{
	talkingLabel = _TalkingLabel;
}