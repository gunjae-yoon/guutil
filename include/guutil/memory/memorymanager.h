#ifndef __guutil_memory_memorymanager_h__
#define __guutil_memory_memorymanager_h__

#include <cstdint>
#include <mutex>

namespace guutil {
	class MemoryManager {
	public:
		MemoryManager(const uint64_t size);
		virtual ~MemoryManager();
	
		void* allocate(const uint64_t size);
		void deallocate(void* ptr);

	protected:
		virtual void* _allocate(const uint64_t size) = 0;
		virtual void _deallocate(void* ptr) = 0;

	protected:
		const uint64_t capacity;
		std::mutex mutex;
	};
}

#endif
