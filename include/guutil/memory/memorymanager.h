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
	
	enum class MMArea {
		LOCAL,
		SHARED
	};

	class MemoryManager {
	public:
		MemoryManager(const MMKind kind = MMKind::PLAIN, const uint64_t size = 0, const MMArea area = MMArea::LOCAL);
		~MemoryManager();
	
		void* allocate(const uint64_t size);
		void deallocate(void* ptr);

	protected:
		std::mutex mutex;
		std::unique_ptr<MemoryManagerImpl> impl;
	};
}

#endif
