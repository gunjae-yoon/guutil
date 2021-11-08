#include <guutil/thread/sharedmutex_impl.h>

namespace guutil {

	SharedMutex::SharedMutex(void) : Mutex() {
	}

	SharedMutex::SharedMutex(std::string name) : Mutex() {
	}

	SharedMutex::~SharedMutex(void) {
	}

	void SharedMutex::lock(void) {
		static_cast<SharedMutexImpl*>(this)->lock();
	}

	void SharedMutex::unlock(void) {
		static_cast<SharedMutexImpl*>(this)->unlock();
	}

	SharedMutex* SharedMutex::createSharedMutex(std::string name) {
		return new SharedMutexImpl(name);
	}
}
