#ifndef __guutil_process_named_mutex_h__
#define __guutil_process_named_mutex_h__

#include <cstdint>
#include <string>
#include <semaphore.h>

namespace guutil {
	class named_mutex {
	public:
		named_mutex(const char* mutexName, uint32_t max = 1);
		~named_mutex();
		
		void lock();
		void unlock();
		
	private:
		sem_t* semaphore;
		std::string name;
	};
}

#endif
