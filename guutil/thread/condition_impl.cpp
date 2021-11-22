#include <guutil/thread/condition_impl.h>

namespace guutil {

	ConditionImpl::ConditionImpl(void) {
	}

	ConditionImpl::~ConditionImpl(void) {
	}

	void ConditionImpl::init(void) {
#if defined(__linux__)
		pthread_mutex_init(&mutexHandle, NULL);
		pthread_cond_init(&handle, NULL);
#elif defined(_WIN32)
#endif
	}

	void ConditionImpl::wait(int32_t usec) {
#if defined(__linux_)
		pthread_cond_wait(&handle, &mutexHandle);
#elif defined(_WIN32)
#endif
	}

	void ConditionImpl::signal(void) {
#if defined(__linux_)
		thread_cond_signal(&handle);
#elif defined(_WIN32)
#endif
	}

}
