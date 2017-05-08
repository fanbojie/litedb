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

#ifndef LITEBASE_CONDITIONVARIABLE_H
#define LITEBASE_CONDITIONVARIABLE_H

#ifdef WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif
 
#ifdef WIN32
#define CONVAR_T CONDITION_VARIABLE    
#define CONVAR_INIT(c) InitializeConditionVariable(c) 
#define CONVAR_UNINIT(c)
#define CONVAR_WAIT(c, m)   SleepConditionVariableCS(c, m, INFINITE)
#define CONVAR_TIMEWAIT(c, m, t)  SleepConditionVariableCS(c, m, t)
#define CONVAR_WAKE(c)  WakeConditionVariable(c)
#define CONVAR_WAKEALL(c) WakeAllConditionVariable(c)
#else
#define CONVAR_T pthread_cond_t
#define CONVAR_INIT(c)  pthread_cond_init(c, NULL) 
#define CONVAR_UNINIT(c)    pthread_cond_destroy(c)
#define CONVAR_WAIT(c, m)   pthread_cond_wait(c, m)
#define CONVAR_TIMEWAIT(c, m, t)  pthread_cond_timewait(c, m, t)
#define CONVAR_WAKE(c)  pthread_cond_signal(c)
#define CONVAR_WAKEALL(c) pthread_cond_broadcast(c)
#endif

#include "Config.h"
#include "Noncopyable.h"
#include "Mutex.h"

namespace litebase
{
	namespace details
	{
		class LITEBASE_DECL CConVariable: public litebase::details::CNoncopyable
		{
		public:
			CConVariable()
			{
                CONVAR_INIT(&m_conVar);
			}

			~CConVariable()
			{
				CONVAR_UNINIT(&m_conVar);
			}

			void wait(int milliSeconds = 0)
			{
				if (milliSeconds == 0)
				{
					CONVAR_WAIT(&m_conVar, m_mutex.getMutex());
				}
				else
				{
                    #ifdef WIN32
                    CONVAR_TIMEWAIT(&m_conVar, m_mutex.getMutex(), milliSeconds);
                    else
                    timespec waitTimes;
                    waitTimes.tv_sec = milliSeconds/1000;
                    waitTimes.tv_nsec = (long)((milliSeconds%1000)*10e6);
                    CONVAR_TIMEWAIT(&m_conVar, m_mutex.getMutex(), &waitTimes);
                    #endif
				}
			}

			void notify()
			{
				CONVAR_WAKE(&m_conVar);
			}

			void notifyAll()
			{
				CONVAR_WAKEALL(&m_conVar);
			}

			litebase::details::CMutex& getMutex()
			{
				return m_mutex;
			}

		private:
			CONVAR_T    m_conVar;
			litebase::details::CMutex	m_mutex;
		};
	}
}
#endif
