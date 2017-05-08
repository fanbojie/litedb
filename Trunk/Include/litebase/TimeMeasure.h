//
//  $Id$
//
//  Copyright (c)1992-2013, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//    Description:    
//    Revisions:        Year-Month-Day      SVN-Author       Modification
//                        2014-02-14        fan_bojie            Create
//

#ifndef LITEBASE_TIMEMEASURE_H
#define LITEBASE_TIMEMEASURE_H

#include "Config.h"
#include "Noncopyable.h"
#include "Trace.h"

#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <sys/times.h>
#endif

namespace litebase
{
    namespace details
    {
        class LITEBASE_DECL CTimeMeasure: public litebase::details::CNoncopyable
        {
        public:
            CTimeMeasure()
            {
                #ifdef WIN32
                m_start = GetTickCount();
                #else
                struct tms buf;
                m_start = (unsigned long)((long long)times(&buf) * 1000 / sysconf(_SC_CLK_TCK));
                #endif                
            }

            ~CTimeMeasure() 
            {
                #ifdef WIN32
                int cost = (GetTickCount() - m_start);
                #else
                struct tms buf;
                int cost = (unsigned long)((long long)times(&buf) * 1000 / sysconf(_SC_CLK_TCK)) - m_start;
                #endif

                if (cost >= 500)
                {
                    TRACE_WARNING("time cost=%d", cost);
                }
            }

            unsigned long getCostTime()
            {
                #ifdef WIN32
                return (GetTickCount() - m_start);
                #else
                struct tms buf;
                return (unsigned long)((long long)times(&buf) * 1000 / sysconf(_SC_CLK_TCK)) - m_start;
                #endif 
            }
        private:
            unsigned long m_start;
        };
    }
}
#endif
