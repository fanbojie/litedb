//
//  $Id$
//
//  Copyright (c)1992-2013, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//    Description:    
//    Revisions:        Year-Month-Day  SVN-Author  Modification
//                       2013-12-18      li_jun5      Create
//

#ifndef LITEBASE_TRACE_H
#define LITEBASE_TRACE_H

#include <string>
#include "Mutex.h"
#define  LOG_CONSOLE_MASK    0x1
#define  LOG_FILE_MASK       0x2

namespace litebase
{
    namespace details
    {
        enum TraceLevel
        {
            LOG_ERROR = 0,
            LOG_WARNING,
            LOG_INFO,
            LOG_DEBUG,

            LOG_MAX,
        };

        // ��־������Ϣ
        struct LogConfig
        {
            LogConfig():outputType(0),  fileSize(0), fileCounts(0), level(LOG_INFO)
            {
            }

            std::string saveDir;
            int         outputType;
            int         fileSize;   // ��־�ļ���С(M)
            int         fileCounts; // ������־�ļ�����
            int         level;      // ��־����
        };

        const char* const TraceLevelStr[LOG_MAX] =
        {
            "ERR",
            "WAR",
            "INF",
            "DBG",
        };

        class CTrace
        {
        private:
            CTrace();
            ~CTrace();
            CTrace(const CTrace& trace);
            CTrace& operator=(const CTrace& trace);

        public:
            static CTrace&  getInstance();
            int  init(const char* prefix, const LogConfig &log_cfg);
            // ������־���ã���־���������ʽ����С
            void loadConfig(const LogConfig &log_cfg);   
            void printLog(TraceLevel level,
                const char* funname,
                const char* declare, 
                int error,
                const char *fmt,  ...);

        private:
            void writeToFile(const char* txt);
            void writeToConsole(TraceLevel level, const char* txt);
            // ��־�ļ����ݣ����ݸ���������m_maxBackupIndex
            void rollOver();  

        private:
            std::string m_logDir;               // ��־�ļ�Ŀ¼
            std::string m_fileName;             // ��־�ļ�����
            std::string m_fileExt;              // ��־�ļ���չ��
            int         m_outputType;           // 0:�������־ 1:�������־�ļ� 2:������ն� 3:������ļ����ն�
            int         m_maxFileSize;          // ��־�ļ�����С  ��λΪM
            int         m_maxBackupIndex;       // ��־�ļ���౸�ݸ���  
            int         m_trace_level;          // 0:ERROR 1:WARNING 2:INFO 3:DEBUG               
            litebase::details::CMutex           m_lock;
            FILE*       m_file;
        };


        // ʹ��TRACE_XX_OBJ���࣬��Ҫ�̳�CDeclearObj
        // �Զ���������ִ���������Ĺ������������ʱ����m_declear_obj
        class CDeclearObj
        {
        public:
            CDeclearObj();
            virtual ~CDeclearObj();

        protected:
            char          m_declare_obj[128];
        };
    }
}

#define TRACE_INIT(file_name, cfg) (litebase::details::CTrace::getInstance().init(file_name, cfg))
#define TRACE_LOAD_CFG(cfg) (litebase::details::CTrace::getInstance().loadConfig(cfg))

#define TRACE_INFO_OBJ(fmt, ...) (litebase::details::CTrace::getInstance().printLog(litebase::details::LOG_INFO, __FUNCTION__, m_declare_obj, 0, fmt, ## __VA_ARGS__))
#define TRACE_WARNING_OBJ(fmt, ...) (litebase::details::CTrace::getInstance().printLog(litebase::details::LOG_WARNING, __FUNCTION__, m_declare_obj, 0, fmt, ## __VA_ARGS__))
#define TRACE_ERR_OBJ(error, fmt, ...) (litebase::details::CTrace::getInstance().printLog(litebase::details::LOG_ERROR, __FUNCTION__, m_declare_obj, error, fmt, ## __VA_ARGS__))
#define TRACE_DEBUG_OBJ(fmt, ...) (litebase::details::CTrace::getInstance().printLog(litebase::details::LOG_DEBUG, __FUNCTION__, m_declare_obj, 0, fmt, ## __VA_ARGS__))

#define TRACE_INFO(fmt, ...) (litebase::details::CTrace::getInstance().printLog(litebase::details::LOG_INFO, __FUNCTION__, "", 0, fmt, ## __VA_ARGS__))
#define TRACE_WARNING(fmt, ...) (litebase::details::CTrace::getInstance().printLog(litebase::details::LOG_WARNING, __FUNCTION__, "", 0, fmt, ## __VA_ARGS__))
#define TRACE_ERR(error, fmt, ...) (litebase::details::CTrace::getInstance().printLog(litebase::details::LOG_ERROR, __FUNCTION__, "", error, fmt, ## __VA_ARGS__))
#define TRACE_DEBUG(fmt, ...) (litebase::details::CTrace::getInstance().printLog(litebase::details::LOG_DEBUG, __FUNCTION__, "", 0, fmt, ## __VA_ARGS__))

#endif // __INCLUDE_TRACE_H__

