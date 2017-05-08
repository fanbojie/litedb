#include "Utility.h"
#include <string.h>
#include <sstream>

#ifdef WIN32
#define strtok_r strtok_s
#endif

using namespace std;

void litebase::utility::CUtility::parseString(const string& str, const string& token, 
										        vector<string> &retValue)
{
	char *pch = NULL; 
	char *context = NULL;
	pch = strtok_r((char*)str.c_str(), token.c_str(), &context);
	while(pch != NULL)
	{
		retValue.push_back(pch);
		pch = strtok_r(NULL, token.c_str(), &context);
	}
}

string litebase::utility::CUtility::int2Str(int integer)
{
	stringstream ss;
	ss<<integer;
	return ss.str();
}

void litebase::utility::CUtility::splitString( const std::string& str, const std::string &endStr, const std::string& delims, std::vector<std::string> &retValue )
{
    size_t pos = str.find(delims);
    size_t endPos = str.find(endStr);
    if (pos == string::npos || endPos == string::npos)
    {
        return;
    }

    string returnKey = "\r\n";
    while (pos < endPos)
    {
        pos += delims.length()+returnKey.length();
        pos += returnKey.length();
        size_t findPos = str.find(returnKey, pos);
        string subString = str.substr(pos, findPos-pos);
        retValue.push_back(subString);
        pos = findPos+returnKey.length();
        pos += returnKey.length();
        findPos = str.find(returnKey, pos);
        subString = str.substr(pos, findPos-pos);
        pos = findPos+returnKey.length();
        pos = str.find(delims, pos);
    }
}
