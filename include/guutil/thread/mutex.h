#ifndef __guutil_thread_mutex_h__
#define __guutil_thread_mutex_h__

#include <guutil/dllexport.h>

#if defined(__linux__)
#include <pthread.h>
#elif defined(_WIN32)
#endif

namespace guutil {

	class DLL_EXPORT Mutex {
	public:
		Mutex(void);
		virtual ~Mutex(void);

		virtual void init(void);
		virtual void lock(void);
		virtual void unlock(void);

		static Mutex* createInstance(void);
	};

}

#endif
