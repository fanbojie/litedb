#include "Trace.h"
#include <fcntl.h>
#include <stdarg.h>
#include <string>
#include <string.h>
#include <stdio.h>
#include "Mutex.h"
#include "ScopeLock.h"
#include "Utility.h"

#ifdef WIN32
#include <windows.h>
#include <time.h>
#include "direct.h"
#define getpid	        GetCurrentProcessId
#define pthread_self    GetCurrentThreadId
#define CreateDir(dir)  _mkdir(dir)
#define snprintf        _snprintf
#else
#include <unistd.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <signal.h>
#define CreateDir(dir)    mkdir(dir, S_IRWXU)
#endif

#define FILE_NAME_LEN  128

using namespace litebase::details;
using namespace litebase::utility;

CTrace::CTrace()
: m_fileExt(".log")
, m_outputType(0)
, m_maxFileSize(0)
, m_maxBackupIndex(0)
, m_trace_level(LOG_INFO)
, m_file(NULL)
{
}

CTrace::~CTrace()
{
    if (m_file)
    {
        fclose(m_file);
        m_file = NULL;
    }
}

CTrace& CTrace::getInstance()
{
    static CTrace trace;
    return trace;
}

int CTrace::init(const char* prefix, const LogConfig& log_cfg)
{
    loadConfig(log_cfg);
    m_logDir = log_cfg.saveDir.empty() ? "log" : log_cfg.saveDir;

    CreateDir(m_logDir.c_str());

    char tmbuf[64] = {0};
    time_t nowtime = time(NULL);
    struct tm *tempTm = localtime(&nowtime);

    char logFile[FILE_NAME_LEN] = {0};
    strftime(tmbuf, sizeof(tmbuf), "%Y%m%d_%H%M%S", tempTm);

    snprintf(logFile, FILE_NAME_LEN - 1, "%s_%d_%s", prefix, getpid(), tmbuf);
    m_fileName = m_logDir + "/" + logFile;
    m_logDir = m_fileName + m_fileExt;
    m_file = fopen(m_logDir.c_str(), "w+");
    if (m_file == NULL)
    {
        printf("init log file error.\n");
        return -1;
    }

    return 0;
}

void CTrace::loadConfig(const LogConfig &log_cfg)
{
    m_outputType = (log_cfg.outputType < 0 || log_cfg.outputType > 3) ? 1 : log_cfg.outputType;
    m_maxBackupIndex = log_cfg.fileCounts < 10 ? 10 : log_cfg.fileCounts;
    if (log_cfg.fileSize < 10 || log_cfg.fileSize > 50)
    {
        m_maxFileSize = 10 * 1024 * 1024;
    }
    else
    {
        m_maxFileSize = log_cfg.fileSize * 1024 * 1024;    
    }

    m_trace_level = (log_cfg.level < 0|| log_cfg.level > LOG_MAX) ? LOG_INFO : log_cfg.level;
}

void CTrace::printLog(
                      TraceLevel level, 
                      const char* funname,
                      const char* declare, 
                      int error,
                      const char *fmt,  ...)
{
    if (m_outputType == 0  || level > m_trace_level)
    {
        return;
    }

    litebase::details::CScopeLock lock(m_lock);

    char time_str[64] = {0};
#ifdef WIN32
    SYSTEMTIME time;
    GetLocalTime(&time);
    snprintf(time_str, sizeof(time_str) - 1, "%04d-%02d-%02d %02d:%02d:%02d-%03lu", time.wYear, time.wMonth, time.wDay,
        time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
#else
    struct timeval time_val;
    gettimeofday(&time_val, NULL);
    struct tm *tempTm = localtime(&time_val.tv_sec);
    snprintf(time_str, sizeof(time_str) - 1, "%04d-%02d-%02d %02d:%02d:%02d-%03lu", tempTm->tm_year + 1900, tempTm->tm_mon + 1, tempTm->tm_mday,
        tempTm->tm_hour, tempTm->tm_min, tempTm->tm_sec, time_val.tv_usec / 1000);
#endif // WIN32

    char declare_str[128] = {0};
    if (strcmp(declare, "") != 0)
    {
        snprintf(declare_str, sizeof(declare_str) - 1, " [%s]", declare);
    }

    char err_str[32] = {0};
    if (error != 0)
    {
        snprintf(err_str, sizeof(err_str) - 1, "error:%d, ", error);
    }

    char buffer[2048] = {0};
    int headlen = 0;

    snprintf(buffer, sizeof(buffer) - 1, "<%s, tid = %x> [%s] -%s (%s) %s", time_str, 
        (unsigned int)pthread_self(), TraceLevelStr[level], declare_str, funname, err_str);

    headlen = (int)strlen(buffer);

    va_list argp;
    va_start(argp, fmt);
    vsnprintf (buffer + headlen, sizeof(buffer) - headlen, fmt, argp) ;
    va_end(argp);
    int msgLen = strlen(buffer);
    buffer[msgLen] = '\n';

    if (m_outputType & LOG_CONSOLE_MASK)
    {
        writeToConsole(level, buffer);
    }

    if (m_outputType & LOG_FILE_MASK)
    {
        writeToFile(buffer);
    }
}

void CTrace::writeToFile( const char* txt )
{
    // 防止init创建文件失败后，继续调用日志
    if (m_file == NULL)
    {
        return;
    }

    int offset = ftell(m_file);
    if (offset >= m_maxFileSize)
    {
        rollOver();
    }

    if (m_file)
    {
        fprintf(m_file, "%s", txt);
        fflush(m_file);
    }
    else
    {
        printf("log file not init.\n");
    }
}

void CTrace::writeToConsole( TraceLevel level, const char* txt )
{
#ifndef WIN32
    switch (level)
    {
    case LOG_ERROR:
        printf("\033[0;31m%s", txt);
        break;
    case LOG_WARNING:
        printf("\033[0;33m%s", txt);
        break;
    case LOG_INFO:
        printf("\033[0;32m%s", txt);
        break;
    case LOG_DEBUG:
        printf("\033[0;37m%s", txt);
        break;
    default:
        printf("%s", txt);
        break;
    }
#endif
}

void CTrace::rollOver()
{
    if (m_file)
    {
        fclose(m_file);
    }
    std::string oldName = m_fileName + "_" + CUtility::int2Str(m_maxBackupIndex) + m_fileExt;
    ::remove(oldName.c_str());
    for (int i = m_maxBackupIndex - 1; i > 1; i--)
    {
        std::string newName = oldName;
        oldName = m_fileName + "_" + CUtility::int2Str(i) + m_fileExt;
        ::rename(oldName.c_str(), newName.c_str());
    }
    ::rename(m_logDir.c_str(), oldName.c_str());
    m_file = fopen(m_logDir.c_str(), "w+");
}

CDeclearObj::CDeclearObj()
{
    memset(m_declare_obj, 0 , sizeof(m_declare_obj));
}

CDeclearObj::~CDeclearObj()
{

}

