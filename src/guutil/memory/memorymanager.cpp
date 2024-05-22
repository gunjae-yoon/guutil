#include <guutil/memory/memorymanager.h>

namespace guutil {
	MemoryManager::MemoryManager(const uint64_t size) : capacity(size) {
	}

	MemoryManager::~MemoryManager() {
	}

	void* MemoryManager::allocate(const uint64_t size) {
		std::unique_lock<std::mutex> guard(mutex);
		return _allocate(size);
	}

	void MemoryManager::deallocate(void* ptr) {
		std::unique_lock<std::mutex> guard(mutex);
		_deallocate(ptr);
	}
}
