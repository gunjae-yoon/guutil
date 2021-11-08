#include <guutil/thread/mutex_impl.h>

namespace guutil {

	Mutex::Mutex(void) {
	}

	Mutex::~Mutex(void) {
	}

	void Mutex::lock(void) {
		static_cast<MutexImpl*>(this)->lock();
	}

	void Mutex::unlock(void) {
		static_cast<MutexImpl*>(this)->unlock();
	}

}
