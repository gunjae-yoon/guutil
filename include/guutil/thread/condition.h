#ifndef __guutil_thread_condition_h__
#define __guutil_thread_condition_h__

#include <stdint.h>
#include <guutil/dllexport.h>

#if defined(__linux__)
#include <pthread.h>
#elif defined(_WIN32)
#endif

namespace guutil {

#if defined(__linux__)
	typedef pthread_cond_t NATIVE_CONDITION_HANDLE;
#elif defined(_WIN32)
#endif

	class DLL_EXPORT Condition {
	protected:
		Condition(void);

	public:
		virtual ~Condition(void);

		virtual void init(void);
		virtual void wait(int32_t usec);
		virtual void signal(void);

		static Condition* createInstance(void);
	};

}

#endif
