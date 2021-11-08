#ifndef __guutil_thread_mutex_impl_h__
#define __guutil_thread_mutex_impl_h__

#include <guutil/thread/mutex.h>

namespace guutil {

#if defined(__linux__)
	typedef pthread_mutex_t NATIVE_MUTEX_HANDLE;
#elif defined(_WIN32)
#endif

	class MutexImpl : public Mutex {
	private:
		NATIVE_MUTEX_HANDLE handle;

	public:
		MutexImpl(void);
		virtual ~MutexImpl(void);

		virtual void lock(void);
		virtual void unlock(void);
	};

}

#endif
