#ifndef __guutil_memory_memorymanager_h__
#define __guutil_memory_memorymanager_h__

#include <cstdint>
#include <mutex>
#include <memory>
#include <guutil/memory/impl/memorymanager_impl.h>

namespace guutil {
	enum class MMKind {
		PLAIN,
		BUDDY
	};

	class MemoryManager {
	public:
		MemoryManager(const MMKind kind, const uint64_t size);
		~MemoryManager();
	
		void* allocate(const uint64_t size);
		void deallocate(void* ptr);

	protected:
		std::mutex mutex;
		std::unique_ptr<MemoryManagerImpl> impl;
	};
}

#endif
