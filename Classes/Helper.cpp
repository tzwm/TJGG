#include "Helper.h"

CCPoint Helper::getPosByName(std::string name, CCTMXTiledMap* map)
{
	CCTMXObjectGroup *objectgroup = map->objectGroupNamed("Object");
	CCDictionary *spawnPoint = objectgroup->objectNamed(name.c_str());
	int x = spawnPoint->valueForKey("x")->intValue();
	int y = spawnPoint->valueForKey("y")->intValue();
	
	return ccp(x, y);
}

bool Helper::IConvConvert(const char *from_charset, const char *to_charset, const char *inbuf, int inlen, char *outbuf, int outlen) 
{
	iconv_t cd = iconv_open(to_charset, from_charset);

	if (cd == 0) return false;

	const char **pin = &inbuf;

	char **pout = &outbuf;

	memset(outbuf,0,outlen);

	size_t ret = iconv(cd,pin,(size_t *)&inlen,pout,(size_t *)&outlen);

	iconv_close(cd);

	return ret == (size_t)(-1) ? false : true;
}

std::string Helper::GBKToUTF8(const std::string& str)
{
	const char* textIn = str.c_str();

	char textOut[256];

	bool ret = IConvConvert("gb2312", "utf-8", textIn, strlen(textIn),textOut, 256);

	return ret ? std::string(textOut) : std::string();
}