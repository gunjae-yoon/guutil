#ifndef __guutil_thread_condition_impl_h__
#define __guutil_thread_condition_impl_h__

#include <guutil/thread/condition.h>

namespace guutil {

#if defined(__linux__)
	typedef pthread_cond_t NATIVE_CONDITION_HANDLE;
	typedef pthread_mutex_t NATIVE_CONDITION_MUTEX_HANDLE;
#elif defined(_WIN32)
#endif

	class DLL_EXPORT ConditionImpl : public Condition {
	private:
		NATIVE_CONDITION_HANDLE handle;
		NATIVE_CONDITION_MUTEX_HANDLE mutexHandle;

	public:
		ConditionImpl(void);
		virtual ~ConditionImpl(void);

		virtual void init(void);
		virtual void wait(int32_t usec);
		virtual void signal(void);
	};

}

#endif
