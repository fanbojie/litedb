#ifndef LITEBASE_REFERENCECOUNT_H
#define LITEBASE_REFERENCECOUNT_H

#include "Noncopyable.h"
#include "ScopeLock.h"
#include "Mutex.h"
#include "Config.h"

namespace litebase
{
    namespace details
    {
        class LITEBASE_DECL CRefCount: public litebase::details::CNoncopyable
        {
        public:
            CRefCount() :m_refCnt(1)
            {
            }

            virtual ~CRefCount() {};

            int addRef()
            {
                litebase::details::CScopeLock lock(m_refMutex);
                int refCount = ++m_refCnt;

                return refCount;
            }

            int decRef()
            {
                int refCount;

                {
                    litebase::details::CScopeLock lock(m_refMutex);
                    refCount = --m_refCnt;
                }

                if (refCount == 0)
                {
                    delete this;
                }

                return refCount;
            }

            // 只减引用计数，不删除对象，用于池
            int decRefNoFree()
            {
                int refCount;

                {
                    litebase::details::CScopeLock lock(m_refMutex);
                    refCount = --m_refCnt;
                }

                return refCount;
            }

        private:
            volatile int m_refCnt;
            litebase::details::CMutex m_refMutex;
        };
    }
}
#endif