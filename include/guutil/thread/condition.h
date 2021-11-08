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
	private:
		NATIVE_CONDITION_HANDLE handle;

	public:
		Condition(void);
		virtual ~Condition(void);

		void wait(int32_t usec);
		void signal(void);
	};

}

#endif
