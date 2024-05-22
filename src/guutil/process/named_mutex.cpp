#include <guutil/process/named_mutex.h>
#include <fcntl.h>

namespace guutil {
	named_mutex::named_mutex(const char* mutexName, uint32_t max) : semaphore(nullptr), name(mutexName) {
		semaphore = sem_open(mutexName, O_CREAT, 0644, max);
		if (semaphore == SEM_FAILED) {
			// error: failed to open semaphore
		}
	}

	named_mutex::~named_mutex() {
		if (semaphore != nullptr) {
			if (sem_close(semaphore) == -1) {
				// error: failed to close semaphore
			}
		}
	}

	void named_mutex::lock() {
		if (semaphore == nullptr) {
			// error: pre-condition not met (semaphore has not opened)
		}
		
		if (sem_wait(semaphore) == -1) {
			// error: failed to get semaphore
		}
	}

	void named_mutex::unlock() {
		if (semaphore == nullptr) {
			// error: pre-condition not met (semaphore has not opened)
		}

		if (sem_post(semaphore) == -1) {
			// error: failed to release semaphore
		}
	}
}
