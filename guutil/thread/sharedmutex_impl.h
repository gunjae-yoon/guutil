#ifndef __guutil_thread_sharedmutex_impl_h__
#define __guutil_thread_sharedmutex_impl_h__

#include <guutil/thread/sharedmutex.h>

#if defined(__linux__)
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#elif defined(_WIN32)
#endif

namespace guutil {

#if defined(__linux__)
	typedef sem_t* NATIVE_SHARED_MUTEX_HANDLE;
#elif defined(_WIN32)
#endif

	class SharedMutexImpl : public SharedMutex {
	private:
		std::string filename;
		NATIVE_SHARED_MUTEX_HANDLE handle;

	protected:
		void init(void);

	public:
		SharedMutexImpl(void);
		SharedMutexImpl(std::string prefix);
		virtual ~SharedMutexImpl(void);

		virtual void lock(void);
		virtual void unlock(void);
	};

}

#endif
