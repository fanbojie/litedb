#include "Version.h"
#include <sstream>
#include <stdio.h>
#include <string>

#ifndef WIN32
#include <strings.h> // strcasecmp()
#endif

void printVerInfo(std::string progName)
{
    std::stringstream ss;
    ss << progName << " Build at: " <<__DATE__<<" "<<__TIME__;
    printf("%s\n", ss.str().c_str());
    return;
}

std::string splitProgName(char * path)
{
    std::string dir = path;
    size_t pos = dir.rfind('/');
    if (pos != std::string::npos)
    {
        return dir.substr(pos+1);
    }

    return dir;    
}

bool traceVerInfo(int argc, char* argv[])
{
    if(argc == 2)
    {
        const char* verTags[]=
        {
            "-v",
            "--version",
            "-version",
            "/v",
            "/version"
        };
        const int count=sizeof(verTags)/sizeof(const char*);
        for(int i = 0; i < count; ++i)
        {
#if defined(WIN32)||defined(WIN64)||defined(WINCE)
            if( 0==_stricmp( argv[1],verTags[i]) )
#else
            if( 0 == strcasecmp( argv[1], verTags[i] ) )
#endif
            {

                printVerInfo(splitProgName(argv[0]));
                return true;
            }
        }
    }
    return false;
}