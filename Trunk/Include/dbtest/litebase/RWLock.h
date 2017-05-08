#ifndef LITEBASE_RWLOCK_H
#define LITEBASE_RWLOCK_H

#include <pthread.h>
#include "Noncopyable.h"

namespace litebase
{
    namespace details
    {
        // 需要支持windows版本
        class LITEBASE_DECL CRWLock: public litebase::details::CNoncopyable
        {
        public:
            CRWLock()
            {
                pthread_rwlock_init(&m_lock, NULL);
            }

            ~CRWLock()
            {
                pthread_rwlock_destroy(&m_lock);
            }

            int rlock()
            {
                return pthread_rwlock_rdlock(&m_lock);
            }

            int wlock()
            {
                return pthread_rwlock_wrlock(&m_lock);
            }

            int unlock()
            {
                return pthread_rwlock_unlock(&m_lock);
            }

        private:
            pthread_rwlock_t        m_lock;
        };

        class LITEBASE_DECL CRScopeLock: public litebase::details::CNoncopyable
        {
        public:
            explicit CRScopeLock(litebase::details::CRWLock& rwlock)
                : m_rwlock(rwlock)
            {
                m_lockFlag = m_rwlock.rlock();
            }

            ~CRScopeLock()
            {
                if (!m_lockFlag)
                {
                    m_rwlock.unlock();
                }
            }

        private:
            int m_lockFlag;
            litebase::details::CRWLock& m_rwlock;
        };

        class LITEBASE_DECL CWScopeLock: public litebase::details::CNoncopyable
        {
        public:
            explicit CWScopeLock(litebase::details::CRWLock& rwlock)
                : m_rwlock(rwlock)
            {
                m_lockFlag = m_rwlock.wlock();
            }

            ~CWScopeLock()
            {
                if (!m_lockFlag)
                {
                    m_rwlock.unlock();
                }
            }

        private:
            int m_lockFlag;
            litebase::details::CRWLock& m_rwlock;
    }
}
#endif
