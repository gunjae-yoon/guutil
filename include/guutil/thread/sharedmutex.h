#ifndef __guutil_thread_sharedmutex_h__
#define __guutil_thread_sharedmutex_h__

#include <guutil/dllexport.h>
#include <guutil/thread/mutex.h>
#include <guutil/thread/condition.h>

#if defined(__linux__)
#include <string>
#endif

namespace guutil {

	class DLL_EXPORT SharedMutex : public Mutex {
	protected:
		SharedMutex(void);
		SharedMutex(std::string name);

	public:
		virtual ~SharedMutex(void);

		virtual void lock(void);
		virtual void unlock(void);

		static SharedMutex* createSharedMutex(std::string name);
	};

}

#endif
