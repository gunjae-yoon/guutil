#include <guutil/thread/mutex_impl.h>

namespace guutil {

	MutexImpl::MutexImpl(void) {
	}

	MutexImpl::~MutexImpl(void) {
	}

	void MutexImpl::init(void) {
#if defined(__linux__)
		pthread_mutex_init(&handle, NULL);
#elif defined(_WIN32)
#endif
	}

	void MutexImpl::lock(void) {
#if defined(__linux__)
		pthread_mutex_lock(&handle);
#elif defined(_WIN32)
#endif
	}

	void MutexImpl::unlock(void) {
#if defined(__linux__)
		pthread_mutex_unlock(&handle);
#elif defined(_WIN32)
#endif
	}

}
