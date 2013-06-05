#ifndef __HELPER_H__
#define __HELPER_H__

#include<string>

#include "iconv\iconv.h"
#pragma comment(lib,"libiconv.lib")

#include "cocos2d.h"

using namespace cocos2d;

class Helper
{
public:
	static CCPoint getPosByName(std::string name, CCTMXTiledMap* map);
	static std::string GBKToUTF8(const std::string& str);


	static bool IConvConvert(const char *from_charset, const char *to_charset, const char *inbuf, int inlen, char *outbuf, int outlen);
};

#endif