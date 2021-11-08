#include <guutil/thread/sharedmutex_impl.h>

namespace guutil {

#if defined(__linux__)
#define DEFAULT_GUUTIL_SHARED_MUTEX_PATH "/dev/shm/sem.";
#elif defined(_WIN32)
#define DEFAULT_GUUTIL_SHARED_MUTEX_PATH "C:\\temp\\";
#endif

	SharedMutexImpl::SharedMutexImpl(void) : SharedMutex() {
		filename = "guutil.sharedmutex";
		init();
	}

	SharedMutexImpl::SharedMutexImpl(std::string name) : SharedMutex(name) {
		filename = "guutil.";
		filename += name;
		init();
	}

	SharedMutexImpl::~SharedMutexImpl(void) {
		if(handle != NULL) {
			sem_unlink(filename.c_str());
			sem_close(handle);
		}
	}

	void SharedMutexImpl::init(void) {
		handle = sem_open(filename.c_str(), O_CREAT | O_EXCL, 0666, 1);
		if ((handle == SEM_FAILED) && (errno == EEXIST)) {
			handle = sem_open(filename.c_str(), 0);
		}
		else {
			printf("handle: %p, errno: %d\n", handle, errno);
		}
	}

	void SharedMutexImpl::lock(void) {
		sem_wait(handle);
	}

	void SharedMutexImpl::unlock(void) {
		sem_post(handle);
	}

}
